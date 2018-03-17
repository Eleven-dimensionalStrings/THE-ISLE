#pragma once
#include "managers.h"
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

class battle_system : public message_listener
{
public:
	bool send_message(info_to_battle_sys&);
protected:
	info * create_message();
	bool interpret_message(info_to_battle_sys&);
private:
	std::stack<action> process_stack;
	void process();
};