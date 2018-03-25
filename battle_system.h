#pragma once
#include <ctime>
//#include "managers.h"
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
	bool send_message(info_to_battle_sys);//已经没用了
protected:
	info * create_message();//似乎也没用了
	bool interpret_message(info_to_battle_sys);//也已经没用了
private:
	data_sys & data;
	std::stack<action> process_stack;
	void process();
};



//临时使用:
class my_random_engine
{
public:
	static std::vector<card> xipai(std::vector<card>);
};
