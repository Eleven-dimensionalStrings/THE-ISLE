#include <iostream>
#include <algorithm>
#include <sstream>
#include <random>
#include <ctime>
#include "battle_system.h"
#include "data_sys.h"
#include "message.h"
using namespace std;using namespace my_container;
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

void battle_system::initiate_battle()
{
	for (auto i = data.e_to_b_pipe.action_set.rbegin(); i != data.e_to_b_pipe.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
	data.e_to_b_pipe.action_set.clear();
	this->process();
	my_vector<card>&deck = data.cards_deck;
	deck = my_random_engine::shuffle(data.cards_pool);
	std::size_t temp_ap = data.player_data.current_ap;//to set the ap on the first round properly
	data.passed_turns = 0;
	//put inherent cards at the top
	for (int i = deck.size() - 1; i >= 0; --i)
	{
		if (deck[i].inherent)
		{
			deck.push_back(deck[i]);
			deck.erase(deck.begin() + i);
		}
	}


	send_message(data.player_data.on_turn_begin());
	data.player_data.current_ap = temp_ap;
}

void battle_system::send_message(info_to_battle_sys input)
{
	for (auto i = input.action_set.rbegin(); i != input.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
	//process();
}

void battle_system::deal_an_action()
{
	//TODO battle_fail
	if (battle_succ())
	{
		while (!process_stack.empty())process_stack.pop();
		//TODO
		info_to_battle_sys temp;
		for (auto&i : data.player_data.buff_pool)
		{
			data.b_to_e_pipe.append(i.on_battle_end(&data.player_data));
		}
		data.enemies_data.clear();
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
		if (temp.action_id == battle_action_type::PERFORMING_ACTION && temp.type <= 7)
			send_message(action(battle_action_type::ENTITY_BE_ATK, temp.caller, temp.listener, 0, 0));

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
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_deck = data.cards_deck;
		my_vector<card>& c_grave = data.cards_grave;
		for (size_t i = 0; i < t.action_set.begin()->value; ++i)
		{
			if (c_deck.empty())
			{
				c_deck = my_random_engine::shuffle(std::move(c_grave));
			}
			if (c_deck.size())
			{
				if (c_deck.size() && c_in_hand.size() < MAX_CARDS_IN_HAND)
				{
					c_in_hand.push_back(c_deck.back());
					c_deck.pop_back();
				}
			}
		}
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case ADD_BUFF:
	{
		for (int i = 0; i < temp.listener->buff_pool.size(); ++i)
		{
			(temp.listener->buff_pool[i].on_manipulate_buff(temp));
		}
		auto it = temp.listener->buff_pool.end();
		if ((it = temp.listener->find_buff(temp.type)) != temp.listener->buff_pool.end())
		{
			*it += buff(temp.type, temp.value);
			break;
		}
		else
		{
			pair<string, size_t> t = data.get_buff(temp.type); // pair<buff_name, priority>
			buff tbuff(temp.type, t.first, t.second, temp.value);
			temp.listener->buff_pool.push_back(tbuff);
			send_message(tbuff.on_create(temp.caller, temp.listener));
		}
		break;
	}
	case REMOVE_BUFF:
	{
		for (int i = 0; i < temp.listener->buff_pool.size(); ++i)
		{
			(temp.listener->buff_pool[i].on_manipulate_buff(temp));
		}
		auto it = temp.listener->buff_pool.end();
		if ((it = temp.listener->find_buff(temp.type)) != temp.listener->buff_pool.end())
		{
			if (temp.value == 0)
			{
				break;
			}
			if (*it - buff(temp.type, temp.value))
			{
				auto ti = *it;
				temp.listener->buff_pool.erase(it);
				send_message(ti.on_delete(temp.caller, temp.listener));
			}
			/*auto it = temp.listener->buff_pool.end();
			if ((it = temp.listener->find_buff(temp.type)) != temp.listener->buff_pool.end())
			{
				*it += buff(temp.type, temp.value);
				break;
			}
			else
			{
				*it -= buff(temp.type, temp.value);
			}*/
			break;
		}
		else if (temp.type == buff_type::STRENGTH || temp.type == buff_type::DEXTERITY || temp.type == buff_type::VITALITY)
		{
			pair<string, size_t> t = data.get_buff(temp.type); // pair<buff_name, priority>
			buff tbuff(temp.type, t.first, t.second, -static_cast<int>(temp.value));
			temp.listener->buff_pool.push_back(tbuff);
			send_message(tbuff.on_create(temp.caller, temp.listener));
		}
		send_message(temp.listener->performing_action(temp));
		break;
	}
	case P_KEEP_A_CARD:
	{
		data.cards_in_hand[temp.value].is_reserve = 1;
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case P_REMOVE_A_CARD:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_removed = data.cards_removed;
		send_message(c_in_hand[temp.value].remove(data));
		c_removed.push_back(c_in_hand[temp.value]);
		c_in_hand.erase(c_in_hand.begin() + temp.value);
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case P_DISCARD_A_CARD:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_grave = data.cards_grave;
		send_message(c_in_hand[temp.value].discard(data));
		deal_an_action();
		c_grave.push_back(c_in_hand[temp.value]);
		c_in_hand.erase(c_in_hand.begin() + temp.value);
		send_message(data.player_data.performing_action(temp));
		break;
	}

	case TURN_END:
	{
		for (auto&i : data.render_select_card)i = 0;
		send_message(data.player_data.on_turn_end());
		//deal_an_action();
		process();
		enemies_action();
		send_message(data.player_data.on_turn_begin());
		data.b_to_i_pipe = info_battle_to_interacting(interact_action_type::BATTLE_TO_VACCANT, MEANINGLESS_VALUE, MEANINGLESS_VALUE);
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
		/*else if (temp.listener == &data.all_enemies)
		{
		atkp.second = 233;
		}*/
		data.b_to_d.push_back(atkp);
		break;
	}
	case battle_action_type::USE_A_CARD:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_grave = data.cards_grave;
		my_vector<card>& c_removed = data.cards_removed;
		my_vector<card>& c_equiped = data.cards_equiped;
		if (data.cards_in_hand[temp.value].exhaust)
		{
			process_stack.push(action(battle_action_type::P_REMOVE_A_CARD, &data.player_data, &data.player_data, MEANINGLESS_VALUE, temp.value));
			/*c_removed.push_back(c_in_hand[temp.value]);
			c_in_hand.erase(c_in_hand.begin() + temp.value);*/
		}
		else if (data.cards_in_hand[temp.value].card_type == card_type::ABILITY)
		{
			c_equiped.push_back(c_in_hand[temp.value]);
			c_in_hand.erase(c_in_hand.begin() + temp.value);
		}
		else
		{
			c_grave.push_back(c_in_hand[temp.value]);
			c_in_hand.erase(c_in_hand.begin() + temp.value);
		}
		switch (temp.type)
		{
		case card_type::ATTACK:
		{
			process_stack.push(action(battle_action_type::ADD_BUFF
				, &data.player_data, &data.player_data, buff_type::USED_ATTACK_CARDS, 1));
			break;
		}
		case card_type::SKILL:
		{
			process_stack.push(action(battle_action_type::ADD_BUFF
				, &data.player_data, &data.player_data, buff_type::USED_SKILL_CARDS, 1));
			break;
		}
		case card_type::ABILITY:
		{
			process_stack.push(action(battle_action_type::ADD_BUFF
				, &data.player_data, &data.player_data, buff_type::USED_ABILITY_CARDS, 1));
			break;
		}
		default:
			break;
		}
		break;
	}
	case ADD_CARD_TO_HAND:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_deck = data.cards_deck;
		my_vector<card>& c_grave = data.cards_grave;
		if (c_in_hand.size() < MAX_CARDS_IN_HAND)
		{
			c_in_hand.push_back(card(temp.value));
		}
		else
		{
			c_grave.push_back(card(temp.value));
		}
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case ADD_CARD_TO_DECK:
	{
		my_vector<card>& c_deck = data.cards_deck;
		c_deck.insert(c_deck.begin() + my_random_engine().get_num(c_deck.size() - 1), card(temp.value));
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case ADD_CARD_TO_DECK_TOP:
	{
		data.b_to_i_pipe = info_battle_to_interacting(temp.action_id, temp.value, temp.type);
		break;
	}
	case P_ADD_CARD_TO_DECK_TOP:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_deck = data.cards_deck;
		c_deck.push_back(c_in_hand[temp.value]);
		c_in_hand.erase(c_in_hand.begin() + temp.value);
		send_message(data.player_data.performing_action(temp));
		break;
	}
	case PURIFIED_MOVE_A_CARD_TO_GRAVE:
	{
		my_vector<card>& c_in_hand = data.cards_in_hand;
		my_vector<card>& c_grave = data.cards_grave;
		c_grave.push_back(c_in_hand[temp.value]);
		c_in_hand.erase(c_in_hand.begin() + temp.value);
		break;
	}
	default:
		break;
	}
}

void battle_system::process()
{
	while (!process_stack.empty())
	{
		deal_an_action();
	}
}

bool battle_system::battle_succ()
{
	if (!data.player_data.is_alive())return 1;
	for (auto& i : data.enemies_data)
	{
		if (i.is_alive())return 0;
	}
	return 1;
}

void battle_system::enemies_action()
{
	for (auto& i : data.enemies_data)
	{
		send_message(i.on_turn_begin());
	}
	for (auto& i : data.enemies_data)
	{
		send_message(i.next_act);
		i.next_act.action_set.clear();
	}
	for (auto& i : data.enemies_data)
	{
		send_message(i.on_turn_end());
	}
}

my_container::my_vector<card> my_random_engine::shuffle(my_container::my_vector<card> v)
{
	my_vector<card>vv;
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

int my_random_engine::get_num(int max)
{
	if (max < 0)
	{
		max = 0;
	}
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(0, static_cast<int>(max));
	int ind = ran(e);
	return ind;
}