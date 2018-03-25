#include "explore_system.h"
#include "event_cards.h"
#include "message.h"
#include "managers.h"
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
			break;
		}
		case AQUIRE_MAX_HIT_POINTS:
		{
			data->player_data.max_hp += temp.value;
			break;
		}
		case REMOVE_HIT_POINTS:
		{
			data->player_data.current_hp -= temp.value;
			break;
		}
		case REMOVE_MAX_HIT_POINTS:
		{
			data->player_data.max_hp -= temp.value;
			break;
		}
		case AQUIRE_CARD:
		{
			data->cards_pool.push_back();// mafan
			break;
		}

		case AQUIRE_RANDOM_CARD:
		{
			break;
		}

		case REMOVE_CARD:
		{
			int selected_card = temp.value;
			player_class.delete_card(selected_card);
			break;
		}

		case REMOVE_RANDOM_CARD:
		{
			break;
		}

		case UPGRADE_CARD:
		{
			player_class.upgrade_card(temp.value);
			break;
		}

		case UPGRADE_RANDOM_CARD:
		{
			break;
		}

		case CHANGE_CARD:
		{
			player_class.change_card(temp.value);
			break;
		}

		case CHANGE_RANDOM_CARD:
		{
			break;
		}

		case AQUIRE_ARTIFACT:
		{
			break;
		}

		case AQUIRE_RANDOM_ARTIFACT:
		{
			break;
		}

		case REMOVE_ARTIFACT:
		{
			player_class.delete_artifact(temp.value);
			break;
		}

		case REMOVE_RANDOM_ARTIFACT:
		{
			break;
		}

		case AQUIRE_GOLD:
		{
			int current = player_class.get_player_gold();
			player_class.set_player_gold(current + temp.value);
			break;
		}

		case REMOVE_GOLD:
		{
			int current = player_class.get_player_gold();
			player_class.set_player_gold(current - temp.value);
			break;
		}

		default:
			break;
		}
	}
}
