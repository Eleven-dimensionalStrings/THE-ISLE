#pragma once
#include <array>
#include "message.h"
#include "buff.h"
class data_sys;
//the definition of base class game_entity

class game_entity
{
public:
	game_entity(data_sys&);
	virtual ~game_entity();
	virtual void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list) = 0;
	info_to_battle_sys calling_action(action);
	info_to_battle_sys performing_action(action);
	virtual info_to_battle_sys kill() = 0;
	bool is_alive();
	virtual info_to_battle_sys on_turn_begin() = 0;
	virtual info_to_battle_sys on_turn_end() = 0;
	std::vector<buff>::iterator find_buff(std::size_t id);

	data_sys& data;
	int max_hp;
	int current_hp;
	int max_ap;
	int current_ap;
	std::vector<buff> buff_pool;

};


//definition of the player class


class player : public game_entity
{
public:
	player(data_sys&);
	virtual ~player();
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)override;
	info_to_battle_sys kill()override;
	info_to_battle_sys on_turn_begin()override;
	info_to_battle_sys on_turn_end()override;
};


//definition of the enemy class


class enemy : public game_entity
{
public:
	enemy(data_sys&);
	virtual ~enemy();
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list)override;
	virtual info_to_battle_sys kill()override;
	info_to_battle_sys on_turn_begin()override;
	info_to_battle_sys on_turn_end()override;
};