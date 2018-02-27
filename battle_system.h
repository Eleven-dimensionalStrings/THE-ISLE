#pragma once
#include "managers.h"
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>

namespace battle_action_type
{
	const unsigned int INSTANTIATE = 99;
	const unsigned int NEXT_TURN = 100;
	const unsigned int CALLING_CHANGE = 1;
	const unsigned int RECEIVING_CHANGE = 2;
	const unsigned int KILL = 5;
	const unsigned int ADD_BUFF = 11;
	const unsigned int REMOVE_BUFF = 12;
}

struct battle_system_action
{
	battle_system_action(std::size_t id, std::string tname, game_entity* tcaller, game_entity* tlistener,
		change tvalue);
	std::string action_name;
	game_entity* caller;
	game_entity* listener;
	std::size_t action_id;
	change value;
};

class battle_system : public message_manager
{
public:
	bool send_message(info_to_battle_sys&);
protected:
	info * create_message();
	bool interpret_message(info_to_battle_sys&);
private:
	std::stack<battle_system_action> process_stack;
	void process();
};