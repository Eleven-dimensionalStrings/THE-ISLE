#include "buff.h"
#include "game_entity.h"
using namespace std;

void buff::operator--()
{
	--buff_life;
}

void buff::operator--(int)
{
	--buff_life;
}

void buff::operator+=(buff t)
{
	buff_life += t.buff_life;
	buff_level += t.buff_level;
}

bool buff::operator-=(buff & t)
{
	buff_life -= t.buff_life;
	buff_level -= t.buff_level;
	if (buff_life <= 0 || buff_level <= 0)return 1;
	return 0;
}

buff::buff(std::size_t id, std::size_t life, std::size_t level)
	:buff_id(id), buff_name(""), buff_priority(0), buff_life(life), buff_level(level)
{
}

buff::buff(std::size_t id, std::string name, std::size_t priority, std::size_t life, int level)
	: buff_id(id), buff_name(name), buff_priority(priority), buff_life(life), buff_level(level)
{
}

info_to_battle_sys buff::on_create(game_entity* creater, game_entity* receiver)
{
	//switch
	return info_to_battle_sys();
}

info_to_battle_sys buff::on_delete(game_entity *, game_entity *)
{
	//switch
	return info_to_battle_sys();
}

info_to_battle_sys buff::on_kill()
{
	return info_to_battle_sys();
}

info_to_battle_sys buff::on_turn_begin(game_entity*p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	case buff_type::POISON:
	{
		if (buff_life == 0 || !p->is_alive())
			break;
		result.append(action(battle_action_type::PERFORMING_ACTION, nullptr, p, type_type::POISON, buff_level));
		--buff_level;
	}
	default:
		break;
	}
	--buff_life;
	return result;
}

info_to_battle_sys buff::on_turn_end(game_entity*)
{
	return info_to_battle_sys();
}

info_to_battle_sys buff::on_calling(info_to_battle_sys t)
{
	switch (buff_id)
	{
		//≤‚ ‘
	case buff_type::STRENGTH:
	{
		for (auto& i : t.action_set)
		{
			if (i.action_id == battle_action_type::CALLING_ACTION && (i.type == type_type::NORMAL || i.type == type_type::FLAME || i.type == type_type::FREEZING
				|| i.type == type_type::INDEPENDENT || i.type == type_type::PIERCE))
				i.value += buff_level;
		}
		break;
	}
	default:
		break;
	}
	return t;
}

info_to_battle_sys buff::on_performing(info_to_battle_sys t)
{
	switch (buff_id)
	{
	case buff_type::VULNERABLE:
	{
		for (auto& i : t.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && (i.type == type_type::NORMAL || i.type == type_type::FLAME || i.type == type_type::FREEZING
				|| i.type == type_type::INDEPENDENT || i.type == type_type::PIERCE))
				i.value += buff_level;
		}
		break;
	}
	default:
		break;
	}
	return t;
}
