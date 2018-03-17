#pragma once
#include <cstdlib>
#include "game_entity.h"
#include <vector>
#define MAX_ENEMIES 5
#define MEANINGLESS_VALUE static_cast<unsigned int>(31415926)
#define TYPE_TO_P_TYPE static_cast<unsigned int>(100)

namespace battle_action_type
{
	const unsigned int INITIATE = 99;
	const unsigned int NEXT_TURN = 100;
	const unsigned int CALLING_ACTION = 1;
	const unsigned int PERFORMING_ACTION = 2;
	const unsigned int KILL = 5;
	const unsigned int UPGRADE_CARD = 6;
	const unsigned int USE_A_CARD = 2333;//action��typeΪ��Ƭ����,valueΪ�����еĵڼ��ſ�
	//������˸�action��,typeֱ�ӱ�ʾ�Ƿ�ǿ��ѡ����ô���ſ�
	//������ʹ�ÿ�Ƭʱ�õ���action
	const unsigned int KEEP_A_CARD = 10000;//�غϽ���ʱ�������ſ�
	const unsigned int REMOVE_A_CARD = 10001;//��������
	const unsigned int DISCARD_A_CARD = 10002;//��Ч��Ӱ������
	const unsigned int ENGRAVE_A_CARD = 10003;//�غϽ���ʱ����,���������Ӱ��
	//�����P����perform,����interactingѡ�꿨Ƭ�󴫻�ս��ϵͳ,ִ�о��������
	const unsigned int P_KEEP_A_CARD = 10100;//�غϽ���ʱ�������ſ�
	const unsigned int P_REMOVE_A_CARD = 10101;//��������
	const unsigned int P_DISCARD_A_CARD = 10102;//��Ч��Ӱ������
	const unsigned int P_ENGRAVE_A_CARD = 10103;//�غϽ���ʱ����,���������Ӱ��
}



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
	const unsigned int ADD_BUFF = 11;
	const unsigned int REMOVE_BUFF = 12;
	const unsigned int MULTIPLY_BUFF = 13;
}

class action
{
public:
	//���������������˺����ܵ��˺���
	action(std::size_t);
	action(std::size_t id, std::size_t ttype, std::size_t tvalue);
	action(std::size_t id, game_entity* tcaller, game_entity* tlistener, std::size_t ttype, std::size_t tvalue);
	std::size_t action_id;
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

class info_battle_to_interacting :public info
{
public:
	info_battle_to_interacting();
	info_battle_to_interacting(std::size_t ttype, std::size_t tnum, bool tis_m);
	std::size_t type, num;
	bool is_m;
	operator bool();
	void clear();
};





