#pragma once
#include <cstdlib>
#include "game_entity.h"
#include "cards.h"
#include <vector>
#define MAX_ENEMIES 5
#define MEANINGLESS_VALUE static_cast<unsigned int>(31415926)
#define TYPE_TO_P_TYPE static_cast<unsigned int>(100)

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
	const unsigned int INITIATE = 99;
	const unsigned int TURN_BEGIN = 100;
	const unsigned int TURN_END = 101;
	const unsigned int CALLING_ACTION = 1;
	const unsigned int PERFORMING_ACTION = 2;
	const unsigned int KILL = 5;
	const unsigned int UPGRADE_CARD = 6;
	const unsigned int USE_A_CARD = 2333;//action中type为卡片类型,value为手牌中的第几张卡
	//在下面八个action中,type直接表示是否强制选满那么多张卡
	//下面是使用卡片时得到的action
	const unsigned int KEEP_A_CARD = 10000;//回合结束时保留这张卡
	const unsigned int REMOVE_A_CARD = 10001;//将卡除外
	const unsigned int DISCARD_A_CARD = 10002;//受效果影响弃牌
	const unsigned int DRAW_CARDS = 10003;//抽卡,value表示抽多少张,遍历buff的操作在on_calling执行
	//下面的P代表perform,是在interacting选完卡片后传回战斗系统,执行具体操作的
	const unsigned int P_KEEP_A_CARD = 10100;//回合结束时保留这张卡
	const unsigned int P_REMOVE_A_CARD = 10101;//将卡除外
	const unsigned int P_DISCARD_A_CARD = 10102;//受效果影响弃牌
}

namespace event_type
{
	const unsigned int select = 1;
	const unsigned int battle = 2;
	const unsigned int select_from_cards = 3;
	const unsigned int select_from_artifacts = 4;
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

class e_action
{
public:
	e_action(std::size_t id, std::size_t tvalue);
	e_action(std::size_t id, artifact tatf);
	e_action(std::size_t id, card tcard);
	e_action(explore_selection exp_s);
	std::size_t action_id;
	std::size_t value;
	artifact atf;
	card selected_card;
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
	info_to_explore_sys();
	info_to_explore_sys(e_action);
	void append(info_to_explore_sys);
	std::vector<e_action> action_set;
};

class info_battle_to_interacting : public info
{
public:
	info_battle_to_interacting();
	info_battle_to_interacting(std::size_t ttype, std::size_t tnum, bool tis_m);
	std::size_t type, num;
	bool is_m;
	operator bool();
	void clear();
};

class info_explore_to_interacting : public info
{
public:
	info_explore_to_interacting();
	info_explore_to_interacting(std::size_t ttype, std::size_t tnum, bool tis_m);
	std::size_t type, num;
	bool is_m;
	operator bool();
	void clear();
};

//explore_selection 是可以选择的选项
class explore_selection
{
public:
	std::size_t type;
	std::size_t value;
	artifact atf;
	card selected_card;
	event_e next_event;
};

//event_e 是事件树的一个节点
class event_e
{
public:
	std::vector<explore_selection> selection;//选择/多项选择事件的选项
	std::vector<event_e> following_event;//后续的分支事件
	std::string name;//事件的名字（选项的的名字）
	std::string text;//显示的事件剧情
	std::size_t type;//事件的种类（战斗，选择，多项选择）
	std::size_t enmey_type;//战斗事件的敌人种类
};

//event_card 是事件卡，就是一棵事件树
class event_card
{
public:
	event_e root;
};

