#pragma once
#include <ctime>
#include <string>
#include "game_entity.h"
#include "message.h"
#include "container.h"
class data_sys;
class battle_system
{
public:
	battle_system(data_sys& d);
	void update();
	void initiate_battle();
	void send_message(info_to_battle_sys);
	void enemies_action();
	bool battle_fail();
private:
	data_sys & data;
	my_container::my_stack<action> process_stack;
	void deal_an_action();
	void process();
	bool battle_succ();
};

class my_random_engine
{
public:
	static my_container::my_vector<card> shuffle(my_container::my_vector<card>);
	static int get_num(int);
};
