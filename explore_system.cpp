#include "explore_system.h"
#include "event_cards.h"
#include "message.h"
#include "managers.h"
#include "stack"

using namespace std;

bool explore_system::send_message(info_to_explore_system)
{

}

bool explore_system::interpret_message(info_to_explore_system)
{

}




//the system randomly selects x event cards
//the player interacts with one of the event cards
//the interact system sends a message (using send_message function) to the explore system
//the explore system interprets the message(using the interpret_message function)
//the explore system adds several actions into the process_stack
//the explore system process through the stack
//the explore system should make changes to the values hold in a specific class, let's say player stats class
//the system randomly selects x event cards again