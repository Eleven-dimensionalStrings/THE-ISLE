#pragma once
#include "managers.h"
#include "message.h"
#include "cards.h"
#include "artifacts.h"
#include "buff.h"

//the definition of base class game_entity

class game_entity : public message_dispatcher, buff_manager
{
public:
	virtual void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list) = 0;
	virtual info_to_battle_sys calling_change(change);
	virtual info_to_battle_sys receiving_change(change);
	virtual info_to_battle_sys kill() = 0;
	virtual info_to_battle_sys add_buff(buff t);
	virtual info_to_battle_sys remove_buff(std::size_t buff_id);
	bool is_alive();
	virtual info_to_battle_sys on_turn_begin() = 0;
	virtual info_to_battle_sys on_turn_end() = 0;


	bool living_state;
	int max_hit_points;
	int current_hit_points;
	int max_action_points;
	int current_action_points;
	std::vector<card> cards_deck;//战斗时牌库
	std::vector<card> cards_grave;//弃牌堆
	std::vector<card> cards_in_hand;//手牌
	std::vector<card> cards_removed;//除外区
	std::vector<card> cards_equiped;//装备区
	std::vector<buff> buff_pool;//buff区
	virtual info_to_battle_sys create_message_to_battle_sys() = 0;
};


//definition of the player class


class player : public game_entity
{
public:
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list);
	info_to_battle_sys kill();
	info_to_battle_sys on_turn_begin();
	info_to_battle_sys on_turn_end();
	//bool has_buff();
	std::size_t gold;
	std::size_t food;

	info_to_battle_sys create_message_to_battle_sys();
};


//definition of the enemy class


class enemy : public game_entity
{
public:
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list);
	virtual info_to_battle_sys kill();
	virtual info_to_battle_sys next_turn();
	virtual bool has_buff();
	virtual bool send_message();
	info_to_battle_sys on_turn_begin();
	info_to_battle_sys on_turn_end();

	info_to_battle_sys create_message_to_battle_sys();
};