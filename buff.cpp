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
		|| buff_id == buff_type::DEXTERITY
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
			|| buff_id == buff_type::DEXTERITY
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
	case buff_type::EXPLODE:
	{
		result.append(action(battle_action_type::CALLING_ACTION, c, p, type_type::INDEPENDENT, buff_level * p->has_buff(buff_type::BURN)));
		result.append(action(battle_action_type::REMOVE_BUFF, nullptr, p, buff_type::EXPLODE, buff_level));
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
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 999));
		break;
	}
	case buff_type::VULNERABLE:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));;
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
		dynamic_cast<enemy*>(p)->next_act.action_set.clear();
		break;
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
		data_sys& d = (dynamic_cast<player*>(p))->data;
		enemy* temp = &d.enemies_data[0];
		for (int i = 0; i < d.enemies_data.size(); i++)
		{
			if (d.enemies_data[i].is_alive())
			{
				temp = &d.enemies_data[i];
				result.append(action(battle_action_type::ADD_BUFF, p, temp, buff_type::BURN, buff_level));
			}
		}
		break;
	}
	case buff_type::LOADED:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::INCREASE_DRAW:
	{
		result.append(action(battle_action_type::DRAW_CARDS, p, p, MEANINGLESS_VALUE, buff_level));
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::REDUCE_AP:
	{
		p->data.player_data.current_ap -= buff_level;
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::INCREASE_AP:
	{
		p->data.player_data.current_ap += buff_level;
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::CULTIST_RITE:
	{
		result.append(action(battle_action_type::ADD_BUFF, p, p, buff_type::STRENGTH, buff_level));
		break;
	}
	case buff_type::PAIN_CURSE:
	{
		result.append(action(battle_action_type::ADD_BUFF, nullptr, p, buff_type::PAIN, buff_level));
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
	case buff_type::STUN:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));
		break;
	}
	case buff_type::STUN_RESIST:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));
		break;
	}
	case buff_type::RESUSCITATE:
	{
		result.append(action(battle_action_type::CALLING_ACTION, p, p, type_type::ADD_HP, buff_level));
		break;
	}
	case buff_type::PAIN:
	{
		result.append(action(battle_action_type::CALLING_ACTION, nullptr, p, type_type::INDEPENDENT, buff_level * p->has_buff(buff_type::USED_ATTACK_CARDS)));
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, buff_level));
		break;
	}
	case buff_type::CORRUPT:
	{
		result.append(action(battle_action_type::CALLING_ACTION, nullptr, p, type_type::INDEPENDENT, buff_level));
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));
		break;
	}
	case buff_type::SHELL:
	{
		result.append(action(battle_action_type::ADD_BUFF, p, p, buff_type::ARMOR, buff_level));
		break;
	}
	case buff_type::MARK:
	{
		result.append(action(battle_action_type::REMOVE_BUFF, p, p, buff_id, 1));
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
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::CALLING_ACTION && (t.type == type_type::NORMAL
				|| t.type == type_type::FLAME || (t.type > 100 && t.type < 500)))
				if (temp.action_set[i].value < -buff_level)
				{
					temp.action_set[i].value = 0;
				}
				else
				{
					temp.action_set[i].value += buff_level;
				}
		}
		break;
	}
	case buff_type::USED_SKILL_CARDS:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::CALLING_ACTION && t.type == type_type::WAR_12)
				temp.action_set[i].value += 6 * buff_level;
			if (t.action_id == battle_action_type::CALLING_ACTION && t.type == type_type::WAR_12_PLUS)
				temp.action_set[i].value += 8 * buff_level;
		}
		break;
	}
	case buff_type::ABILITY_BURN:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::CALLING_ACTION && (t.type == type_type::NORMAL
				|| t.type == type_type::FLAME || (t.type > 100 && t.type < 500)))
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, t.caller, t.listener, buff_type::BURN, buff_level));
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
	case buff_type::DEXTERITY:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && (t.type == type_type::NORMAL
				|| t.type == type_type::FLAME || t.type == type_type::INDEPENDENT || (t.type > 100 && t.type < 500)))
				temp.action_set[i].value -= buff_level;
		}
		break;
	}
	case buff_type::ARMOR:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION
				&& (t.type == type_type::NORMAL ||
					t.type == type_type::FLAME ||
					(t.type > 100 && t.type < 500)))
			{
				if (buff_level > t.value)
				{
					temp.action_set.push_back(action(battle_action_type::REMOVE_BUFF,
						t.caller, t.listener, buff_id, t.value));
					temp.action_set[i].value = 0;
				}
				else
				{
					temp.action_set[i].value -= buff_level;
					temp.action_set.push_back(action(battle_action_type::REMOVE_BUFF,
						t.caller, temp.action_set[i].listener, buff_id, buff_level));
				}
			}
		}
		break;
	}
	case buff_type::VULNERABLE:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && (t.type == type_type::NORMAL
				|| t.type == type_type::FLAME || (t.type > 100 && t.type < 500)))
				temp.action_set[i].value *= 1.5;
		}
		break;
	}
	case buff_type::BURN:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && t.type == type_type::FLAME)
				temp.action_set[i].value += buff_level;
		}
		break;
	}
	case buff_type::FIGHTING_SPIRIT:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::P_REMOVE_A_CARD && t.type == card_type::STAT)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, t.caller, t.listener, buff_type::STRENGTH, buff_level));
		}
		break;
	}
	case buff_type::RITE:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && t.type == type_type::PURE)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, nullptr, t.listener, buff_type::STRENGTH, buff_level));
		}
		break;
	}
	case buff_type::RESUSCITATE:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && t.type == type_type::PURE)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, nullptr, t.listener, buff_id, t.value));
		}
		break;
	}
	case buff_type::ANGER:
	{
		for (int i = 0; i < temp.action_set.size(); ++i)
		{
			action &t = (temp.action_set[i]);
			if (t.action_id == battle_action_type::PERFORMING_ACTION && t.type != type_type::PURE && t.value > 0)
				temp.action_set.push_back(action(battle_action_type::ADD_BUFF, t.listener, t.listener, buff_type::STRENGTH, buff_level));
		}
		break;
	}
	default:
		break;
	}
	return temp;
}

void buff::on_manipulate_buff(action & temp)
{
	switch (buff_id)
	{
	case buff_type::FRAGILE:
	{
		if (temp.action_id == battle_action_type::ADD_BUFF && (temp.type == buff_type::ARMOR))
			temp.value *= 0.5;
		break;
	}
	case buff_type::STUN_RESIST:
	{
		if (temp.action_id == battle_action_type::ADD_BUFF && temp.type == buff_type::STUN)
			temp.value = 0;
		break;
	}
	case buff_type::VITALITY:
	{
		if (temp.action_id == battle_action_type::ADD_BUFF && (temp.type == buff_type::ARMOR))
			temp.value += buff_level;
		break;
	}
	case buff_type::INVULNARABLE:
	{
		if (temp.action_id == battle_action_type::ADD_BUFF && (temp.type == buff_type::VULNERABLE))
			temp.value = 0;
		break;
	}
	default:
		break;
	}
}
