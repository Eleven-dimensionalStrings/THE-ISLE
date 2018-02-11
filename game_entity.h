#pragma once
#include "handlers.h"
#include "buff.h"
#include <queue>

class game_entity : public message_handler , buff_handler
{
public:
	virtual std::string deal_damage() = 0;
	virtual std::string recieve_damage() = 0;
	virtual std::string acquire_hit_points() = 0;
	virtual std::string remove_hit_points() = 0;
	virtual std::string kill() = 0;
	virtual std::string add_buff() = 0;
	virtual std::string remove_buff() = 0;
	virtual std::string next_turn() = 0;
	virtual bool has_buff() = 0;
	virtual bool is_alive() = 0;
	virtual bool send_message() = 0;

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;
	
	//some re-designed container to hold the buffs
	std::priority_queue<buff> buff_list;

	virtual std::string create_message() = 0;
	virtual bool interpret_message() = 0;
};

class player : public game_entity 
{
public:
	std::string deal_damage();
	std::string recieve_damage();
	std::string acquire_hit_points();
	std::string remove_hit_points();
	std::string kill();
	std::string add_buff();
	std::string remove_buff();
	std::string next_turn();
	bool has_buff();
	bool is_alive();
	bool send_message();

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	//some re-designed container to hold the buffs
	std::priority_queue<buff> buff_list;

	std::string create_message();
	bool interpret_message();
};