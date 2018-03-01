#pragma once
#include "buff.h"
#include "message.h"
#include <queue>
#include <random>

class message_dispatcher
{
public:
	virtual info_to_battle_sys create_message_to_battle_sys() = 0;
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
	virtual info_to_battle_sys add_buff();
	virtual info_to_battle_sys remove_buff();
	virtual info_to_battle_sys next_turn();
	virtual bool has_buff();
protected:
	//some re-designed container to hold the buffs
	std::vector<buff> buff_list;
};

class random_engine
{
public:
	static random_engine* instantiate_engine();
	static bool random_event(int);
	static int random_battle_cards(int card_generate_value);
private:
	random_engine();
	static std::default_random_engine generator;
};