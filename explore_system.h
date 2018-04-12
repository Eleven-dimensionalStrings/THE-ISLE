#pragma once
#include <string>
#include <stack>
#include <vector>
#include "message.h"
#include "game_entity.h"
class data_sys;

class explore_system
{
public:
	explore_system(data_sys& d);
	void send_message(info_to_explore_sys);
	void update();
private:
	std::stack<e_action> process_stack;
	std::vector<enemy> temp_enemy_list;
	void process();
	data_sys& data;
};

class e_random_engine
{
public:
	size_t get_card_by_id(int id);
	size_t get_card_by_class(int class_id);
};