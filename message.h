#pragma once

namespace change_value_type
{
	const int DAMAGE = 1;
	const int HEALING = 2;
}

namespace damage_type
{
	const int NORMAL = 1;
	const int FLAME = 2;
	const int LEECH = 3;
	const int PIERCE = 4;
}

#include "game_entity.h"
#include <queue>

class info
{
public:
	size_t sender_id;
	std::queue<size_t> action_id;
	std::queue<std::string> action_name;
	virtual void next_message() = 0;
};

class info_to_battle_system : public info
{
public:
	std::queue<game_entity*> caller;
	std::queue<game_entity*> listener;
	std::queue<int> value;
	void next_message()
	{
		action_id.pop();
		action_name.pop();
		caller.pop();
		listener.pop();
		value.pop();
	}
};

class info_to_explore_system : public info
{
public:
	std::queue<int> value;
	void next_message()
	{
		action_id.pop();
		action_name.pop();
		value.pop();
	}
};

class change_value_set
{
public:
	game_entity* caller;
	game_entity* listener;
	int value;
};

class damage : public change_value_set
{
public:
	std::vector<std::pair<size_t, double>> sss; // TO BE renamed
	size_t get_type()
	{
		return change_value_type::DAMAGE;
	}
};

class healing : public change_value_set
{
public:
	size_t get_type()
	{
		return change_value_type::HEALING;
	}
};

//battle_system 调用攻击者的 deal_damage(damage*)
//攻击者的deal_damage函数遍历攻击者的buff_list
//攻击者把damage类对象中间的某些数值提取出来，修改，然后重新封装到一个新的message里面
//攻击者的deal_damage函数返回一个message


