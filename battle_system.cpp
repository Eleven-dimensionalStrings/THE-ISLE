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
		case battle_action_type::DEALING_DAMAGE:
		{
			explore_system_action next_action(battle_action_type::DEALING_DAMAGE);
			next_action.action_name = input.action_name.front();
			next_action.caller = input.caller.front();
			next_action.listener = input.listener.front();
			next_action.value;//asdlkashlkdhasklfhalksfhasiofhaslkfasf
			process_stack.push(next_action);
			input.next_message();
			break;
		}
		case battle_action_type::RECEIVING_DAMAGE:
		{
			explore_system_action next_action(battle_action_type::RECEIVING_DAMAGE);
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

info* battle_system::create_message()
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
		case battle_action_type::DEALING_DAMAGE:
		{
			send_message(temp.caller->deal_damage(temp.value));
			break;
		}
		case battle_action_type::RECEIVING_DAMAGE:
		{
			send_message(temp.listener->receive_damage(temp.value));
			break;
		}
		default:
			break;
		}
	}
}