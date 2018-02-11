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

struct message
{
	size_t sender_id;
	std::queue<size_t> action_id;
	std::queue<std::string> action_name;
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

//battle_system ���ù����ߵ� deal_damage(damage*)
//�����ߵ�deal_damage�������������ߵ�buff_list
//�����߰�damage������м��ĳЩ��ֵ��ȡ�������޸ģ�Ȼ�����·�װ��һ���µ�message����
//�����ߵ�deal_damage��������һ��message


