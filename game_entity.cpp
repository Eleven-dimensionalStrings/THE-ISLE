#include <string>
#include "message.h"
#include "battle_system.h"
#include "game_entity.h"
#include "data_sys.h"
using namespace std; using namespace my_container;
using std::size_t;

player::player(data_sys &d) :game_entity(d)
{
}

player::~player()
{
}

void player::initiate(my_container::my_vector<card>&card_pool, my_container::my_vector<artifact>&artifact_list)
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
	t.append(action(battle_action_type::DRAW_CARDS, MEANINGLESS_VALUE, 4));
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
	my_vector<card>& c_in_hand = data.cards_in_hand;
	my_vector<card>& c_grave = data.cards_grave;
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
max_hp(80), current_hp(80), max_ap(3), current_ap(3)
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
		if (present_act.type <= 200)
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

my_vector<buff>::iterator game_entity::find_buff(std::size_t id)
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
	max_ap = 0;
	current_ap = 0;
	switch (enemy_id)
	{
	case 1:
		max_hp = current_hp = 20;
	case 2:
		max_hp = current_hp = 15;
	case 3:
		max_hp = current_hp = 18;
	case 4:
		max_hp = current_hp = 30;
	case 5:
		max_hp = current_hp = 60;
	case 6:
		max_hp = current_hp = 18;
	case 7:
		max_hp = current_hp = 25;
	case 8:
		max_hp = current_hp = 20;
	case 9:
		max_hp = current_hp = 20;
	case 10:
		max_hp = current_hp = 25;
	case 11:
		max_hp = current_hp = 80;
	case 12:
		max_hp = current_hp = 22;
	case 13:
		max_hp = current_hp = 24;
	case 14:
		max_hp = current_hp = 16;
	case 15:
		max_hp = current_hp = 20;
	case 16:
		max_hp = current_hp = 50;
	case 17:
		max_hp = current_hp = 48;
	case 18:
		max_hp = current_hp = 15;
	case 19:
		max_hp = current_hp = 18;
	case 20:
		max_hp = current_hp = 18;
	case 21:
		max_hp = current_hp = 15;
	case 22:
		max_hp = current_hp = 20;
	case 23:
		max_hp = current_hp = 35;
	case 24:
		max_hp = current_hp = 14;
	case 25:
		max_hp = current_hp = 77;
	case 26:
		max_hp = current_hp = 33;
	case 27:
		max_hp = current_hp = 23;
	case 28:
		max_hp = current_hp = 30;
	case 29:
		max_hp = current_hp = 20;
	case 30:
		max_hp = current_hp = 48;
	case 31:
		max_hp = current_hp = 10;
	case 32:
		max_hp = current_hp = 40;
	case 33:
		max_hp = current_hp = 12;
	case 34:
		max_hp = current_hp = 12;
	case 35:
		max_hp = current_hp = 50;
	case 36:
		max_hp = current_hp = 12;
	case 37:
		max_hp = current_hp = 22;
	case 38:
		max_hp = current_hp = 25;
	case 39:
		max_hp = current_hp = 8;
	case 40:
		max_hp = current_hp = 70;
	case 41:
		max_hp = current_hp = 14;
	case 42:
		max_hp = current_hp = 25;
	case 43:
		max_hp = current_hp = 15;
	case 44:
		max_hp = current_hp = 40;
	case 45:
		max_hp = current_hp = 80;
	case 46:
		max_hp = current_hp = 8;
	case 47:
		max_hp = current_hp = 30;
	case 48:
		max_hp = current_hp = 60;
	case 49:
		max_hp = current_hp = 13;
	default:
		max_hp = current_hp = 45;
	}
}

enemy::~enemy()
{
}


void enemy::initiate(my_container::my_vector<card>& card_pool, my_container::my_vector<artifact>& artifact_list)
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
