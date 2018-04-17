#pragma once
#include <array>
#include <string>
#include <vector> 
#include <map>
#include <functional>
#include "game_entity.h"
class battle_system;

class random_engine
{
public:
	random_engine(data_sys *d);
	size_t get_num(int lb, int ub);
	size_t get_enemy();
	size_t get_other_enemy(int pos);
	bool chance(std::size_t c);
	bool chance_luck_increase(std::size_t c);
	bool chance_luck_decrease(std::size_t c);
	data_sys* data;
};

class data_sys
{
public:
	data_sys();
	info_to_battle_sys card_effect(std::size_t id);
	info_to_battle_sys card_remove(std::size_t id);
	info_to_battle_sys card_discard(std::size_t id);
	info_to_battle_sys card_on_turn_end(std::size_t id);
	info_to_explore_sys event_effect(std::size_t event_id);
	info_to_battle_sys enemy_battle_start(std::size_t enemy_id);//TODO
	info_to_battle_sys enemy_act(std::size_t enemy_id);
	std::vector<card> cards_pool;
	std::vector<artifact> artifacts;
	std::map<std::size_t, std::size_t> card_upgrade_id;
	std::map<std::size_t, std::string> card_name;
	player player_data;
	std::vector<enemy> enemies_data;
	enemy all_enemies, random_enemy, select_one_enemy;
	std::pair<std::string, std::size_t> get_buff(std::size_t);

	battle_system* b;
	std::size_t gold;
	std::size_t food;
	std::size_t strength;
	std::size_t dexterity;
	std::size_t vitality;
	std::size_t luck;
	std::vector<card> cards_deck;
	std::vector<card> cards_grave;
	std::vector<card> cards_in_hand;
	std::vector<card> cards_removed;
	std::vector<card> cards_equiped;
	std::array<bool, MAX_CARDS_IN_HAND>render_select_card;
	info_to_battle_sys i_to_b_pipe;
	info_battle_to_interacting b_to_i_pipe;
	info_to_explore_sys i_to_e_pipe;
	info_explore_to_interacting e_to_i_pipe;
	info_to_battle_sys e_to_b_pipe;
	info_to_explore_sys b_to_e_pipe;
	std::vector<std::pair<std::size_t, std::size_t>>b_to_d;
	std::size_t explore_map[MAP_LENGTH][MAP_WIDTH];
	int map_marks[MAP_LENGTH][MAP_WIDTH];
	std::pair<int, int> player_location;
	std::vector<e_action> choice_list;
	std::vector<std::string> choice_name_list;
	std::string text_to_be_displayed;
	std::string map_text;
	//to determine explore context
	std::size_t current_select_page;//indicates the position of the first selection in choice_list.  
	bool is_vaccant;
	bool is_battle;
	std::size_t next_event_id;//for "SKIP" button
	std::size_t player_s_class;
	std::size_t passed_turns;
	bool has_other_enemy(std::size_t pos);
	bool event_is_not_mandetory;
	random_engine re;

	//TODO for artifacts
	info_to_explore_sys artifact_on_create(std::size_t atf_id);
	info_to_explore_sys artifact_on_remove(std::size_t atf_id);
	info_to_explore_sys artifact_on_encounter_event(std::size_t atf_id);
	info_to_explore_sys artifact_on_event_body(std::size_t atf_id);
	info_to_battle_sys artifact_on_start_battle(std::size_t atf_id);
	info_to_explore_sys artifact_on_end_event(std::size_t atf_id);
};

