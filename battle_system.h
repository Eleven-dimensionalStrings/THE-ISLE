#pragma once
#include <ctime>
#include "game_entity.h"
#include "message.h"
#include <stack>
#include <string>
class data_sys;
class battle_system
{
public:
	battle_system(data_sys& d);
	void update();
	void send_message(info_to_battle_sys);
private:
	data_sys & data;
	std::stack<action> process_stack;
	void process();
	bool battle_succ();
};

class my_random_engine
{
public:
	static std::vector<card> xipai(std::vector<card>);
};
