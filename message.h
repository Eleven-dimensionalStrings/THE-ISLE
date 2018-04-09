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
	const int PLAYER = 0;//�������λ��
	const int UNKNOWN = 1;//û��ȥ��
	const int KNOWN = 2;//�Ѿ�����������û��ȥ��
	const int VISITED = 3;//�Ѿ�ȥ��
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
	const std::size_t USE_A_CARD = 2333;//action��typeΪ��Ƭ����,valueΪ�����еĵڼ��ſ�
	//������˸�action��,typeֱ�ӱ�ʾ�Ƿ�ǿ��ѡ����ô���ſ�
	//������ʹ�ÿ�Ƭʱ�õ���action
	const std::size_t KEEP_A_CARD = 10000;//�غϽ���ʱ�������ſ�
	const std::size_t REMOVE_A_CARD = 10001;//��������
	const std::size_t DISCARD_A_CARD = 10002;//��Ч��Ӱ������
	const std::size_t DRAW_CARDS = 10003;//�鿨,value��ʾ�������,����buff�Ĳ�����on_callingִ��
	//�����P����perform,����interactingѡ�꿨Ƭ�󴫻�ս��ϵͳ,ִ�о��������
	const std::size_t P_KEEP_A_CARD = 10100;//�غϽ���ʱ�������ſ�
	const std::size_t P_REMOVE_A_CARD = 10101;//��������
	const std::size_t P_DISCARD_A_CARD = 10102;//��Ч��Ӱ������
	const std::size_t ENTITY_BE_ATK = 10300;//ʵ���յ�����,����battle������Ϣ��draw
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

//action��type�ľ�����𣬼��˺���buff�ľ������
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
	const std::size_t VULNERABLE = 1;//����
	const std::size_t POISON = 2;//����
}

namespace window_unit_size
{
	using cstszt = const std::size_t;
	cstszt window_width = 1200;
	cstszt window_height = 720;
	//��������
	cstszt card_in_hand_up = 500;
	cstszt card_in_hand_down = 720;
	cstszt card_in_hand_left = 0;
	cstszt card_in_hand_right = 900;
	cstszt card_width = 100;//ÿ���ƵĿ��
	cstszt card_up = 510;//�Ƶ�λ��
	cstszt card_down = 710;
	cstszt card_closure = 10;
}

class game_entity;

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

//explore_selection �ǿ���ѡ���ѡ��
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

//event_e ���¼�����һ���ڵ�
class event_e
{
public:
	std::vector<explore_selection> selection;//ѡ��/����ѡ���¼���ѡ��
	std::vector<event_e> following_event;//�����ķ�֧�¼�
	std::string name;//�¼������֣�ѡ��ĵ����֣�
	std::string text;//��ʾ���¼�����
	std::size_t type;//�¼������ࣨս����ѡ�񣬶���ѡ��
	std::size_t enmey_type;//ս���¼��ĵ�������
};

//event_card ���¼���������һ���¼���
class event_card
{
public:
	event_e root;
};

