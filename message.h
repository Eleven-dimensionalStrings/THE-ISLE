#pragma once
#include <cstdlib>
#include <vector>
#include <queue>
#include <cstddef>
#define MAX_ENEMIES 5
#define MAX_CARDS_IN_HAND 10
#define ETERNAL 10000
#define MEANINGLESS_VALUE static_cast<std::size_t>(31415926)
#define TYPE_TO_P_TYPE static_cast<std::size_t>(100)
class data_sys;
namespace map_mark_type
{
	const int EMPTY = -1;
	const int PLAYER = 0;
	const int UNKNOWN = 1;
	const int KNOWN = 2;
	const int VISITED = 3;
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
	const std::size_t USE_A_CARD = 2333;
	const std::size_t KEEP_A_CARD = 10000;
	const std::size_t REMOVE_A_CARD = 10001;
	const std::size_t DISCARD_A_CARD = 10002;
	const std::size_t DRAW_CARDS = 10003;
	const std::size_t P_KEEP_A_CARD = 10100;
	const std::size_t P_REMOVE_A_CARD = 10101;
	const std::size_t P_DISCARD_A_CARD = 10102;
	const std::size_t ENTITY_BE_ATK = 10300;
	const std::size_t ADD_CARD_TO_HAND = 10400;
	const std::size_t ADD_CARD_TO_DECK = 10500;
	const std::size_t ADD_CARD_TO_DECK_TOP = 10510;
	const std::size_t P_ADD_CARD_TO_DECK_TOP = 10610;
}

namespace event_type
{
	const unsigned int SELECT = 1;
	const unsigned int BATTLE = 2;
	const unsigned int REMOVE_CARDS = 3;
	const unsigned int UPGRADE_CARDS = 4;
	const unsigned int CHANGE_CARDS = 5;
	const unsigned int REMOVE_ARTIFACTS = 6;
	const unsigned int SELECT_NEXT_EVENT = 7;
}

namespace type_type
{
	const std::size_t NORMAL = 1;
	const std::size_t FLAME = 2;
	const std::size_t PIERCE = 3;//穿甲
	const std::size_t POISON = 4;
	const std::size_t BLEEDING = 5;
	const std::size_t PURE = 6;//不受buff影响，穿甲
	const std::size_t INDEPENDENT = 7;//不受buff影响
	const std::size_t ADD_AP = 20000;
	const std::size_t ADD_HP = 20001;
	const std::size_t HEALING = 20002;
}

namespace card_type
{
	const std::size_t STAT = 0;
	const std::size_t ATTACK = 1;
	const std::size_t SKILL = 2;
	const std::size_t ABILITY = 3;
}

namespace buff_type
{
	const std::size_t STRENGTH = 0;
	const std::size_t VULNERABLE = 1;
	const std::size_t POISON = 2;
	const std::size_t WEAK = 3;
	const std::size_t USED_ATTACK_CARDS = 4;
	const std::size_t USED_SKILL_CARDS = 5;
	const std::size_t USED_ABILITY_CARDS = 6;
	const std::size_t EXHAUST = 7;
	const std::size_t CHAIN = 8;
	const std::size_t BURN = 9;
	const std::size_t STUN = 10;
	const std::size_t STUN_RESIST = 11;
	const std::size_t ARMOR = 12;
	const std::size_t MOVE_MUSSLE = 13;
}

namespace window_unit_size
{
	using cstszt = const std::size_t;
	cstszt window_width = 1200;
	cstszt window_height = 720;

	cstszt card_in_hand_up = 500;
	cstszt card_in_hand_down = 720;
	cstszt card_in_hand_left = 0;
	cstszt card_in_hand_right = 900;
	cstszt card_width = 100;
	cstszt card_up = 510;
	cstszt card_down = 710;
	cstszt card_closure = 10;
}
class info_to_battle_sys;
class card
{
public:
	card();
	card(std::size_t id);
	card(const card& copy_card);
	card& operator=(const card& copy_card);


	std::size_t card_id;
	std::string card_name;
	std::size_t card_type;
	std::size_t upgrade_version_id; //0 means the card has no upgrade version(already upgraded);
	std::size_t cost;
	bool is_reserve;
	bool require_target; //true代表需要选择目标，false代表不用
	bool exhaust;//true代表消耗
	bool inherent;//true代表固有

	info_to_battle_sys use_card(data_sys&);
	info_to_battle_sys discard(data_sys&);
	info_to_battle_sys remove(data_sys&);
	info_to_battle_sys on_turn_end(data_sys&);
};




class artifact
{
public:
	//~artifact();
	//info_to_battle_sys on_battle_begin(); // adds buff to the player entity or the enemy entity(s)
	//info_to_battle_sys on_exploring(); //has the same working theory as buffs does in battles
	//void on_create();
	//void on_delete();
};

class game_entity;

class action
{
public:
	action(std::size_t);
	action(std::size_t id, std::size_t ttype, std::size_t tvalue);
	action(std::size_t id, game_entity* tcaller, game_entity* tlistener, std::size_t ttype, std::size_t tvalue);
	std::size_t action_id;
	game_entity* caller;
	game_entity* listener;

	//it is a change_type value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//when the action_id is associated with buff actions, the value is a buff_type value.
	std::size_t type;

	//value is the damage/healing value when action_id is not ADD_BUFF or REMOVE_BUFF.
	//first two bytes buff_life, ....buff_level
	std::size_t value;
};
class explore_selection;

class event_e
{
public:
	std::vector<explore_selection> selection;
	std::vector<event_e> following_event;
	std::string name;
	std::string text;
	std::size_t type;
	std::size_t enemy_type;
};

class explore_selection
{
public:
	explore_selection();
	explore_selection(std::size_t ttype, std::size_t tvalue);
	explore_selection(std::size_t ttype, card tcard);
	explore_selection(std::size_t ttype, artifact tatf);
	explore_selection(std::size_t ttype, event_e tevent);
	explore_selection(std::size_t ttype, std::size_t tvalue, card tcard);
	explore_selection(std::size_t ttype, std::size_t tvalue, artifact tatf);
	std::size_t type;
	std::size_t value;
	artifact atf;
	card selected_card;
	event_e next_event;
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
	info_to_battle_sys(std::vector<action>);
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
	info_explore_to_interacting(std::size_t ttype, std::size_t tnum);
	std::size_t type, num;
	operator bool();
	void clear();
};




class event_card
{
public:
	event_e root;
};







