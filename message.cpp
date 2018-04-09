#include <iostream>
#include "message.h"
#include "data_sys.h"
using namespace std;

info_to_battle_sys::info_to_battle_sys() 
	:info(), action_set()
{
}

info_to_battle_sys::info_to_battle_sys(action ichange)
	:info()
{
	action_set.push_back(ichange);
}

info_to_battle_sys::info_to_battle_sys(vector<action> ichange) :action_set(std::move(ichange))
{
}

void info_to_battle_sys::append(info_to_battle_sys t)
{
	for (auto &i : t.action_set)
	{
		action_set.push_back(i);
	}
}

info::info()
{
}

action::action(std::size_t id) :action_id(id), caller(nullptr), listener(nullptr), type(MEANINGLESS_VALUE), value(MEANINGLESS_VALUE)
{
}

action::action(std::size_t id, std::size_t ttype, std::size_t tvalue)
	: action_id(id), caller(nullptr), listener(nullptr), type(ttype), value(tvalue)
{
}

action::action(std::size_t id, game_entity * tcaller, game_entity * tlistener, std::size_t ttype, std::size_t tvalue)
	: action_id(id), caller(tcaller), listener(tlistener), type(ttype), value(tvalue)
{
}

info_battle_to_interacting::info_battle_to_interacting(std::size_t ttype, std::size_t tnum, bool tis_m)
	: type(ttype), num(tnum), is_m(tis_m)
{
}

info_battle_to_interacting::operator bool()
{
	return (type || num || is_m);
}

void info_battle_to_interacting::clear()
{
	type = num = is_m = 0;
}

info_battle_to_interacting::info_battle_to_interacting()
{

}

e_action::e_action(std::size_t id, std::size_t tvalue)
	:action_id(id), value(tvalue)
{
}

e_action::e_action(std::size_t id, artifact tatf)
	:action_id(id), atf(tatf)
{
}

e_action::e_action(std::size_t id, card tcard)
	:action_id(id), selected_card(tcard)
{
}

e_action::e_action(explore_selection exp_s)
	:selected_card(exp_s.selected_card)
{
	action_id = exp_s.type;
	value = exp_s.value;
	atf = exp_s.atf;
}

info_to_explore_sys::info_to_explore_sys()
	:info(), action_set()
{
}

info_to_explore_sys::info_to_explore_sys(e_action ichange)
	: info()
{
	action_set.push_back(ichange);
}

void info_to_explore_sys::append(info_to_explore_sys t)
{
	for (auto &i : t.action_set)
	{
		action_set.push_back(i);
	}
}

info_explore_to_interacting::info_explore_to_interacting()
{
}

info_explore_to_interacting::info_explore_to_interacting(std::size_t ttype, std::size_t tnum)
	: type(ttype), num(tnum)
{
}

info_explore_to_interacting::operator bool()
{
	return (type || num);
}

void info_explore_to_interacting::clear()
{
	type = num = 0;
}

explore_selection::explore_selection()
{
}

explore_selection::explore_selection(std::size_t ttype, std::size_t tvalue)
	:type(ttype), value(tvalue)
{
}

explore_selection::explore_selection(std::size_t ttype, card tcard)
	:type(ttype), selected_card(tcard)
{
}

explore_selection::explore_selection(std::size_t ttype, artifact tatf)
	: type(ttype), atf(tatf)
{
}

explore_selection::explore_selection(std::size_t ttype, event_e tevent)
	: type(ttype), next_event(tevent)
{
}

explore_selection::explore_selection(std::size_t ttype, std::size_t tvalue, card tcard)
	:type(ttype), value(tvalue), selected_card(tcard)
{
}

explore_selection::explore_selection(std::size_t ttype, std::size_t tvalue, artifact tatf)
	: type(ttype), value(tvalue), atf(tatf)
{
}

card::card()
{
}

card::card(size_t id) 
{
	switch (id)
	{
	case 0:
	{
		card_id = id;
		card_name = "打100";
		card_type = card_type::attack;
		upgrade_version_id = 0;
		cost = 1;
		is_reserve = 0;
		require_target = 1;
		break;
	}
	case 1:
	{
		card_id = id;
		card_name = "100力量";
		card_type = card_type::skill;
		upgrade_version_id = 0;
		cost = 1;
		is_reserve = 0;
		require_target = 0;
		break;
	}
	case 2:
	{
		card_name = "打100";
		card_type = card_type::attack;
		upgrade_version_id = 0;
		cost = 1;
		is_reserve = 0;
		require_target = 1;
	}
	case 3:
	{
		card_name = "打100";
		card_type = card_type::attack;
		upgrade_version_id = 0;
		cost = 1;
		is_reserve = 0;
		require_target = 1;
	}
	case 4:
	{
		card_name = "打100";
		card_type = card_type::attack;
		upgrade_version_id = 0;
		cost = 1;
		is_reserve = 0;
		require_target = 1;
	}
	default:
		break;
	}
}

card::card(const card& copy_card) : is_reserve(copy_card.is_reserve), card_id(copy_card.card_id),
card_name(copy_card.card_name), card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id),
require_target(copy_card.require_target)
{
}

card & card::operator=(const card & c)
{
	this->is_reserve = c.is_reserve;
	this->card_id = c.card_id;
	this->card_name = c.card_name;
	this->card_type = c.card_type;
	this->upgrade_version_id = c.upgrade_version_id;
	this->require_target = c.require_target;
	return *this;
}


info_to_battle_sys card::use_card(data_sys&d)
{
	return d.card_effect(card_id);
}

info_to_battle_sys card::discard(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::remove(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::on_turn_end(data_sys&)
{
	return info_to_battle_sys();
}

