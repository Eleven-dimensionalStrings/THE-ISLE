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
	t.append(action(battle_action_type::DRAW_CARDS, MEANINGLESS_VALUE, 7));
	for (auto& i : buff_pool)
	{
		t.append(i.on_turn_begin(this));
	}
	for (int i = 0; i < data.enemies_data.size(); ++i)
	{
		data.enemies_data[i].next_act = data.enemy_act(i);
	}
	return t;
}

info_to_battle_sys player::on_turn_end()
{
	info_to_battle_sys temp;
	vector<card>& c_in_hand = data.cards_in_hand;
	vector<card>& c_grave = data.cards_grave;
	for (int i = data.cards_in_hand.size() - 1; i >= 0; --i)
	{
		temp.append(c_in_hand[i].on_turn_end(data));
		if (c_in_hand[i].vanity)
		{
			temp.append(action(battle_action_type::P_REMOVE_A_CARD, &data.player_data, &data.player_data, c_in_hand[i].card_type, i));
		}
		else if (!c_in_hand[i].is_reserve)
		{
			temp.append(action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &data.player_data, &data.player_data,
				c_in_hand[i].card_type, i));
		}
	}
	temp.append(action(battle_action_type::ADD_BUFF, nullptr, &data.player_data, buff_type::PASSED_TURNS, 1));
	data.passed_turns++;
	for (auto& i : buff_pool)
	{
		temp.append(i.on_turn_end(this));
	}
	return temp;

}


game_entity::game_entity(data_sys& d) :data(d),
max_hp(10000), current_hp(10000), max_ap(10), current_ap(10)
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
		if (present_act.type <= 7)
		{
			current_hp -= static_cast<int>(present_act.value);
			if (current_hp <= 0)
				result.append(this->kill());
		}
		else if (present_act.type == ADD_HP)
		{
			current_hp += static_cast<int>(present_act.value);
			if (current_hp > max_hp)
				current_hp = max_hp;
		}
		else if (present_act.type == ADD_AP)
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
	:game_entity(d), enemy_id(id)
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
	info_to_battle_sys t;
	for (auto& i : buff_pool)
	{
		t.append(i.on_turn_end(this));
	}
	return t;
}
