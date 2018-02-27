#include "message.h"
using namespace std;

info_to_battle_sys::info_to_battle_sys() :info(), caller(), listener(), value()
{
}

info_to_battle_sys::info_to_battle_sys(change)
{
}

void info_to_battle_sys::append(info_to_battle_sys t)
{
	for (int i = 0; i < t.action_id.size(); ++i)
	{
		action_id.push_back(t.action_id[i]);
		action_name.push_back(t.action_name[i]);
		caller.push_back(t.caller[i]);
		listener.push_back(t.listener[i]);
		value.push_back(t.value[i]);
	}
}

info::info() :action_id(), action_name()
{
}
