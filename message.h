#pragma once
#include <cstdlib>
#include "game_entity.h"
#include <vector>
namespace change_type
{
	const unsigned int NORMAL = 1;
	const unsigned int FLAME = 2;
	const unsigned int PIERCE = 3;
	const unsigned int POISON = 4;
	const unsigned int FREEZING = 5;
	const unsigned int INDEPENDENT = 6;
	const unsigned int HEALING = 65535;
}


class info
{
public:
	info();
	std::size_t sender_id;
	std::vector<std::size_t> action_id;
	std::vector<std::string> action_name;
};

class info_to_battle_sys : public info
{
public:
	info_to_battle_sys();
	info_to_battle_sys(change);
	void append(info_to_battle_sys);
	std::vector<game_entity*> caller;
	std::vector<game_entity*> listener;
	std::vector<change> value;
};

class info_to_explore_system : public info
{
public:
	std::queue<int> value;
};

class change
{
public:
	std::size_t value;
	std::size_t type;
};


//battle_system 调用攻击者的 deal_damage(damage*)
//攻击者的deal_damage函数遍历攻击者的buff_list
//攻击者把damage类对象中间的某些数值提取出来，修改，然后重新封装到一个新的message里面
//攻击者的deal_damage函数返回一个message


