#pragma once
#include "buff.h"
#include "message.h"
#include <queue>

class message_dispatcher
{
protected:
	virtual info* create_message() = 0;
};

class message_listener
{
public:
	virtual bool send_message() = 0;
protected:
	virtual bool interpret_message() = 0;
};

class message_manager : public message_dispatcher, message_listener
{
public:
	virtual bool send_message() = 0;
protected:
	virtual info* create_message() = 0;
	virtual bool interpret_message() = 0;
};

class buff_manager
{
public:
	virtual info_to_battle_system add_buff();
	virtual info_to_battle_system remove_buff();
	virtual info_to_battle_system next_turn();
	virtual bool has_buff();
protected:
	//some re-designed container to hold the buffs
	std::priority_queue<buff*> buff_list;
};
