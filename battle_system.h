#pragma once
#include "managers.h"
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

struct action
{
	action(size_t id)
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
	bool send_message(message);
protected:
	message create_message();
	bool interpret_message(message);
private:
	std::stack<action> process_stack;
	void process();
};