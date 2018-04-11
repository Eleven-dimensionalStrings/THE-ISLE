#include "buff.h"
#include "game_entity.h"
using namespace std;

void buff::operator--()
{
	--buff_level;
}

void buff::operator--(int)
{
	--buff_level;
}

void buff::operator+=(buff t)
{
	buff_level += t.buff_level;
}

bool buff::operator-=(buff & t)
{
	buff_level -= t.buff_level;
	if (buff_id == buff_type::STRENGTH || buff_id == buff_type::AGILITY || buff_id == buff_type::VITALITY)return 0;
	if (buff_level <= 0)return 1;
	return 0;
}

buff::buff(std::size_t id, int level)
	:buff_id(id), buff_name(""), buff_priority(0), buff_level(level)
{
}

buff::buff(std::size_t id, std::string name, std::size_t priority, int level)
	: buff_id(id), buff_name(name), buff_priority(priority), buff_level(level)
{
}

info_to_battle_sys buff::on_create(game_entity* c, game_entity* p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	default:
		break;
	}
	return result;
}

info_to_battle_sys buff::on_delete(game_entity* c, game_entity* p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	default:
		break;
	}
	return result;
}

info_to_battle_sys buff::on_kill()
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	default:
		result.append(action(battle_action_type::REMOVE_BUFF, buff_id, buff_level));
		break;
	}
	return result;
}

info_to_battle_sys buff::on_turn_begin(game_entity* p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	case buff_type::ARMOR:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, buff_type::ARMOR, 999));
		break;
	}
	case buff_type::POISON:
	{
		if (!p->is_alive())
			break;
		result.append(action(battle_action_type::PERFORMING_ACTION, nullptr, p, type_type::POISON, buff_level));
		--buff_level;
		break;
	}
	case buff_type::USED_ATTACK_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, buff_id, buff_level));
		break;
	}
	case buff_type::USED_SKILL_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, buff_id, buff_level));
		break;
	}
	case buff_type::USED_ABILITY_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, buff_id, buff_level));
		break;
	}
	default:
		break;
	}
	return result;
}

info_to_battle_sys buff::on_turn_end(game_entity* p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	case buff_type::WEAK:
	{
		--buff_level;
		break;
	}
	case buff_type::VULNERABLE:
	{
		--buff_level;
		break;
	}
	case buff_type::FRAGILE:
	{
		--buff_level;
		break;
	}
	case buff_type::BLEED:
	{
		if (!p->is_alive())
			break;
		result.append(action(battle_action_type::PERFORMING_ACTION, nullptr, p, type_type::BLEED, buff_level));
		break;
	}
	default:
		break;
	}
	return result;
}

info_to_battle_sys buff::on_calling(info_to_battle_sys temp)
{
	switch (buff_id)
	{
	case buff_type::STRENGTH:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::CALLING_ACTION && (i.type == type_type::NORMAL 
				|| i.type == type_type::FLAME || (i.type > 100 && i.type < 500)))
				i.value += buff_level;
		}
		break;
	}
	case buff_type::VITALITY:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::ADD_BUFF && (i.type == buff_type::ARMOR))
				i.value += buff_level;
		}
		break;
	}
	default:
		break;
	}
	return temp;
}

info_to_battle_sys buff::on_performing(info_to_battle_sys temp)
{
	switch (buff_id)
	{
	case buff_type::AGILITY:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && (i.type == type_type::NORMAL
				|| i.type == type_type::FLAME || i.type == type_type::INDEPENDENT || (i.type > 100 && i.type < 500)))
				i.value -= buff_level;
		}
		break;
	}
	case buff_type::ARMOR:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && (i.type == type_type::NORMAL
				|| i.type == type_type::FLAME || (i.type > 100 && i.type < 500)))
				i.value -= buff_level;
		}
		break;
	}
	case buff_type::FRAGILE:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::ADD_BUFF && (i.type == buff_type::ARMOR))
				i.value *= 0.5;
		}
		break;
	}
	case buff_type::VULNERABLE:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && (i.type == type_type::NORMAL
				|| i.type == type_type::FLAME || (i.type > 100 && i.type < 500)))
				i.value *= 1.5;
		}
		break;
	}
	case buff_type::BURN:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && i.type == type_type::FLAME)
				i.value += buff_level;
		}
		break;
	}
	case buff_type::USED_ATTACK_CARDS:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && i.type == type_type::WAR_12)
				i.value += 6 * buff_level;
			if (i.action_id == battle_action_type::PERFORMING_ACTION && i.type == type_type::WAR_12_PLUS)
				i.value += 8 * buff_level;
			break;
		}
		break;
	}
	default:
		break;
	}
	return temp;
}
