#include "game_entity.h"
#include "message.h"
#include "managers.h"

bool player::instantiate()
{

}

message player::deal_damage(game_entity* listener, int value)
{
	//should check buffs and such

	message result = create_message();
	return result;
}

message player::receive_damage(game_entity* caller, int value)
{

}

message player::create_message()
{

}