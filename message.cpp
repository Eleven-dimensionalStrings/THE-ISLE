#include <iostream>
#include "message.h"
#include "data_sys.h"
using namespace std;

info_to_battle_sys::info_to_battle_sys()
	:info(), action_set()
{
}

info_to_battle_sys::info_to_battle_sys(action ichange)
	: info()
{
	action_set.push_back(ichange);
}

info_to_battle_sys::info_to_battle_sys(vector<action> ichange) : action_set(std::move(ichange))
{
}

void info_to_battle_sys::append(info_to_battle_sys t)
{
	for (auto &i : t.action_set)
	{
		action_set.push_back(i);
	}
}

info::info()
{
}

action::action(std::size_t id) :action_id(id), caller(nullptr), listener(nullptr), type(MEANINGLESS_VALUE), value(MEANINGLESS_VALUE)
{
}

action::action(std::size_t id, std::size_t ttype, std::size_t tvalue)
	: action_id(id), caller(nullptr), listener(nullptr), type(ttype), value(tvalue)
{
}

action::action(std::size_t id, game_entity * tcaller, game_entity * tlistener, std::size_t ttype, std::size_t tvalue)
	: action_id(id), caller(tcaller), listener(tlistener), type(ttype), value(tvalue)
{
}

info_battle_to_interacting::info_battle_to_interacting(std::size_t ttype, std::size_t tnum, bool tis_m)
	: type(ttype), num(tnum), is_m(tis_m)
{
}

info_battle_to_interacting::operator bool()
{
	return (type || num || is_m);
}

void info_battle_to_interacting::clear()
{
	type = num = is_m = 0;
}

info_battle_to_interacting::info_battle_to_interacting()
{

}

e_action::e_action(std::size_t id)
	:action_id(id), type(MEANINGLESS_VALUE), value(MEANINGLESS_VALUE), text("ERROR")
{
}

e_action::e_action(std::size_t id, std::size_t ttype, std::size_t tvalue, std::string ttext)
	: action_id(id), type(ttype), value(tvalue), text(ttext)
{
}

e_action::e_action(std::size_t id, std::size_t ttype, artifact tatf, std::string ttext)
	: action_id(id), type(ttype), atf(tatf), text(ttext)
{
}

e_action::e_action(std::size_t id, std::size_t ttype, card tcard, std::string ttext)
	: action_id(id), type(ttype), selected_card(tcard), text(ttext)
{
}

e_action e_action::to_selection()
{
	action_id = explore_action_type::EVENT_BODY;
	return *this;
}

info_to_explore_sys::info_to_explore_sys()
	: info(), action_set()
{
}

info_to_explore_sys::info_to_explore_sys(e_action ichange)
	: info()
{
	action_set.push_back(ichange);
}

info_to_explore_sys::info_to_explore_sys(vector<e_action> ichange) : action_set(std::move(ichange))
{
}

void info_to_explore_sys::append(info_to_explore_sys t)
{
	for (auto &i : t.action_set)
	{
		action_set.push_back(i);
	}
}

info_explore_to_interacting::info_explore_to_interacting()
{
}

info_explore_to_interacting::info_explore_to_interacting(std::size_t ttype)
	: type(ttype)
{
}

info_explore_to_interacting::operator bool()
{
	return (type);
}

void info_explore_to_interacting::clear()
{
	type = 0;
}

card::card()
{
}

card::card(size_t id)
	:card_id(id), is_reserve(0), exhaust(false), inherent(false), vanity(false)
{
	card_id = id;
	if ((id >= 1 && id <= 60) || (id >= 121 && id <= 180) || (id >= 241 && id <= 300))
	{
		upgrade_version_id = id + 60;
	}
	else
	{
		upgrade_version_id = 0;
	}
	switch (id)
	{
	case 1:
	{
		card_name = "���";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 2:
	{
		card_name = "��ն";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 3:
	{
		card_name = "ʹ��";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 4:
	{
		card_name = "����ն";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 5:
	{
		card_name = "ͻ��";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 6:
	{
		card_name = "����ն";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 7:
	{
		card_name = "���";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 8:
	{
		card_name = "����ն";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 9:
	{
		card_name = "ͻ��";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = false;
		break;
	}
	case 10:
	{
		card_name = "����ˤ";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 11:
	{
		card_name = "����";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = true;
		break;
	}
	case 12:
	{
		card_name = "��������";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 13:
	{
		card_name = "��ı���";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 14:
	{
		card_name = "ɢ��";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 15:
	{
		card_name = "ȫ�����";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 16:
	{
		card_name = "�ͳ�";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 17:
	{
		card_name = "��ս";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 18:
	{
		card_name = "��ˮһս";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 19:
	{
		card_name = "Ѫ֮��";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 20:
	{
		card_name = "�������";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 21:
	{
		card_name = "���ȴ��";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 22:
	{
		card_name = "��Ѫ���";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		break;
	}
	case 23:
	{
		card_name = "����籩";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = false;
		break;
	}
	case 24:
	{
		card_name = "��������";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 25:
	{
		card_name = "����";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 26:
	{
		card_name = "����";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 27:
	{
		card_name = "��ײ";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 28:
	{
		card_name = "�Ϲ�ȭ";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		vanity = true;
		break;
	}
	case 29:
	{
		card_name = "������";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 30:
	{
		card_name = "����";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 31:
	{
		card_name = "���Ƹ�";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 32:
	{
		card_name = "��װ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 33:
	{
		card_name = "����";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 34:
	{
		card_name = "����";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 35:
	{
		card_name = "ĥ��";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 36:
	{
		card_name = "�������";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 37:
	{
		card_name = "ս��";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 38:
	{
		card_name = "����";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 39:
	{
		card_name = "ս��";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 40:
	{
		card_name = "���Ȼ�";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 41:
	{
		card_name = "ŭ��";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 42:
	{
		card_name = "��֮����";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 43:
	{
		card_name = "ͻ�Ƽ���";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 44:
	{
		card_name = "ʢŭ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 45:
	{
		card_name = "��Ѫ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 46:
	{
		card_name = "��Ʒ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 47:
	{
		card_name = "��ȼ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		exhaust = true;
		break;
	}
	case 48:
	{
		card_name = "��֮ӡ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 49:
	{
		card_name = "��ŭ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 50:
	{
		card_name = "��е";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 51:
	{
		card_name = "����";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 52:
	{
		card_name = "������ĥ";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 53:
	{
		card_name = "�޾���ŭ";
		card_type = card_type::ABILITY;
		cost = 3;
		require_target = false;
		break;
	}
	case 54:
	{
		card_name = "��и�ɻ�";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 55:
	{
		card_name = "��־";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 56:
	{
		card_name = "��";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 57:
	{
		card_name = "��ʽ";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 58:
	{
		card_name = "��������";
		card_type = card_type::ABILITY;
		cost = 3;
		require_target = false;
		break;
	}
	case 59:
	{
		card_name = "ȼ��";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 60:
	{
		card_name = "����";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 61:
	{
		card_name = "���+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 62:
	{
		card_name = "��ն+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 63:
	{
		card_name = "ʹ��+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 64:
	{
		card_name = "����ն+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 65:
	{
		card_name = "ͻ��+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 66:
	{
		card_name = "����ն+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 67:
	{
		card_name = "���+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 68:
	{
		card_name = "����ն+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 69:
	{
		card_name = "ͻ��+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = false;
		break;
	}
	case 70:
	{
		card_name = "����ˤ+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 71:
	{
		card_name = "����+";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = true;
		break;
	}
	case 72:
	{
		card_name = "��������+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 73:
	{
		card_name = "��ı���+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 74:
	{
		card_name = "ɢ��+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 75:
	{
		card_name = "ȫ�����+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 76:
	{
		card_name = "�ͳ�+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 77:
	{
		card_name = "��ս+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 78:
	{
		card_name = "��ˮһս+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 79:
	{
		card_name = "Ѫ֮��+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 80:
	{
		card_name = "�������+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 81:
	{
		card_name = "���ȴ��+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 82:
	{
		card_name = "��Ѫ���+";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		break;
	}
	case 83:
	{
		card_name = "����籩+";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = false;
		break;
	}
	case 84:
	{
		card_name = "��������+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 85:
	{
		card_name = "����+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 86:
	{
		card_name = "����+";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		exhaust = true;
		break;
	}
	case 87:
	{
		card_name = "��ײ+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 88:
	{
		card_name = "�Ϲ�ȭ+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		vanity = true;
		break;
	}
	case 89:
	{
		card_name = "������+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 90:
	{
		card_name = "����+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 91:
	{
		card_name = "���Ƹ�+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 92:
	{
		card_name = "��װ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 93:
	{
		card_name = "����+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 94:
	{
		card_name = "����+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 95:
	{
		card_name = "ĥ��+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 96:
	{
		card_name = "�������+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 97:
	{
		card_name = "ս��+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 98:
	{
		card_name = "����+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 99:
	{
		card_name = "ս��+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 100:
	{
		card_name = "���Ȼ�+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 101:
	{
		card_name = "ŭ��+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 102:
	{
		card_name = "��֮����+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 103:
	{
		card_name = "ͻ�Ƽ���+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 104:
	{
		card_name = "ʢŭ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		exhaust = true;
		break;
	}
	case 105:
	{
		card_name = "��Ѫ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 106:
	{
		card_name = "��Ʒ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 107:
	{
		card_name = "��ȼ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 108:
	{
		card_name = "��֮ӡ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 109:
	{
		card_name = "��ŭ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 110:
	{
		card_name = "��е+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 111:
	{
		card_name = "����+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 112:
	{
		card_name = "������ĥ+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 113:
	{
		card_name = "�޾���ŭ+";
		card_type = card_type::ABILITY;
		cost = 3;
		require_target = false;
		break;
	}
	case 114:
	{
		card_name = "��и�ɻ�+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 115:
	{
		card_name = "��־+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 116:
	{
		card_name = "��+";
		card_type = card_type::ABILITY;
		cost = 0;
		require_target = false;
		break;
	}
	case 117:
	{
		card_name = "��ʽ+";
		card_type = card_type::ABILITY;
		cost = 0;
		require_target = false;
		break;
	}
	case 118:
	{
		card_name = "��������+";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 119:
	{
		card_name = "ȼ��+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 120:
	{
		card_name = "����+";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 1001:
	{
		card_name = "ƣ��";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = true;
		break;
	}
	default:
		break;
	}
}

card::card(const card& copy_card) : card_id(copy_card.card_id),
card_name(copy_card.card_name), card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id),
cost(copy_card.cost), is_reserve(copy_card.is_reserve), require_target(copy_card.require_target),
exhaust(copy_card.exhaust), inherent(copy_card.inherent), vanity(copy_card.vanity)
{

}

card & card::operator=(const card & c)
{
	this->is_reserve = c.is_reserve;
	this->card_id = c.card_id;
	this->card_name = c.card_name;
	this->card_type = c.card_type;
	this->upgrade_version_id = c.upgrade_version_id;
	this->require_target = c.require_target;
	this->cost = c.cost;
	this->exhaust = c.exhaust;
	this->inherent = c.inherent;
	this->vanity = c.vanity;
	return *this;
}


info_to_battle_sys card::use_card(data_sys&d)
{
	return d.card_effect(card_id);
}

info_to_battle_sys card::discard(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::remove(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::on_turn_end(data_sys&)
{
	return info_to_battle_sys();
}

