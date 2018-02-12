#include "game_entity.h"
#include "message.h"
#include "managers.h"

bool player::instantiate()
{

}

info_to_battle_system player::deal_damage(game_entity* listener, int value)
{
	//should check buffs and such

	info_to_battle_system result = create_message();
	return result;
}

info_to_battle_system player::receive_damage(game_entity* caller, int value)
{

}

info_to_battle_system player::create_message()
{

}