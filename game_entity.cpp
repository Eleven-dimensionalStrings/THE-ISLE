#include "game_entity.h"
#include "message.h"
#include "managers.h"
using namespace std;

void player::initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)
{
	
}



info_to_battle_sys player::create_message_to_battle_sys()
{

}

info_to_battle_sys game_entity::calling_change(change t)
{
	//ttt储存所有buff返回的info,最后加在修改后的change生成的info后面,返回给battle
	info_to_battle_sys ttt;
	for (auto i : buff_pool)
	{
		auto tt = i.on_calling(t);
		t = tt.first;
		ttt.append(tt.second);
	}

	return 
}

info_to_battle_sys game_entity::receiving_change(change)
{
	return info_to_battle_sys();
}


info_to_battle_sys game_entity::kill()
{
	return info_to_battle_sys();
}

info_to_battle_sys game_entity::add_buff(buff t)
{
	return info_to_battle_sys();
}

info_to_battle_sys game_entity::remove_buff(std::size_t buff_id)
{
	return info_to_battle_sys();
}

bool game_entity::is_alive()
{
	return false;
}

info_to_battle_sys game_entity::on_turn_begin()
{
	return info_to_battle_sys();
}

info_to_battle_sys game_entity::on_turn_end()
{
	return info_to_battle_sys();
}
