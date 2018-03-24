#pragma once
#include "message.h"
#include "managers.h"

class event_cards
{
public:
	virtual info_to_explore_sys activate() = 0;
protected:
	virtual info* create_message() = 0;
};

