#pragma once
#include "message.h"


class artifact
{
public:
	info* on_battle_begin(); // adds buff to the player entity or the enemy entity(s)
	info* on_exploring(); //has the same working theory as buffs does in battles
	void on_obtaining();
	void on_losing();
};