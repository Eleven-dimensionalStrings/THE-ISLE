#include <string>
#include "message.h"
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
	current_ap = max_ap;
	for (auto &i : data.cards_in_hand)
	{
		i.is_reserve = 0;
	}
	info_to_battle_sys t;
	t.append(action(battle_action_type::DRAW_CARDS, 0, 2));
	for (auto& i : buff_pool)
	{
		t.append(i.on_turn_begin(this));
	}
	//这里调用enemies的on_turn_end

	for (auto& i : data.enemies_data)
	{
		t.append(i.on_turn_end());
	}
	return t;
}

info_to_battle_sys player::on_turn_end()
{
	info_to_battle_sys t;
	for (int i = data.cards_in_hand.size() - 1; i >= 0; --i)
	{
		if (!data.cards_in_hand[i].is_reserve)
		{
			if (data.cards_in_hand[i].vanity)
			{
				t.append(action(battle_action_type::P_REMOVE_A_CARD, &data.player_data, &data.player_data,
					data.cards_in_hand[i].card_type, i));
			}
			else
			{
				t.append(action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &data.player_data, &data.player_data,
					data.cards_in_hand[i].card_type, i));
			}
		}
	}
	for (auto& i : buff_pool)
	{
		t.append(i.on_turn_end(this));
	}
	for (auto& i : data.enemies_data)
	{
		t.append(i.on_turn_begin());
	}
	return t;

}


game_entity::game_entity(data_sys& d) :data(d),
max_hp(10000), current_hp(10000), max_ap(100), current_ap(1)
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
	//TODO

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (!is_alive())
		return info_to_battle_sys();
	info_to_battle_sys result(iaction);
	for (auto i : buff_pool)
	{
		result = i.on_performing(result);
	}

	//now that the potentially triggered changes are added,
	//we have to perform the original action
	action present_act = result.action_set[0];
	result.action_set.erase(result.action_set.begin());
	using namespace type_type;
	if (iaction.action_id == battle_action_type::PERFORMING_ACTION)
	{
		if (present_act.type <= 500)//造成伤害
		{
			current_hp -= static_cast<int>(present_act.value);
			result.append(action(battle_action_type::ENTITY_BE_ATK, present_act.caller, present_act.listener, 0, 0));
			if (current_hp <= 0)
				result.append(this->kill());
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
	}
	return result;

}

info_to_battle_sys game_entity::kill()
{
	return info_to_battle_sys();
}

bool game_entity::is_alive()
{
	if (current_hp <= 0)
		return 0;
	return 1;
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

std::size_t game_entity::has_buff(std::size_t id)
{
	for (int i = 0; i < buff_pool.size(); i++)
	{
		if (buff_pool[i].buff_id == id)
		{
			return buff_pool[i].buff_level;
		}
	}
	return 0;
}

enemy::enemy(data_sys&d, std::size_t id)
	:game_entity(d)
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
	info_to_battle_sys t;
	for (auto& i : buff_pool)
	{
		t.append(i.on_turn_begin(this));
	}


	return t;
}

info_to_battle_sys enemy::on_turn_end()
{
	return info_to_battle_sys();
}
