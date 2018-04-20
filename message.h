#pragma once
#include <cstdlib>
#include <vector>
#include <queue>
#include <cstddef>
#include <string>
#define MAX_ENEMIES 5
#define MAP_LENGTH 13
#define MAP_WIDTH 5
#define MAX_CARDS_IN_HAND 7
#define MEANINGLESS_VALUE static_cast<std::size_t>(31415926)
#define TYPE_TO_P_TYPE static_cast<std::size_t>(100)
#define MAX_ARTIFACT_NO 20 //TODO
#define END 9999

#undef PURE
//a fucking sb define PURE without namespace or other protect

namespace map_mark_type
{
	const int EMPTY = 0;
	const int PLAYER = 2;
	const int UNKNOWN = 3;
	const int KNOWN = 5;
	const int VISITED = 6;
}

namespace explore_action_type
{
	const std::size_t ENCOUNTER_EVENT = 94;
	const std::size_t EVENT_BODY = 95;
	const std::size_t SELECTION = 96;
	const std::size_t MAX_SELECTION = 97;
	const std::size_t ENEMY = 98;
	const std::size_t NEXT_PHASE = 99;
	const std::size_t END_EVENT = 100;
}

namespace battle_action_type
{
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
	const std::size_t PURIFIED_MOVE_A_CARD_TO_GRAVE = 10700;
}

namespace interact_action_type
{
	const std::size_t EXPLORE_TO_SELECT = 1;
	const std::size_t EXPLORE_TO_VACCANT = 2;
	const std::size_t BATTLE_TO_SELECT = 30000;
	const std::size_t BATTLE_TO_VACCANT = 40000;
}

namespace event_type
{
	//const std::size_t MANDATORY = 1;
	//const std::size_t NOT_MANDATORY = 2;
	const std::size_t PROCEED = 3;
	const std::size_t PURE_TEXT = 4;
	const std::size_t START_BATTLE = 5;
	const std::size_t AQUIRE_HIT_POINTS = 10;
	const std::size_t AQUIRE_MAX_HIT_POINTS = 11;
	const std::size_t REMOVE_HIT_POINTS = 12;
	const std::size_t REMOVE_MAX_HIT_POINTS = 13;
	const std::size_t AQUIRE_STRENGTH = 14;
	const std::size_t AQUIRE_DEXTERITY = 15;
	const std::size_t AQUIRE_VITALITY = 16;
	const std::size_t AQUIRE_LUCK = 17;
	const std::size_t REMOVE_STRENGTH = 18;
	const std::size_t REMOVE_DEXTERITY = 19;
	const std::size_t REMOVE_VITALITY = 20;
	const std::size_t REMOVE_LUCK = 21;
	const std::size_t AQUIRE_CARD = 30;//card
	const std::size_t DUPLICATE_CARD_FROM_DECK = 130;
	const std::size_t AQUIRE_CARD_FROM_SELECTION = 230;
	const std::size_t REMOVE_CARD = 31;//size_t
	const std::size_t REMOVE_CARD_FROM_DECK = 131;
	const std::size_t UPGRADE_CARD = 32;//size_t
	const std::size_t UPGRADE_CARD_FROM_DECK = 132;
	const std::size_t CHANGE_CARD = 33;//size_t
	const std::size_t CHANGE_CARD_FROM_DECK = 133;
	const std::size_t AQUIRE_ARTIFACT = 34;//artifact
	const std::size_t REMOVE_ARTIFACT = 35;//size_t
	const std::size_t AQUIRE_GOLD = 36;
	const std::size_t REMOVE_GOLD = 37;
	const std::size_t AQUIRE_FOOD = 38;
	const std::size_t REMOVE_FOOD = 39;
	const std::size_t REVEAL_MAP = 40;
}

namespace type_type
{
	const std::size_t NORMAL = 1;
	const std::size_t FLAME = 2;
	const std::size_t POISON = 4;
	const std::size_t BLEED = 5;
	const std::size_t PURE = 6;//不受buff影响，穿甲
	const std::size_t INDEPENDENT = 7;//不受buff影响
	const std::size_t WAR_12 = 101;//蓄力劈砍；
	const std::size_t WAR_12_PLUS = 102;//蓄力劈砍+；
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
	const std::size_t STRENGTH = 1;
	const std::size_t DEXTERITY = 2;
	const std::size_t VITALITY = 3;
	const std::size_t ARMOR = 4;
	const std::size_t WEAK = 5;
	const std::size_t VULNERABLE = 6;
	const std::size_t FRAGILE = 7;
	const std::size_t BURN = 8;
	const std::size_t POISON = 9;
	const std::size_t BLEED = 10;
	const std::size_t USED_ATTACK_CARDS = 11;
	const std::size_t USED_SKILL_CARDS = 12;
	const std::size_t USED_ABILITY_CARDS = 13;
	const std::size_t EXHAUST = 14;
	const std::size_t CHAIN = 15;
	const std::size_t MOVE_MUSSLE = 16;
	const std::size_t STUN = 17;
	const std::size_t STUN_RESIST = 18;
	const std::size_t EXPLODE = 19;
	const std::size_t PASSED_TURNS = 20;
	const std::size_t INCREASE_DRAW = 22;
	const std::size_t REDUCE_AP = 23;
	const std::size_t INCREASE_AP = 24;

	//buff from ability cards
	const std::size_t ETERNAL_FURY = 41;
	const std::size_t INVULNARABLE = 42;
	const std::size_t FIGHTING_SPIRIT = 43;
	const std::size_t FRENZY = 44;
	const std::size_t RITE = 45;
	const std::size_t RESUSCITATE = 46;
	const std::size_t ABILITY_BURN = 47;
	const std::size_t SCORCHED_EARTH = 48;
	const std::size_t SHELL = 49;

	//enemies' buffs
	const std::size_t LOADED = 71;
	const std::size_t PAIN = 72;
	const std::size_t CULTIST_RITE = 73;
	const std::size_t PAIN_CURSE = 74;
	const std::size_t CORRUPT = 75;
	const std::size_t FEAST = 76; //TODO not done yet	
	const std::size_t MARK = 77;
	const std::size_t ANGER = 78;

}

namespace gra_size
{
	const std::size_t window_width = 1450;
	const std::size_t window_height = 750;
	const std::size_t max_enemies = 5;
	const std::size_t max_cards = 7;

	const std::size_t buff_side_len = 15;
	const std::size_t buff_closure = 5;
	const std::size_t card_starting_pos = 200;
	const std::size_t card_width = 135;
	const std::size_t card_closure = 10;
	const std::size_t card_x = 0;
	const std::size_t card_rx = card_x + card_width * max_cards + card_closure * (max_cards + 1);
	const std::size_t card_y = 510;
	const std::size_t card_dy = 710;
	const std::size_t viewcard_firrow_x = 150;
	const std::size_t viewcard_firrow_y = 80;
	const std::size_t viewcard_secrow_x = 150;
	const std::size_t viewcard_secrow_y = 320;

	const std::size_t hp_y = 110;
	const std::size_t hp_x = 35;
	const std::size_t gold_y = 110;
	const std::size_t gold_x = 155;
	const std::size_t food_y = 110;
	const std::size_t food_x = 260;
	const std::size_t ap_y = 593;
	const std::size_t ap_x = 60;
	const std::size_t confirm_button_y = 520;
	const std::size_t confirm_button_x = 1315;
	const std::size_t cancel_button_y = 585;
	const std::size_t cancel_button_x = 1315;
	const std::size_t turn_end_button_y = 650;
	const std::size_t turn_end_button_x = 1315;
	const std::size_t enemy_x = 400;
	const std::size_t enemy_y = 200;
	const std::size_t enemy_width = 160;
	const std::size_t enemy_closure = 10;
	const std::size_t player_x = 50;
	const std::size_t player_y = 200;

	//TODO replace the ap_pic (a circle) to a pic(square), should change the following values
	const std::size_t ap_pic_x = 80;
	const std::size_t ap_pic_y = 600;
	const std::size_t ap_pic_radius = 60;

	const std::size_t hp_pic_x = 20;
	const std::size_t hp_pic_y = 20;
	const std::size_t gold_pic_x = 120;
	const std::size_t gold_pic_y = 20;
	const std::size_t food_pic_x = 220;
	const std::size_t food_pic_y = 20;
	const std::size_t ability_num_x = 400;
	const std::size_t ability_num_y = 20;

	const std::size_t deck_pic_x = 1320;
	const std::size_t deck_pic_y = 20;
	const std::size_t r_deck_pic_x = 1375;
	const std::size_t r_deck_pic_y = 20;
	const std::size_t grave_pic_x = 1320;
	const std::size_t grave_pic_y = 80;
	const std::size_t remove_pic_x = 1375;
	const std::size_t remove_pic_y = 80;
	const std::size_t deck_width = 45;
	const std::size_t deck_height = 50;
	const std::size_t view_artifact_x = 1250;
	const std::size_t view_artifact_y = 60;

	const std::size_t left_arrow_x = 50;
	const std::size_t left_arrow_y = 550;
	const std::size_t right_arrow_x = 1320;
	const std::size_t right_arrow_y = 550;
	const std::size_t event_card_x = 500;
	const std::size_t event_card_y = 150;
	const std::size_t event_text_x = 800;
	const std::size_t event_text_y = 150;
	const std::size_t next_x = 1100;
	const std::size_t next_y = 250;

	const std::size_t map_start_x = 230;
	const std::size_t map_start_y = 200;
	const std::size_t map_block_size = 60;
	const std::size_t map_closure = 25;
	const std::size_t map_end_x = map_start_x + 13 * map_block_size + 12 * map_closure;
	const std::size_t map_end_y = map_start_y + 5 * map_block_size + 4 * map_closure;
}

namespace player_class
{
	const std::size_t WAR = 1;
	const std::size_t PLAGUE = 2;
	const std::size_t DEATH = 3;
}

class info_to_battle_sys;
class info_to_explore_sys;
class IMAGE;
class data_sys;
class card
{
public:
	card();
	card(std::size_t id);
	card(const card& copy_card);
	card& operator=(const card& copy_card);

	std::size_t id;
	std::string card_name;
	std::size_t card_type;
	std::size_t upgrade_version_id; //0 means the card has no upgrade version(already upgraded);
	std::size_t cost;
	bool is_reserve;
	bool require_target; //true代表需要选择目标，false代表不用
	bool exhaust;//true代表消耗
	bool inherent;//true代表固有
	bool vanity;//true代表虚无

	info_to_battle_sys use_card(data_sys&);
	info_to_battle_sys discard(data_sys&);
	info_to_battle_sys remove(data_sys&);
	info_to_battle_sys on_turn_end(data_sys&);
};


class artifact
{
public:
	artifact();
	artifact(std::size_t id);
	std::size_t id;
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
	//value is the buff's level when action_id is ADD_BUFF or REMOVE_BUFF.
	std::size_t value;
};

bool default_res(data_sys*);
class e_action
{
public:
	e_action(std::size_t id);
	e_action(std::size_t id, std::size_t ttype, std::size_t tvalue, std::string ttext = "", std::string etext = "", bool(*func)(data_sys*) = default_res);
	e_action(std::size_t id, std::size_t ttype, artifact tatf, std::string ttext = "", std::string etext = "", bool(*func)(data_sys*) = default_res);
	e_action(std::size_t id, std::size_t ttype, card tcard, std::string ttext = "", std::string etext = "", bool(*func)(data_sys*) = default_res);
	e_action(std::size_t id, std::size_t ttype, card tcard, std::size_t tvalue, std::string etext = "", bool(*func)(data_sys*) = default_res);
	std::size_t action_id;
	std::size_t type;
	std::size_t value;
	artifact atf;
	card selected_card;
	std::string text;
	std::string end_text;
	bool(*restriction)(data_sys*); //TODO lambda表达式

	e_action to_event_body();
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
	info_to_explore_sys(std::vector<e_action>);
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
	info_explore_to_interacting(std::size_t ttype);
	info_explore_to_interacting(std::size_t ttype, std::size_t tvalue);
	std::size_t type;
	std::size_t value;
	operator bool();
	void clear();
};







