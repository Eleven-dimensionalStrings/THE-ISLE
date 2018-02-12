#pragma once
#include "managers.h"
#include "message.h"

//the definition of base class game_entity

class game_entity : public message_dispatcher , buff_manager
{
public:
	virtual bool instantiate() = 0;
	virtual info_to_battle_system deal_damage(damage*) = 0;
	virtual info_to_battle_system receive_damage(damage*) = 0;
	virtual info_to_battle_system acquire_hit_points() = 0;
	virtual info_to_battle_system remove_hit_points() = 0;
	virtual info_to_battle_system kill() = 0;
	virtual info_to_battle_system add_buff() = 0;
	virtual info_to_battle_system remove_buff() = 0;
	virtual info_to_battle_system next_turn() = 0;
	virtual bool has_buff() = 0;
	virtual bool is_alive() = 0;

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;
	virtual info* create_message() = 0;
};


//definition of the player class


class player : public game_entity
{
public:
	virtual bool instantiate();
	virtual info_to_battle_system deal_damage(change_value_set*);
	virtual info_to_battle_system receive_damage(change_value_set*);
	virtual info_to_battle_system acquire_hit_points();
	virtual info_to_battle_system remove_hit_points();
	virtual info_to_battle_system kill();
	virtual info_to_battle_system add_buff();
	virtual info_to_battle_system remove_buff();
	virtual info_to_battle_system next_turn();
	virtual bool has_buff();
	virtual bool is_alive();

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	virtual info_to_battle_system* create_message();
};


//definition of the enemy class


class enemy : public game_entity
{
public:
	virtual bool instantiate();
	virtual info_to_battle_system deal_damage(game_entity*, int);
	virtual info_to_battle_system receive_damage(game_entity*, int);
	virtual info_to_battle_system acquire_hit_points();
	virtual info_to_battle_system remove_hit_points();
	virtual info_to_battle_system kill();
	virtual info_to_battle_system add_buff();
	virtual info_to_battle_system remove_buff();
	virtual info_to_battle_system next_turn();
	virtual bool has_buff();
	virtual bool is_alive();
	virtual bool send_message();

protected:
	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;

	virtual info_to_battle_system* create_message();
	virtual bool interpret_message();
};