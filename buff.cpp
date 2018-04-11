#include "buff.h"
#include "game_entity.h"
#include "data_sys.h"
using namespace std;

void buff::operator--()
{
	--buff_level;
}

void buff::operator--(int t)
{
	--buff_level;
}

void buff::operator+=(buff t)
{
	buff_level += t.buff_level;
}

bool buff::operator-=(buff t)
{
	buff_level -= t.buff_level;
	if (buff_id == buff_type::STRENGTH
		|| buff_id == buff_type::AGILITY
		|| buff_id == buff_type::VITALITY
		|| buff_id == buff_type::RESUSCITATE)
		return 0;
	if (buff_level <= 0)
		return 1;
	return 0;
}
bool buff::operator-(buff t)
{
	if (buff_level <= t.buff_level)
	{
		if (buff_id == buff_type::STRENGTH
			|| buff_id == buff_type::AGILITY
			|| buff_id == buff_type::VITALITY
			|| buff_id == buff_type::RESUSCITATE)
			return 0;
		return 1;
	}
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
	case buff_type::CHAIN:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, c, p, buff_type::STRENGTH, buff_level));
		break;
	}
	case buff_type::STUN:
	{
		result.append(action(battle_action_type::ADD_BUFF, c, p, buff_type::STUN_RESIST, 2));
		break;
	}
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
	case buff_type::CHAIN:
	{
		result.append(action(battle_action_type::ADD_BUFF, c, p, buff_type::STRENGTH, buff_level));
		break;
	}
	default:
		break;
	}
	return result;
}

info_to_battle_sys buff::on_kill(game_entity* p)
{
	info_to_battle_sys result;
	switch (buff_id)
	{
	default:
		result.append(action(battle_action_type::REMOVE_BUFF, nullptr, p, buff_id, buff_level));
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
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_type::ARMOR, 999));
		break;
	}
	case buff_type::POISON:
	{
		if (!p->is_alive())
			break;
		result.append(action(battle_action_type::PERFORMING_ACTION, nullptr, p, type_type::POISON, buff_level));
		result.append(action(battle_action_type::REMOVE_BUFF, buff_id, 1));;
		break;
	}
	case buff_type::USED_ATTACK_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, nullptr, p, buff_id, buff_level));
		break;
	}
	case buff_type::USED_SKILL_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, nullptr, p, buff_id, buff_level));
		break;
	}
	case buff_type::USED_ABILITY_CARDS:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, nullptr, p, buff_id, buff_level));
		break;
	}
	case buff_type::EXHAUST:
	{
		result.append(action(battle_action_type::ADD_BUFF, p, p, buff_type::CHAIN, buff_level));
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::STUN:
	{
		break;//TODO ������ʵ��Ļغ�
	}
	case buff_type::ETERNAL_FURY:
	{
		result.append(action(battle_action_type::ADD_BUFF, p, p, buff_type::STRENGTH, buff_level));
		break;
	}
	case buff_type::FRENZY:
	{
		result.append(action(battle_action_type::CALLING_ACTION, p, p, type_type::PURE, buff_level));
		result.append(action(battle_action_type::DRAW_CARDS, p, p, MEANINGLESS_VALUE, buff_level));
		break;
	}
	case buff_type::RESUSCITATE:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::SCORCHED_EARTH:
	{
		//TODO
		data_sys& d = (dynamic_cast<player*>(p))->data;
		enemy* temp = &d.enemies_data[0];
		for (int i = 0; i < d.enemies_data.size(); i++)
		{
			if (d.enemies_data[i].is_alive())
				result.append(action(battle_action_type::ADD_BUFF, p, temp+i, buff_type::BURN, buff_level));
		}
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
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));;
		break;
	}
	case buff_type::VULNERABLE:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));;
		break;
	}
	case buff_type::FRAGILE:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));;
		break;
	}
	case buff_type::BLEED:
	{
		if (!p->is_alive())
			break;
		result.append(action(battle_action_type::PERFORMING_ACTION, nullptr, p, type_type::BLEED, buff_level));
		break;
	}
	case buff_type::CHAIN:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::MOVE_MUSSLE:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_type::STRENGTH, buff_level));
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::STUN_RESIST:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));;
		break;
	}
	case buff_type::RESUSCITATE:
	{
		result.append(action(battle_action_type::CALLING_ACTION, p, p, type_type::ADD_HP, buff_level));
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
	case buff_type::USED_SKILL_CARDS:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::CALLING_ACTION && i.type == type_type::WAR_12)
				i.value += 6 * buff_level;
			if (i.action_id == battle_action_type::CALLING_ACTION && i.type == type_type::WAR_12_PLUS)
				i.value += 8 * buff_level;
		}
		break;
	}
	case buff_type::ABILITY_BURN:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::CALLING_ACTION && (i.type == type_type::NORMAL
				|| i.type == type_type::FLAME || (i.type > 100 && i.type < 500)))
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, i.caller, i.listener, buff_type::BURN, buff_level));
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
	case buff_type::STUN_RESIST:
	{
		for (int i = 0; i < temp.action_set.size(); i++)
		{
			if (temp.action_set[i].action_id == battle_action_type::ADD_BUFF && temp.action_set[i].type == buff_type::STUN)
				temp.action_set.erase(temp.action_set.begin() + i);
		}
		break;
	}
	case buff_type::INVULNARABLE:
	{
		for (int i = 0; i < temp.action_set.size(); i++)
		{
			if (temp.action_set[i].action_id == battle_action_type::ADD_BUFF && temp.action_set[i].type == buff_type::VULNERABLE)
				temp.action_set.erase(temp.action_set.begin() + i);
		}
		break;
	}
	case buff_type::FIGHTING_SPIRIT:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::P_REMOVE_A_CARD && i.type == card_type::STAT)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, buff_type::STRENGTH, buff_level));
		}
		break;
	}
	case buff_type::RITE:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && i.type == type_type::PURE)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, buff_type::STRENGTH, buff_level));
		}
		break;
	}
	case buff_type::RESUSCITATE:
	{
		for (auto& i : temp.action_set)
		{
			if (i.action_id == battle_action_type::PERFORMING_ACTION && i.type == type_type::PURE)
				buff_level += i.value;
		}
		break;
	}
	default:
		break;
	}
	return temp;
}
