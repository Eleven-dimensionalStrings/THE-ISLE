#include "data_sys.h"
using namespace std;
battle_sys_data::battle_sys_data(vector<card>& t1,
	vector<card>& t2, vector<card>& t3,
	vector<card>& t4, vector<card>&t5, vector<card>&t6, vector<buff>&t7,
	std::vector<artifact>&t8, player& player_t, std::size_t& tgold, std::size_t& tfood,
	vector<enemy>& enemies_t)
	:cards_deck(t1), cards_grave(t2), cards_in_hand(t3), cards_removed(t4), cards_pool(t5), cards_equiped(t6),
	buff_pool(t7), player_data(player_t), gold(tgold), food(tfood), enemies_data(enemies_t)
{
}

battle_sys_data&& data_sys::get_battle_sys_data()
{
	return std::move(battle_sys_data());
}
