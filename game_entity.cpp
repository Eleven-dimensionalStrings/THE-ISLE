#include <string>
#include "message.h"
//#include "managers.h"
#include "battle_system.h"
#include "game_entity.h"
#include "data_sys.h"
using namespace std;
using std::size_t;

player::player(data_sys &d) :game_entity(d)
{
}

player::~player()
{
	//TODO
}

void player::initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)
{

}

info_to_battle_sys player::kill()
{
	return info_to_battle_sys();
}

info_to_battle_sys player::on_turn_begin()
{
	for (auto &i : data.cards_in_hand)
	{
		i.is_reserve = 0;
	}
	for (int i = 0; i < 2; ++i)data.draw_a_card();
	return info_to_battle_sys();
}

info_to_battle_sys player::on_turn_end()
{

	for (auto i = data.cards_in_hand.begin(); i != data.cards_in_hand.end();)
	{
		if (!i->is_reserve)
		{
			data.cards_grave.push_back(*i);
			i = data.cards_in_hand.erase(i);
		}
		else
			++i;
	}
	return info_to_battle_sys();

}


game_entity::game_entity(data_sys& d) :data(d), living_state(1),
max_hp(100), current_hp(100), max_ap(1), current_ap(1)
{
}

game_entity::~game_entity()
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

	return result;
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
	using namespace type_type;
	if (present_act.type <= 6)//造成伤害
	{
		current_hp -= static_cast<int>(present_act.value);
		if (current_hp <= 0)
			return this->kill();
	}
	else if (present_act.type == ADD_HP)//增加生命值
	{
		current_hp += static_cast<int>(present_act.value);
		if (current_hp > max_hp)
			current_hp = max_hp;
	}
	/*else if (present_act.type < 30000)//减少行动力
	{
		current_ap -= static_cast<int>(present_act.value);
	}*/
	else if (present_act.type == ADD_AP)//增加行动力
	{
		current_ap += static_cast<int>(present_act.value);
	}
	/*else if (present_act.type == REMOVE_BUFF)//减少/删除buff
	{
		//先空着,之后再改
		/*buff* ptr;
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

		也是先空着
		if (ptr = buff_pool.find(present_act.type))
		{
			ptr->buff_life *= get_buff_life(present_act.type);
			ptr->buff_level *= get_buff_level(present_act.type);
		}
		return info_to_battle_sys();
	}*/
	//其他再补充
	return result;

}

info_to_battle_sys game_entity::kill()
{
	return info_to_battle_sys();
}

bool game_entity::is_alive()
{
	if (current_hp <= 0)
		living_state = 0;
	return living_state;
}

info_to_battle_sys game_entity::on_turn_begin()
{
	return info_to_battle_sys();
}

info_to_battle_sys game_entity::on_turn_end()
{
	return info_to_battle_sys();
}

vector<buff>::iterator game_entity::find_buff(std::size_t id)
{
	for (auto i = buff_pool.begin(); i != buff_pool.end(); ++i)
	{
		if (i->buff_id == id)
			return i;
	}
	return buff_pool.end();
}

enemy::enemy(data_sys&d) :game_entity(d)
{
}

enemy::~enemy()
{
	//TODO
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
