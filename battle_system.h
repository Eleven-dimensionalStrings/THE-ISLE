#pragma once
#include <ctime>
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

class battle_system
{
public:
	void update();
	bool send_message(info_to_battle_sys);
private:
	bool interpret_message(info_to_battle_sys);
	data_sys & data;
	std::stack<action> process_stack;
	void process();
};