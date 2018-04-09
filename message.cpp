#include "message.h"
#include "artifacts.h"
#include "cards.h"
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
