#pragma once
#include <cstdlib>
#include <vector>
#include <queue>
#define MAX_ENEMIES 5
#define MEANINGLESS_VALUE static_cast<std::size_t>(31415926)
#define TYPE_TO_P_TYPE static_cast<std::size_t>(100)

namespace map_mark_type
{
	const int EMPTY = -1;
	const int PLAYER = 0;//玩家所处位置
	const int UNKNOWN = 1;//没有去过
	const int KNOWN = 2;//已经翻开，但是没有去过
	const int VISITED = 3;//已经去过
}

namespace battle_action_type
{
	const std::size_t INITIATE = 99;
	const std::size_t TURN_BEGIN = 100;
	const std::size_t TURN_END = 101;
	const std::size_t CALLING_ACTION = 1;
	const std::size_t PERFORMING_ACTION = 2;
	const std::size_t KILL = 5;
	const std::size_t UPGRADE_CARD = 6;
	const std::size_t ADD_BUFF = 11;
	const std::size_t REMOVE_BUFF = 12;
	const std::size_t MULTIPLY_BUFF = 13;
	const std::size_t USE_A_CARD = 2333;//action中type为卡片类型,value为手牌中的第几张卡
	//在下面八个action中,type直接表示是否强制选满那么多张卡
	//下面是使用卡片时得到的action
	const std::size_t KEEP_A_CARD = 10000;//回合结束时保留这张卡
	const std::size_t REMOVE_A_CARD = 10001;//将卡除外
	const std::size_t DISCARD_A_CARD = 10002;//受效果影响弃牌
	const std::size_t DRAW_CARDS = 10003;//抽卡,value表示抽多少张,遍历buff的操作在on_calling执行
	//下面的P代表perform,是在interacting选完卡片后传回战斗系统,执行具体操作的
	const std::size_t P_KEEP_A_CARD = 10100;//回合结束时保留这张卡
	const std::size_t P_REMOVE_A_CARD = 10101;//将卡除外
	const std::size_t P_DISCARD_A_CARD = 10102;//受效果影响弃牌
	const std::size_t ENTITY_BE_ATK = 10300;//实体收到攻击,再由battle传递消息给draw
}



//action里type的具体类别，即伤害、buff的具体类别
namespace type_type
{
	const std::size_t NORMAL = 1;
	const std::size_t FLAME = 2;
	const std::size_t PIERCE = 3;
	const std::size_t POISON = 4;
	const std::size_t FREEZING = 5;
	const std::size_t INDEPENDENT = 6;
	const std::size_t ADD_AP = 20000;
	const std::size_t ADD_HP = 20001;
	const std::size_t HEALING = 20002;
}

namespace buff_type
{
	const std::size_t STRENGTH = 0;
	const std::size_t VULNERABLE = 1;//易伤
	const std::size_t POISON = 2;//易伤
}

namespace window_unit_size
{
	using cstszt = const std::size_t;
	cstszt window_width = 1200;
	cstszt window_height = 720;
	//手牌区域
	cstszt card_in_hand_up = 500;
	cstszt card_in_hand_down = 720;
	cstszt card_in_hand_left = 0;
	cstszt card_in_hand_right = 900;
	cstszt card_width = 100;//每张牌的宽度
	cstszt card_up = 510;//牌的位置
	cstszt card_down = 710;
	cstszt card_closure = 10;
}

class game_entity;

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
	info_to_battle_sys(std::vector<action>);
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





