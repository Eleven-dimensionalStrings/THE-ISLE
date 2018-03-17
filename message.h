#pragma once
#include <cstdlib>
#include "game_entity.h"
#include <vector>
#define MAX_ENEMIES 5
#define MEANINGLESS_VALUE static_cast<unsigned int>(31415926)

namespace battle_action_type
{
	const unsigned int INITIATE = 99;
	const unsigned int NEXT_TURN = 100;
	const unsigned int CALLING_ACTION = 1;
	const unsigned int PERFORMING_ACTION = 2;
	const unsigned int KILL = 5;
	const unsigned int UPGRADE_CARD = 6;
	const unsigned int USE_A_CARD = 23333;//action中type为卡片类型,value为手牌中的第几张卡
	const unsigned int REMOVE_A_CARD = 233333;//将卡除外
	const unsigned int DISCARD_A_CARD = 2333333;//受效果影响弃牌
	const unsigned int ENGRAVE_A_CARD = 23333333;//回合结束时弃牌,不造成其他影响
}



//action里type的具体类别，即伤害、buff的具体类别
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
	//动作的类别，如造成伤害、受到伤害等
	action(std::size_t);
	action(std::size_t id, std::size_t ttype, std::size_t tvalue);
	action(std::size_t id, game_entity* tcaller, game_entity* tlistener, std::size_t ttype, std::size_t tvalue);
	std::size_t action_id;
	game_entity* caller;
	game_entity* listener;

	//伤害、buff的具体类别，如吸血、中毒等
	//it is a change_type value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//when the action_id is associated with buff actions, the value is a buff_type value.
	std::size_t type;

	//value is the damage/healing value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//前两个字节表示buff_life，后两个字节表示buff_level
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





