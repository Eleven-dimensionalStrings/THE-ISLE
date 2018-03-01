#include "game_entity.h"
#include "message.h"
#include "managers.h"
#include "battle_system.h"
using namespace std;

void player::initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)
{

}



info_to_battle_sys player::create_message_to_battle_sys()
{

}

info_to_battle_sys game_entity::calling_action(action iaction)
{
	info_to_battle_sys result(iaction);
	for (auto i : buff_pool)
	{
		result = i.on_calling(result);
	}

	//now that the potentially triggered changes are added,
	//we have to change the original change_type to PERFORMING_ACTION.
	result.action_set[0].action_id = battle_action_type::PERFORMING_ACTION;

	return std::move(result);
}

info_to_battle_sys game_entity::performing_action(action iaction)
{
	info_to_battle_sys result(iaction);
	for (auto i : buff_pool)
	{
		result = i.on_calling(result);
	}

	//now that the potentially triggered changes are added,
	//we have to perform the original action
	action present_act = result.action_set[0];
	result.action_set.erase(result.action_set.begin());
	if (present_act.type < 10000)//造成伤害
	{

	}
	else if (present_act.type < 20000)//添加/删除 buff
	{

	}
	//其他再补充
	return std::move(result);

}


info_to_battle_sys game_entity::kill()
{
	return info_to_battle_sys();
}

info_to_battle_sys game_entity::add_buff(buff t)
{
	bool buff_exist = 0;
	for (auto &i : buff_list)
	{
		if (i.buff_id == t.buff_id)
		{
			i += t;
			buff_exist = 1;
		}
	}
	if (!buff_exist)
	{
		buff_pool.push_back(t);
	}
}

info_to_battle_sys game_entity::remove_buff(buff t)
{
	for (auto i = buff_list.begin(); i != buff_list.end(); ++i)
	{
		if (i->buff_id == t.buff_id)
		{
			if (*i -= t)
			{
				info_to_battle_sys result = i->on_delete();
				buff_list.erase(i);
				return result;
			}
		}
	}

}

void game_entity::multiply_buff(buff)
{

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

//
//
//
//