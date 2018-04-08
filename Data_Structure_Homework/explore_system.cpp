#include "explore_system.h"
#include "message.h"
#include "stack"

using namespace std;
using namespace explore_action_type;

void explore_system::process()
{
	while (!process_stack.empty())
	{
		explore_system_action temp = process_stack.top();
		process_stack.pop();
		switch (temp.action_id)
		{
		case AQUIRE_HIT_POINTS:
		{
			data->player_data.current_hp += temp.value;
			if (data->player_data.current_hp > data->player_data.max_hp)
			{
				data->player_data.current_hp = data->player_data.max_hp;
			}
			break;
		}
		case AQUIRE_MAX_HIT_POINTS:
		{
			data->player_data.max_hp += temp.value;
			data->player_data.current_hp += temp.value;
			break;
		}
		case REMOVE_HIT_POINTS:
		{
			data->player_data.current_hp -= temp.value;
			//should detect whether the game is over here;
			break;
		}
		case REMOVE_MAX_HIT_POINTS:
		{
			data->player_data.max_hp -= temp.value;
			if (data->player_data.current_hp > data->player_data.max_hp)
			{
				data->player_data.current_hp = data->player_data.max_hp;
			}
			break;
		}
		case AQUIRE_STRENGTH:
		{
			data->strength += temp.value;
			break;
		}
		case AQUIRE_DEXRITY:
		{
			data->dexterity += temp.value;
			break;
		}
		case AQUIRE_VITALITY:
		{
			data->vitality += temp.value;
			break;
		}
		case AQUIRE_LUCK:
		{
			data->luck += temp.value;
			break;
		}
		case REMOVE_STRENGTH:
		{
			data->strength -= temp.value;
			break;
		}
		case REMOVE_DEXRITY:
		{
			data->dexterity -= temp.value;
			break;
		}
		case REMOVE_VITALITY:
		{
			data->vitality -= temp.value;
			break;
		}
		case REMOVE_LUCK:
		{
			data->luck -= temp.value;
			break;
		}
		case AQUIRE_CARD:
		{
			data->cards_pool.push_back(temp.c);
			break;
		}
		case REMOVE_CARD:
		{
			//remove the card according to its position
			data->cards_pool.erase(data->cards_pool.begin() + temp.value, data->cards_pool.begin() + temp.value + 1);
			break;
		}
		case UPGRADE_CARD:
		{
			//upgrade the card according to its position
			data->cards_pool[temp.value] = card(data->cards_pool[temp.value].upgrade_version_id, data->card_upgrade_id[temp.value], data->card_name[temp.value]);
			break;
		}
		case CHANGE_CARD:
		{
			//change the card according to its position
			data->cards_pool.erase(data->cards_pool.begin() + temp.value, data->cards_pool.begin() + temp.value + 1);
			data->cards_pool.push_back(get_random_card(1,false)[0]);
			break;
		}
		case AQUIRE_ARTIFACT:
		{
			data->artifacts.push_back(temp.atf);
			break;
		}
		case REMOVE_ARTIFACT:
		{
			data->artifacts.erase(data->artifacts.begin() + temp.value, data->artifacts.begin() + temp.value + 1);
			break;
		}
		case AQUIRE_GOLD:
		{
			data->gold += temp.value;
			break;
		}
		case REMOVE_GOLD:
		{
			if (data->gold < temp.value)
			{
				data->gold = 0;
			}
			else
			{
				data->gold -= temp.value;
			}
			break;
		}
		case AQUIRE_FOOD:
		{
			data->food += temp.value;
			break;
		}
		case REMOVE_FOOD:
		{
			if (data->food < temp.value)
			{
				data->food = 0;
			}
			else
			{
				data->food -= temp.value;
			}
		}
		default:
			break;
		}
	}
}

explore_system_action::explore_system_action(std::size_t id, int val, artifact tatf, card tc)
	:action_id(id), value(val), atf(tatf), c(tc)
{
}
