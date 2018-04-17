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

void explore_system::end_battle()
{
	if (data.is_battle == 1)
	{
		for (auto i = data.b_to_e_pipe.action_set.rbegin(); i != data.b_to_e_pipe.action_set.rend(); ++i)
		{
			process_stack.push(*i);
		}
		data.b_to_e_pipe.action_set.clear();
		data.is_battle = 0;
		this->process();
	}
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
			if (data.is_vaccant == 1)
			{
				for (int i = 0; i < data.artifacts.size(); ++i)
				{
					send_message(data.artifact_on_encounter_event(data.artifacts[i].artifact_id));
				}
			}
			data.next_event_id = 0;
			data.is_vaccant = 0;
			max_selection = 1;
			data.current_select_page = 0;
			data.choice_list.clear();
			data.choice_name_list.clear();
			send_message(data.event_effect(temp.value));
			break;
		}
		case EVENT_BODY:
		{
			data.text_to_be_displayed = temp.text;
			for (int i = 0; i < data.artifacts.size(); ++i)
			{
				send_message(data.artifact_on_event_body(data.artifacts[i].artifact_id));
			}
			switch (temp.type)
			{
			case PURE_TEXT:
			{
				//nothing happens but display the text
				break;
			}
			case PROCEED:
			{
				process_stack.push(e_action(ENCOUNTER_EVENT, MEANINGLESS_VALUE, temp.value, ""));
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
			case DUPLICATE_CARD_FROM_DECK:
			{
				info_to_explore_sys message;
				for (int i = 0; i < data.cards_pool.size(); ++i)
				{
					message.action_set.push_back(e_action(SELECTION, AQUIRE_CARD, data.cards_pool[i], i));
				}
				send_message(message);
				break;
			}
			case AQUIRE_CARD_FROM_SELECTION:
			{
				info_to_explore_sys message;
				for (int i = 0; i < temp.value; ++i)
				{
					message.action_set.push_back(e_action(SELECTION, AQUIRE_CARD,
						e_random_engine().get_card_by_class(data.player_s_class), MEANINGLESS_VALUE));
				}
				send_message(message);
				break;
			}
			case REMOVE_CARD:
			{
				//remove the card according to its position
				data.cards_pool.erase(data.cards_pool.begin() + temp.value, data.cards_pool.begin() + temp.value + 1);
				break;
			}
			case REMOVE_CARD_FROM_DECK:
			{
				info_to_explore_sys message;
				for (int i = 0; i < data.cards_pool.size(); ++i)
				{
					message.action_set.push_back(e_action(SELECTION, REMOVE_CARD, data.cards_pool[i], i));
				}
				send_message(message);
				break;
			}
			case UPGRADE_CARD:
			{
				//upgrade the card according to its position
				data.cards_pool[temp.value] = card(data.cards_pool[temp.value].upgrade_version_id);
				break;
			}
			case UPGRADE_CARD_FROM_DECK:
			{
				info_to_explore_sys message;
				for (int i = 0; i < data.cards_pool.size(); ++i)
				{
					if (data.cards_pool[i].upgrade_version_id != 0)
						message.action_set.push_back(e_action(SELECTION, UPGRADE_CARD, data.cards_pool[i], i));
				}
				send_message(message);
				break;
			}
			case CHANGE_CARD:
			{
				//change the card according to its position
				data.cards_pool.push_back(card((e_random_engine().get_card_by_id(data.cards_pool[temp.value].card_id))));
				data.cards_pool.erase(data.cards_pool.begin() + temp.value);
				break;
			}
			case CHANGE_CARD_FROM_DECK:
			{
				info_to_explore_sys message;
				for (int i = 0; i < data.cards_pool.size(); ++i)
				{
					message.action_set.push_back(e_action(SELECTION, CHANGE_CARD, data.cards_pool[i], i));
				}
				send_message(message);
				break;
			}
			case AQUIRE_ARTIFACT:
			{
				data.artifacts.push_back(temp.atf);
				send_message(data.artifact_on_create(temp.atf.artifact_id));
				break;
			}
			case REMOVE_ARTIFACT:
			{
				data.artifacts.erase(data.artifacts.begin() + temp.value);
				send_message(data.artifact_on_remove(data.artifacts[temp.value].artifact_id));
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
			if (temp.restriction(&data))
			{
				data.choice_list.push_back(temp.to_event_body());
				data.choice_name_list.push_back(temp.text);
			}
			break;
		}
		case MAX_SELECTION:
		{
			max_selection = temp.value;
			break;
		}
		case ENEMY:
		{
			data.enemies_data.push_back(enemy(data, temp.value));
			break;
		}
		case START_BATTLE:
		{
			info_to_battle_sys initiate_info;
			for (int i = 0; i < data.artifacts.size(); ++i)
			{
				initiate_info.append(data.artifact_on_start_battle(data.artifacts[i].artifact_id));
			}
			for (int i = 0; i < data.enemies_data.size(); ++i)
			{
				initiate_info.append(data.enemy_battle_start(data.enemies_data[i].enemy_id));
			}
			data.e_to_b_pipe = initiate_info;
			data.is_battle = 1;
			break;
		}
		case NEXT_PHASE:
		{
			data.next_event_id = temp.value;
			break;
		}
		case END_EVENT:
		{
			for (int i = 0; i < data.artifacts.size(); ++i)
			{
				send_message(data.artifact_on_end_event(data.artifacts[i].artifact_id));
			}
			data.next_event_id = 0;
			data.is_vaccant = 1;
			data.current_select_page = 0;
			data.choice_list.clear();
			data.choice_name_list.clear();
			data.e_to_i_pipe = info_explore_to_interacting(interact_action_type::EXPLORE_TO_VACCANT);
			break;
		}
		default:
			break;
		}
	}
	if (!data.choice_list.empty())
	{
		data.e_to_i_pipe = info_explore_to_interacting(interact_action_type::EXPLORE_TO_SELECT, max_selection);
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
