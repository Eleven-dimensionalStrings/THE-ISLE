#include "battle_system.h"
#include <iostream>
#include <sstream>
using namespace std;
using std::size_t;
using namespace battle_action_type;
void battle_system::update()
{
	for (auto& i : from_interacting)
	{

	}
}

bool battle_system::send_message(info_to_battle_sys input)
{
	battle_system::interpret_message(input);
	//send back something afterwards
}

bool battle_system::interpret_message(info_to_battle_sys input)
{
	for (size_t i = input.action_set.size() - 1; i >= 0; --i)
	{
		switch (input.action_set[i].action_id)
		{
		case battle_action_type::CALLING_ACTION:
		{
			break;
		}
		case battle_action_type::PERFORMING_ACTION:
		{
			break;
		}
		default:
			break;
		}
	}
	delete &input;
}

void battle_system::process()
{
	while (!process_stack.empty())
	{
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
					//需要随机洗牌
					c_deck = std::move(my_random_engine.xipai(std::move(c_grave)));
				}
				if (c_deck.size())//抽空了卡组就抽不出东西了

				{
					c_in_hand.push_back(*(c_deck.end() - 1));
					c_deck.pop_back();
				}
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
			send_message((c_in_hand.end() - 1)->discard());
			c_in_hand.erase(c_in_hand.begin() + temp.value);
			break;
		}
		case TURN_END://还要调用buff的turn_end
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
		default:
			break;
		}
		process_stack.pop();
	}
}
