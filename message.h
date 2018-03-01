#pragma once
#include <cstdlib>
#include "game_entity.h"
#include <vector>
//action��type�ľ�����𣬼��˺���buff�ľ������
namespace type_type
{
	const unsigned int NORMAL = 1;
	const unsigned int FLAME = 2;
	const unsigned int PIERCE = 3;
	const unsigned int POISON = 4;
	const unsigned int FREEZING = 5;
	const unsigned int INDEPENDENT = 6;
	const unsigned int ADD_AP = 20000;
	const unsigned int ADD_HP = 20001;
	const unsigned int HEALING = 20002;
}

class action
{
public:
	//���������������˺����ܵ��˺���
	std::size_t action_id;
	std::string action_name;
	game_entity* caller;
	game_entity* listener;

	//�˺���buff�ľ����������Ѫ���ж���
	//it is a change_type value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//when the action_id is associated with buff actions, the value is a buff_type value.
	std::size_t type;

	//value is the damage/healing value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//ǰ�����ֽڱ�ʾbuff_life���������ֽڱ�ʾbuff_level
	std::size_t value;
};

class info
{
public:
	info();
	std::size_t sender_id;
};

class info_to_battle_sys : public info
{
public:
	info_to_battle_sys();
	info_to_battle_sys(action);
	void append(info_to_battle_sys);
	std::vector<action> action_set;
};

class info_to_explore_sys : public info
{
public:
	std::queue<int> value;
};





