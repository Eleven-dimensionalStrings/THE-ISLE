#include "interacting.h"
using namespace std;

info_to_battle_sys interacting_sys::play_a_card(std::size_t card_pos, game_entity* target)
{
	info_to_battle_sys result(action(battle_action_type::USE_A_CARD, &data.player_data, target,
		data.player_data.cards_in_hand[card_pos].card_type, card_pos));
	result.append(data.player_data.cards_in_hand[card_pos].use());
	return result;
}
