#pragma once
#include "message.h"
#include "managers.h"

class event_cards : public message_dispatcher
{
public:
	virtual info_to_explore_sys activate();
protected:
	virtual info* create_message() = 0;
}; 
	
