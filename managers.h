#pragma once
#include "buff.h"
#include "message.h"
#include <queue>

class message_manager
{
public:
	virtual bool send_message() = 0;
protected:
	virtual message create_message() = 0;
	virtual bool interpret_message() = 0;
};

class buff_manager
{
public:
	virtual message add_buff();
	virtual message remove_buff();
	virtual message next_turn();
	virtual bool has_buff();
protected:
	//some re-designed container to hold the buffs
	std::priority_queue<buff*> buff_list;
};

class event_dispatcher
{
private:
	//some re-designed container to hold the observers
	std::priority_queue<buff> observers;
public:

};

class event_observer
{
	
};