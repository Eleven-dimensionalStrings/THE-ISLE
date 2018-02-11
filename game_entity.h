#pragma once
#include "managers.h"
#include "message.h"

//the definition of base class game_entity

class game_entity : public message_manager , buff_manager
{
public:
	virtual bool instantiate() = 0;
	virtual message deal_damage(damage*) = 0;
	virtual message receive_damage(damage*) = 0;
	virtual message acquire_hit_points() = 0;
	virtual message remove_hit_points() = 0;
	virtual message kill() = 0;
	virtual message add_buff() = 0;
	virtual message remove_buff() = 0;
	virtual message next_turn() = 0;
	virtual bool has_buff() = 0;
	virtual bool is_alive() = 0;
	virtual bool send_message() = 0;

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	virtual message create_message() = 0;
	virtual bool interpret_message() = 0;
};


//definition of the player class


class player : public game_entity
{
public:
	virtual bool instantiate();
	virtual message deal_damage(change_value_set*);
	virtual message receive_damage(change_value_set*);
	virtual message acquire_hit_points();
	virtual message remove_hit_points();
	virtual message kill();
	virtual message add_buff();
	virtual message remove_buff();
	virtual message next_turn();
	virtual bool has_buff();
	virtual bool is_alive();
	virtual bool send_message();

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	virtual message create_message();
	virtual bool interpret_message();
};


//definition of the enemy class


class enemy : public game_entity
{
public:
	virtual bool instantiate();
	virtual message deal_damage(game_entity*, int);
	virtual message receive_damage(game_entity*, int);
	virtual message acquire_hit_points();
	virtual message remove_hit_points();
	virtual message kill();
	virtual message add_buff();
	virtual message remove_buff();
	virtual message next_turn();
	virtual bool has_buff();
	virtual bool is_alive();
	virtual bool send_message();

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	virtual message create_message();
	virtual bool interpret_message();
};