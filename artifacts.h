#pragma once
#include "message.h"
#include "managers.h"

class artifact : public message_dispatcher
{
public:
	virtual info* on_battle_begin() = 0; // adds buff to the player entity or the enemy entity(s)
	virtual info* on_exploring() = 0; //has the same working theory as buffs does in battles
	virtual void on_create() = 0;
	virtual void on_delete() = 0;
protected:
	virtual info* create_message() = 0;
};