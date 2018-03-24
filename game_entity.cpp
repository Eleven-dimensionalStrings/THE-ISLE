#include <string>
#include "message.h"
#include "managers.h"
#include "battle_system.h"
#include "game_entity.h"
using namespace std;
using std::size_t;

void player::initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)
{

}

info_to_battle_sys player::on_turn_begin()
{
	for (auto &i : data.cards_in_hand)
	{
		i.is_reserve = 0;
	}
	return info_to_battle_sys();
}


game_entity::game_entity()
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
		current_hp -= present_act.value;
		if (current_hp <= 0)
			return this->kill();
	}
	else if (present_act.type < 20000)//增加生命值
	{
		current_hp += present_act.value;
		if (current_hp > max_hp)
			current_hp = max_hp;
	}
	else if (present_act.type < 30000)//减少行动力
	{
		current_ap -= present_act.value;
	}
	else if (present_act.type < 40000)//增加行动力
	{
		current_ap += present_act.value;
	}
	else if (present_act.type < 50000)//添加buff
	{
		buff* ptr;
		if (ptr = buff_pool.find(present_act.type))
		{
			*ptr += buff(present_act.type, get_buff_life(present_act.type), get_buff_level(present_act.type));
			return info_to_battle_sys();
		}
		else
		{
			pair<string, size_t> t = data.get_buff(present_act.type); // pair<buff_name, priority>
			buff temp(present_act.type, t.first, t.second, get_buff_life(present_act.type), get_buff_level(present_act.type));
			buff_pool.push_back(temp);
			return temp.on_create(present_act.caller, present_act.listener);
		}
	}
	else if (present_act.type < 60000)//减少/删除buff
	{
		buff* ptr;
		if (ptr = buff_pool.find(present_act.type))
		{
			if (*ptr -= buff(present_act.type, get_buff_life(present_act.type), get_buff_level(present_act.type)))
			{
				info_to_battle_sys result = ptr->on_delete(present_act.caller, present_act.listener);
				buff_pool.erase(ptr);
				return result;
			}
		}
		else
			return info_to_battle_sys();
	}
	else if (present_act.type < 60000)//buff翻倍
	{
		buff* ptr;
		if (ptr = buff_pool.find(present_act.type))
		{
			ptr->buff_life *= get_buff_life(present_act.type);
			ptr->buff_level *= get_buff_level(present_act.type);
		}
		return info_to_battle_sys();
	}
	//其他再补充
	return std::move(result);

}

info_to_battle_sys game_entity::kill()
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

enemy::enemy() :game_entity()
{
}

void enemy::initiate(std::vector<card>& card_pool, std::vector<artifact>& artifact_list)
{
}

info_to_battle_sys enemy::kill()
{
	return info_to_battle_sys();
}

info_to_battle_sys enemy::on_turn_begin()
{
	return info_to_battle_sys();
}

info_to_battle_sys enemy::on_turn_end()
{
	return info_to_battle_sys();
}
