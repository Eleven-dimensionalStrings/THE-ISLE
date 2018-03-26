#include "data_sys.h"
using namespace std;

data_sys::data_sys() :player_data(*this), all_enemies(*this), random_enemy(*this), select_one_enemy(*this)
{
	card_effect.insert(pair < size_t, vector<action>>(0, vector<action>{action(battle_action_type::CALLING_ACTION
		, &player_data, &select_one_enemy, type_type::NORMAL, 10)}));
	card_effect.insert(pair < size_t, vector<action>>(1, vector<action>{action(battle_action_type::ADD_BUFF
		, &player_data, &player_data, buff_type::STRENGTH, mix_value(1000,100))}));
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

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	using namespace buff_type;
	switch (id)
	{
	case STRENGTH:
		return pair<string, size_t>(string("strength"), 1);
	default:
		return pair<string, size_t>("", 1);
	}
}
