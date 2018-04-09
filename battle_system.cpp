#include <iostream>
#include <algorithm>
#include <sstream>
#include <random>
#include <ctime>
#include "battle_system.h"
#include "data_sys.h"
#include "message.h"
using namespace std;
using std::size_t;
using namespace battle_action_type;
default_random_engine e(static_cast<int>(time(0)));
battle_system::battle_system(data_sys & d) :data(d)
{
}
void battle_system::update()
{
	for (auto i = data.i_to_b_pipe.action_set.rbegin(); i != data.i_to_b_pipe.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
	data.i_to_b_pipe.action_set.clear();
	this->process();
}

void battle_system::send_message(info_to_battle_sys input)
{
	for (auto i = input.action_set.rbegin(); i != input.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
}

void battle_system::process()
{
	while (!process_stack.empty())
	{
		if (battle_finishes())
		{
			while (!process_stack.empty())process_stack.pop();
			//TODO
			break;
		}
		action temp = process_stack.top();
		process_stack.pop();
		switch (temp.action_id)
		{
		case battle_action_type::CALLING_ACTION:
		{
			send_message(temp.caller->calling_action(temp));
			break;
		}
		case battle_action_type::PERFORMING_ACTION:
		{
			uniform_int_distribution<int> ran(0, static_cast<int>(data.enemies_data.size()) - 1);
			if (temp.listener == &data.random_enemy)
			{
				do
				{
					temp.listener = &data.enemies_data[ran(e)];
				} while (!temp.listener->is_alive());
			}
			send_message(temp.listener->performing_action(temp));
			break;
		}
		case KEEP_A_CARD:
		{
			data.b_to_i_pipe = info_battle_to_interacting(temp.action_id, temp.value, temp.type);
			break;
		}
		case REMOVE_A_CARD:
		{
			data.b_to_i_pipe = info_battle_to_interacting(temp.action_id, temp.value, temp.type);
			break;
		}
		case DISCARD_A_CARD:
		{
			data.b_to_i_pipe = info_battle_to_interacting(temp.action_id, temp.value, temp.type);
			break;
		}
		case DRAW_CARDS:
		{
			info_to_battle_sys t(temp);
			for (auto& i : data.player_data.buff_pool)
			{
				t = i.on_calling(t);
			}
			vector<card>& c_in_hand = data.cards_in_hand;
			vector<card>& c_deck = data.cards_deck;
			vector<card>& c_grave = data.cards_grave;
			for (size_t i = 0; i < t.action_set.begin()->value; ++i)
			{
				if (c_deck.empty())
				{
					c_deck = my_random_engine::xipai(std::move(c_grave));
				}
				if (c_deck.size())

				{
					c_in_hand.push_back(c_deck.back());
					c_deck.pop_back();
				}
			}
			break;
		}
		case ADD_BUFF://11,还有12/13在game_entity中需要移动过来
		{

			auto it = temp.listener->buff_pool.end();
			//先空着,之后写find
			if ((it = temp.listener->find_buff(temp.type)) != temp.listener->buff_pool.end())
			{
				*it += buff(temp.type, get_buff_life(temp.value), get_buff_level(temp.value));
				break;
			}
			else
			{
				pair<string, size_t> t = data.get_buff(temp.type); // pair<buff_name, priority>
				buff tbuff(temp.type, t.first, t.second, get_buff_life(temp.value), get_buff_level(temp.value));
				temp.listener->buff_pool.push_back(tbuff);
				send_message(tbuff.on_create(temp.caller, temp.listener));
			}
			break;
		}
		case P_KEEP_A_CARD:
		{
			data.cards_in_hand[temp.value].is_reserve = 1;
			break;
		}
		case P_REMOVE_A_CARD:
		{
			vector<card>& c_in_hand = data.cards_in_hand;
			vector<card>& c_removed = data.cards_in_hand;
			c_removed.push_back(c_in_hand[temp.value]);
			c_in_hand.erase(c_in_hand.begin() + temp.value);
			break;
		}
		case P_DISCARD_A_CARD:
		{
			vector<card>& c_in_hand = data.cards_in_hand;
			vector<card>& c_grave = data.cards_grave;
			c_grave.push_back(c_in_hand[temp.value]);
			send_message((c_in_hand.end() - 1)->discard(data));
			c_in_hand.erase(c_in_hand.begin() + temp.value);
			break;
		}
		case TURN_END:
		{
			vector<card>& c_in_hand = data.cards_in_hand;
			vector<card>& c_grave = data.cards_grave;
			for (auto i = c_in_hand.begin(); i != c_in_hand.end(); ++i)
			{
				if (!i->is_reserve)
				{
					c_grave.push_back(*i);
					c_in_hand.erase(i++);
				}
			}
			break;
		}
		case ENTITY_BE_ATK:
		{
			pair<size_t, size_t> atkp;
			if (temp.caller == &data.player_data)
			{
				atkp.first = 666;
			}
			else if (temp.caller >= &data.enemies_data[0] && temp.caller <= &data.enemies_data[0] + 10)
			{
				atkp.first = dynamic_cast<enemy*>(temp.caller) - &data.enemies_data[0];
			}
			else if (temp.caller == nullptr)
			{
				atkp.first = 999;
			}
			if (temp.listener == &data.player_data)
			{
				atkp.second = 666;
			}
			else if (temp.listener >= &data.enemies_data[0] && temp.listener <= &data.enemies_data[0] + 10)
			{
				atkp.second = dynamic_cast<enemy*>(temp.listener) - &data.enemies_data[0];
			}
			else if (temp.listener == nullptr)
			{
				atkp.second = 999;
			}
			data.b_to_d.push_back(atkp);
			break;
		}
		default:
			break;
		}
	}
}

bool battle_system::battle_finishes()
{
	if (!data.player_data.is_alive())return 1;
	for (auto& i : data.enemies_data)
	{
		if (i.is_alive())return 0;
	}
	return 1;
}

std::vector<card> my_random_engine::xipai(std::vector<card> v)
{
	vector<card>vv;
	default_random_engine e(static_cast<unsigned>(time(0)));
	while (!v.empty())
	{
		uniform_int_distribution<int> ran(0, static_cast<int>(v.size()) - 1);
		int ind = ran(e);
		vv.push_back(*(v.begin() + ind));
		v.erase(v.begin() + ind);
	}
	return vv;
}
