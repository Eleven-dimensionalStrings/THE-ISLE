#include "battle_system.h"
#include <iostream>
#include <sstream>
using namespace std;
using std::size_t;
bool battle_system::send_message(info_to_battle_sys& input)
{
	battle_system::interpret_message(input);
	//send back something afterwards
}

bool battle_system::interpret_message(info_to_battle_sys& input)
{
	for (size_t i = input.action_id.size() - 1; i >= 0; --i)
	{
		switch (input.action_id[i])
		{
		case battle_action_type::DEALING_DAMAGE:
		{
			battle_system_action next_action(battle_action_type::DEALING_DAMAGE,
			input.action_name[i],input.caller[i],input.listener[i],input.value[i]);
			process_stack.push(next_action);
			break;
		}
		case battle_action_type::RECEIVING_DAMAGE:
		{
			battle_system_action next_action(battle_action_type::RECEIVING_DAMAGE,
			input.action_name[i], input.caller[i], input.listener[i], input.value[i]);
			process_stack.push(next_action);
			break;
		}
		default:
			break;
		}
	}
	delete &input;
}

info* battle_system::create_message()
{

}

void battle_system::process()
{
	while (!process_stack.empty())
	{
		battle_system_action& temp = process_stack.top();
		switch (temp.action_id)
		{
		case battle_action_type::DEALING_DAMAGE:
		{
			send_message(temp.caller->calling_change(temp.value));
			delete temp.value;
			break;
		}
		case battle_action_type::RECEIVING_DAMAGE:
		{
			send_message(temp.listener->receiving_change(temp.value));
			delete temp.value;
			break;
		}
		default:
			break;
		}
		process_stack.pop();
	}
}

battle_system_action::battle_system_action(std::size_t id, std::string tname, game_entity * tcaller, game_entity * tlistener, change tvalue)
	:action_name(tname), caller(tcaller), listener(tlistener), action_id(id), value(tvalue)
{
}
