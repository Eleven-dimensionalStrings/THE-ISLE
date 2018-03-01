#pragma once
#include "managers.h"
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

namespace battle_action_type
{
	const unsigned int INITIATE = 99;
	const unsigned int NEXT_TURN = 100;
	const unsigned int CALLING_ACTION = 1;
	const unsigned int PERFORMING_ACTION = 2;
	const unsigned int KILL = 5;
	const unsigned int ADD_BUFF = 11;
	const unsigned int REMOVE_BUFF = 12;
	const unsigned int MULTIPLY_BUFF = 13;
	const unsigned int USE_A_CARD = 233333;
}

class battle_system : public message_manager
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