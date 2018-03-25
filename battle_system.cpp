#include <iostream>
#include <algorithm>
#include <sstream>
#include "battle_system.h"
#include "data_sys.h"
using namespace std;
using std::size_t;
using namespace battle_action_type;
battle_system::battle_system(data_sys & d) :data(d)
{
}
void battle_system::update()
{
	for (auto i = data.i_to_b_pipe.action_set.rbegin(); i != data.i_to_b_pipe.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
	this->process();
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
	return 0;
}

info* battle_system::create_message()
{

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
					//��Ҫ���ϴ��
					c_deck = std::move(my_random_engine::xipai(std::move(c_grave)));
				}
				if (c_deck.size())//����˿���ͳ鲻��������

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
		case TURN_END://��Ҫ����buff��turn_end
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

std::vector<card> my_random_engine::xipai(std::vector<card> v)
{
	sort(v.begin(), v.end(), [](card& l, card& r) {return l.card_id > r.card_id; });
	return std::move(v);
}
