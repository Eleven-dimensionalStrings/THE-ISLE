#include "message.h"
using namespace std;

info_to_battle_sys::info_to_battle_sys() :info(), action_set()
{
}

info_to_battle_sys::info_to_battle_sys(action ichange)
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