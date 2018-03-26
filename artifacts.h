#pragma once
#include "message.h"

class artifact
{
public:
	virtual ~artifact();
	virtual info_to_battle_sys on_battle_begin() = 0; // adds buff to the player entity or the enemy entity(s)
	virtual info_to_battle_sys on_exploring() = 0; //has the same working theory as buffs does in battles
	virtual void on_create() = 0;
	virtual void on_delete() = 0;
};