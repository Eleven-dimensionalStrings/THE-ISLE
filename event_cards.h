#pragma once
#include "message.h"
#include "managers.h"

class event_cards : public event_dispatcher
{
public:
	virtual info_to_explore_system activate();
protected:
	virtual info* create_message() = 0;
}; 
	
