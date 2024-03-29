#pragma once
#include <string>
#include "container.h"
#include <random>
#include <time.h>
#include "message.h"
#include "game_entity.h"
class data_sys;

class explore_system
{
public:
	explore_system(data_sys& d);
	void send_message(info_to_explore_sys);
	void update();
	void end_battle();
	void create_map(std::size_t map_type = 0);
private:
	my_container::my_stack<e_action> process_stack;
	std::size_t max_selection;
	void process();
	data_sys& data;
};

class e_random_engine
{
public:
	e_random_engine();
	std::default_random_engine egn;
	size_t get_card_by_id(int id);
	size_t get_card_by_class(int class_id);
	size_t get_event(std::size_t map_type = 0);
};