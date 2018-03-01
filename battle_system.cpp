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
	for (size_t i = input.action_set.size() - 1; i >= 0; --i)
	{
		switch (input.action_set[i].action_id)
		{
		case battle_action_type::CALLING_ACTION:
		{
			break;
		}
		case battle_action_type::PERFORMING_ACTION:
		{
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
		action temp = process_stack.top();
		process_stack.pop();
		switch (temp.action_id)
		{
		case battle_action_type::CALLING_ACTION:
		{
			send_message(temp.caller->calling_action(temp));
			break;
		}
		case battle_action_type::PERFORMING_ACTION:
		{
			send_message(temp.listener->performing_action(temp));
			break;
		}
		default:
			break;
		}
		process_stack.pop();
	}
}
