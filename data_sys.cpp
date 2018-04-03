#include "data_sys.h"
using namespace std;

data_sys::data_sys() :player_data(*this), all_enemies(*this), random_enemy(*this), select_one_enemy(*this)
{
	
}

void data_sys::draw_a_card()
{
	if (!cards_deck.empty())
	{
		cards_in_hand.push_back(cards_deck.back());
		cards_deck.pop_back();
		return;
	}
	cards_deck = cards_grave;
	cards_in_hand.push_back(cards_deck.back());
	cards_deck.pop_back();
}

info_to_battle_sys data_sys::card_effect(std::size_t id)
{
	switch (id)
	{
	case 0://打10
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
	case 1://加100力量
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, fix_buff_value(10000, 100))});
	case 2://100易伤
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::VULNERABLE, fix_buff_value(10000, 100))});
	case 3://100毒
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::POISON, fix_buff_value(100, 100))});
	case 4://随机打
	{
		info_to_battle_sys t;
		for (int i = 0; i < 10; ++i)
		{
			t.append(action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::NORMAL, 10));
		}
		return t;
	}
	default:
		break;
	}
	return info_to_battle_sys();
}

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	switch (id)
	{
	case buff_type::STRENGTH:
		return pair<string, size_t>(string("strength"), 1);
	case buff_type::VULNERABLE:
		return pair<string, size_t>(string("strength"), 1);
	case buff_type::POISON:
		return pair<string, size_t>(string("poison"), 1);
	default:
		throw exception("buff id does not found");
	}
}
