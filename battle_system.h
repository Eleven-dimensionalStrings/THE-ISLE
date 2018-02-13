#pragma once
#include "managers.h"
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

namespace battle_action_type
{
	const int INSTANTIATE = 99;
	const int NEXT_TURN = 100;
	const int DEALING_DAMAGE = 1;
	const int RECEIVING_DAMAGE = 2;
	const int AQUIREING_HITPOINTS = 3;
	const int REMOVING_HITPOINTS = 4;
	const int KILL = 5;
	const int ADD_BUFF = 11;
	const int REMOVE_BUFF = 12;
}


struct explore_system_action
{
	explore_system_action(size_t id)
		:action_name(" "), caller(NULL), listener(NULL), action_id(id), value()
	{};
	std::string action_name;
	game_entity* caller;
	game_entity* listener;
	size_t action_id;
	change_value_set* value;
};

class battle_system : public message_manager
{
public:
	bool send_message(info_to_battle_system);
protected:
	info* create_message();
	bool interpret_message(info_to_battle_system);
private:
	std::stack<explore_system_action> process_stack;
	void process();
};