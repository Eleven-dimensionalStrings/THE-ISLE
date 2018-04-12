#include <random>
#include <ctime>
#include <stack>
#include "explore_system.h"
#include "message.h"
#include "data_sys.h"

using namespace std;
using namespace explore_action_type;
using namespace event_type;

explore_system::explore_system(data_sys & d) :data(d)
{
}

void explore_system::send_message(info_to_explore_sys input)
{
	for (auto i = input.action_set.rbegin(); i != input.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
}

void explore_system::update()
{
	for (auto i = data.i_to_e_pipe.action_set.rbegin(); i != data.i_to_e_pipe.action_set.rend(); ++i)
	{
		process_stack.push(*i);
	}
	data.i_to_e_pipe.action_set.clear();
	this->process();
}

void explore_system::process()
{
	while (!process_stack.empty())
	{
		e_action temp = process_stack.top();
		process_stack.pop();
		switch (temp.action_id)
		{
		case ENCOUNTER_EVENT:
		{
			data.is_vaccant = 0;
			send_message(data.event_effect(temp.value));
			break;
		}
		case EVENT_BODY:
		{
			switch (temp.type)
			{
			case PROCEED:
			{
				//TODO
				break;
			}
			case AQUIRE_HIT_POINTS:
			{
				data.player_data.current_hp += static_cast<int>(temp.value);
				if (data.player_data.current_hp > data.player_data.max_hp)
				{
					data.player_data.current_hp = data.player_data.max_hp;
				}
				break;
			}
			case AQUIRE_MAX_HIT_POINTS:
			{
				data.player_data.max_hp += static_cast<int>(temp.value);
				data.player_data.current_hp += static_cast<int>(temp.value);
				break;
			}
			case REMOVE_HIT_POINTS:
			{
				data.player_data.current_hp -= static_cast<int>(temp.value);
				//should detect whether the game is over here;
				break;
			}
			case REMOVE_MAX_HIT_POINTS:
			{
				data.player_data.max_hp -= static_cast<int>(temp.value);
				if (data.player_data.current_hp > data.player_data.max_hp)
				{
					data.player_data.current_hp = data.player_data.max_hp;
				}
				//should detect whether the game is over here;
				break;
			}
			case AQUIRE_STRENGTH:
			{
				data.strength += temp.value;
				break;
			}
			case AQUIRE_DEXRITY:
			{
				data.dexterity += temp.value;
				break;
			}
			case AQUIRE_VITALITY:
			{
				data.vitality += temp.value;
				break;
			}
			case AQUIRE_LUCK:
			{
				data.luck += temp.value;
				break;
			}
			case REMOVE_STRENGTH:
			{
				data.strength -= temp.value;
				break;
			}
			case REMOVE_DEXRITY:
			{
				data.dexterity -= temp.value;
				break;
			}
			case REMOVE_VITALITY:
			{
				data.vitality -= temp.value;
				break;
			}
			case REMOVE_LUCK:
			{
				data.luck -= temp.value;
				break;
			}
			case AQUIRE_CARD:
			{
				data.cards_pool.push_back(temp.selected_card);
				break;
			}
			case REMOVE_CARD:
			{
				//remove the card according to its position
				data.cards_pool.erase(data.cards_pool.begin() + temp.value, data.cards_pool.begin() + temp.value + 1);
				break;
			}
			case UPGRADE_CARD:
			{
				//upgrade the card according to its position
				data.cards_pool[temp.value] = card(data.cards_pool[temp.value].upgrade_version_id);
				break;
			}
			case CHANGE_CARD:
			{
				//change the card according to its position
				data.cards_pool.push_back(card((e_random_engine().get_card_by_id(data.cards_pool[temp.value].card_id))));
				data.cards_pool.erase(data.cards_pool.begin() + temp.value);
				break;
			}
			case AQUIRE_ARTIFACT:
			{
				data.artifacts.push_back(temp.atf);
				break;
			}
			case REMOVE_ARTIFACT:
			{
				data.artifacts.erase(data.artifacts.begin() + temp.value);
				break;
			}
			case AQUIRE_GOLD:
			{
				data.gold += temp.value;
				break;
			}
			case REMOVE_GOLD:
			{
				if (data.gold < temp.value)
				{
					data.gold = 0;
				}
				else
				{
					data.gold -= temp.value;
				}
				break;
			}
			case AQUIRE_FOOD:
			{
				data.food += temp.value;
				break;
			}
			case REMOVE_FOOD:
			{
				if (data.food < temp.value)
				{
					data.food = 0;
				}
				else
				{
					data.food -= temp.value;
				}
				break;
			}
			}
			break;
		}
		case SELECTION:
		{
			data.choice_list.push_back(temp.to_selection());
			data.choice_name_list.push_back(temp.text);
			break;
		}
		case ENEMY:
		{
			temp_enemy_list.push_back(enemy(data, temp.value));
			break;
		}
		case START_BATTLE:
		{
			//TODO
			break;
		}
		case NEXT_PHASE:
		{
			data.next_event_id = temp.value;
			break;
		}
		case END_EVENT:
		{
			data.is_vaccant = 1;
			data.choice_list.clear();
			data.choice_name_list.clear();
			data.e_to_i_pipe = info_explore_to_interacting(interact_action_type::TO_VACCANT);
			break;
		}
		default:
			break;
		}
	}
	if (!data.choice_list.empty())
	{
		data.e_to_i_pipe = info_explore_to_interacting(interact_action_type::TO_SELECT);
	}
}

size_t e_random_engine::get_card_by_id(int id)
{
	int lb, ub, dis = (id - 1) / 60;
	lb = 1 + 60 * dis;
	ub = 60 + 60 * dis;
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(lb, ub);
	int result = ran(e);
	return result;
}

size_t e_random_engine::get_card_by_class(int class_id)
{
	int lb, ub, dis = (class_id - 1) / 120;
	lb = 1 + 120 * dis;
	ub = 120 + 120 * dis;
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(lb, ub);
	int result = ran(e);
	return result;
}
