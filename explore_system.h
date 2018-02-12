#pragma once
#include "message.h"
#include "managers.h"
#include <stack>

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

class explore_system : public message_manager
{
public:
	bool send_message(info_to_explore_system);
protected:
	info* create_message();
	bool interpret_message(info_to_explore_system);
private:
	std::stack<explore_system_action> process_stack;
	void process();
};