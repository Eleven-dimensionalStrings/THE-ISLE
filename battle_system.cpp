namespace action_type
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


#include "battle_system.h"
#include <iostream>
#include <sstream>

bool battle_system::send_message(info_to_battle_system input)
{
	battle_system::interpret_message(input);
	//send back something afterwards
}

bool battle_system::interpret_message(info_to_battle_system input)
{
	while (!input.action_id.empty())
	{
		switch (input.action_id.front())
		{
		case action_type::DEALING_DAMAGE:
		{
			explore_system_action next_action(action_type::DEALING_DAMAGE);
			next_action.action_name = input.action_name.front();
			next_action.caller = input.caller.front();
			next_action.listener = input.listener.front();
			next_action.value;//asdlkashlkdhasklfhalksfhasiofhaslkfasf
			process_stack.push(next_action);
			input.next_message();
			break;
		}
		case action_type::RECEIVING_DAMAGE:
		{
			explore_system_action next_action(action_type::RECEIVING_DAMAGE);
			next_action.action_name = input.action_name.front();
			next_action.caller = input.caller.front();
			next_action.listener = input.listener.front();
			next_action.value;//sadklkaskjdhaskjdhkasjdasasdasfasfafasfasf
			process_stack.push(next_action);
			input.next_message();
			break;
		}
		default:
			break;
		}
	}
}

info_to_battle_system battle_system::create_message()
{

}

void battle_system::process()
{
	while (!process_stack.empty())
	{
		explore_system_action temp = process_stack.top();
		process_stack.pop();
		switch (temp.action_id)
		{
		case action_type::DEALING_DAMAGE:
		{
			send_message(temp.caller->deal_damage(temp.value));
			break;
		}
		case action_type::RECEIVING_DAMAGE:
		{
			send_message(temp.listener->receive_damage(temp.value));
			break;
		}
		default:
			break;
		}
	}
}