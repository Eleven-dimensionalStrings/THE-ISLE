#include <iostream>
#include "message.h"
#include "data_sys.h"
using namespace std; using namespace my_container;

bool default_res(data_sys*)
{
	return 1;
}
info_to_battle_sys::info_to_battle_sys()
	:info(), action_set()
{
}

info_to_battle_sys::info_to_battle_sys(action ichange)
	: info()
{
	action_set.push_back(ichange);
}

info_to_battle_sys::info_to_battle_sys(my_vector<action> ichange) : action_set(std::move(ichange))
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
	:action_id(id), type(MEANINGLESS_VALUE), value(MEANINGLESS_VALUE), text(-1), end_text(-1), restriction(default_res), selected_card(card(0)), atf(0)
{
}

e_action::e_action(std::size_t id, std::size_t ttype, std::size_t tvalue, int ttext, int etext, bool(*func)(data_sys*))
	: action_id(id), type(ttype), value(tvalue), text(ttext), end_text(etext), restriction(func), selected_card(card(0)), atf(0)
{
}

e_action::e_action(std::size_t id, std::size_t ttype, artifact tatf, int ttext, int etext, bool(*func)(data_sys*))
	: action_id(id), type(ttype), atf(tatf), text(ttext), end_text(etext), restriction(func), selected_card(card(0))
{
}

e_action::e_action(std::size_t id, std::size_t ttype, card tcard, int ttext, int etext, bool(*func)(data_sys*))
	: action_id(id), type(ttype), selected_card(tcard), text(ttext), end_text(etext), restriction(func), atf(0)
{
}

e_action::e_action(std::size_t id, std::size_t ttype, card tcard, std::size_t tvalue, int etext, bool(*func)(data_sys*))
	: action_id(id), type(ttype), selected_card(tcard), text(-1), value(tvalue), end_text(etext), restriction(func), atf(0)
{
}


e_action e_action::to_event_body()
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

info_to_explore_sys::info_to_explore_sys(my_vector<e_action> ichange) : action_set(std::move(ichange))
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

info_explore_to_interacting::info_explore_to_interacting(std::size_t ttype, std::size_t tvalue)
	: type(ttype), value(tvalue)
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
	:id(id), is_reserve(0), exhaust(false), inherent(false), vanity(false)
{
	id = id;
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
		card_name = "´ò»÷";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 2:
	{
		card_name = "×ÝÕ¶";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 3:
	{
		card_name = "Í´»÷";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 4:
	{
		card_name = "ÉÏÁÃÕ¶";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 5:
	{
		card_name = "Í»´Ì";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 6:
	{
		card_name = "ÏÂÅüÕ¶";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 7:
	{
		card_name = "ºá»Ó";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 8:
	{
		card_name = "Ðý·çÕ¶";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 9:
	{
		card_name = "Í»ÆÆ";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = false;
		break;
	}
	case 10:
	{
		card_name = "¹ý¼çË¤";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 11:
	{
		card_name = "äÎÃð";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = true;
		break;
	}
	case 12:
	{
		card_name = "ÐîÁ¦Åü¿³";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 13:
	{
		card_name = "ÎÞÄ±´ò»÷";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 14:
	{
		card_name = "É¢»ª";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 15:
	{
		card_name = "È«Á¦´ò»÷";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 16:
	{
		card_name = "ÃÍ³å";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 17:
	{
		card_name = "»ìÕ½";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 18:
	{
		card_name = "±³Ë®Ò»Õ½";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 19:
	{
		card_name = "ÑªÖ®ÈÐ";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 20:
	{
		card_name = "½ßÁ¦´ò»÷";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 21:
	{
		card_name = "×ÆÈÈ´ò»÷";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 22:
	{
		card_name = "·ÐÑª´ò»÷";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		break;
	}
	case 23:
	{
		card_name = "»ðÑæ·ç±©";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = false;
		break;
	}
	case 24:
	{
		card_name = "»ðÑæäöÎÐ";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 25:
	{
		card_name = "»ðÉß";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 26:
	{
		card_name = "Òý±¬";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 27:
	{
		card_name = "¼ç×²";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 28:
	{
		card_name = "ÉÏ¹´È­";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		vanity = true;
		break;
	}
	case 29:
	{
		card_name = "ÏÂÂíÍþ";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 30:
	{
		card_name = "·ÀÓù";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 31:
	{
		card_name = "¶ÜÅÆ¸ñµ²";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 32:
	{
		card_name = "Îä×°";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 33:
	{
		card_name = "ÌôÐÆ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 34:
	{
		card_name = "¹ÌÊØ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 35:
	{
		card_name = "Ä¥µ¶";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 36:
	{
		card_name = "ÖØÕûÆì¹Ä";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 37:
	{
		card_name = "Õ½ºð";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 38:
	{
		card_name = "½»·æ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 39:
	{
		card_name = "Õ½Òâ";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 40:
	{
		card_name = "°×ÈÈ»¯";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 41:
	{
		card_name = "Å­ºð";
		card_type = card_type::SKILL;
		cost = 2;
		require_target = false;
		break;
	}
	case 42:
	{
		card_name = "ÉñÖ®Á¦Á¿";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 43:
	{
		card_name = "Í»ÆÆ¼«ÏÞ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 44:
	{
		card_name = "Ê¢Å­";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 45:
	{
		card_name = "·ÅÑª";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 46:
	{
		card_name = "¼ÀÆ·";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 47:
	{
		card_name = "ÒýÈ¼";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		exhaust = true;
		break;
	}
	case 48:
	{
		card_name = "»ðÖ®Ó¡";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 49:
	{
		card_name = "¼¤Å­";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 50:
	{
		card_name = "½ÉÐµ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 51:
	{
		card_name = "ÍþÏÅ";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 52:
	{
		card_name = "ÀûÈÐÑÐÄ¥";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 53:
	{
		card_name = "ÎÞ¾¡·ßÅ­";
		card_type = card_type::ABILITY;
		cost = 3;
		require_target = false;
		break;
	}
	case 54:
	{
		card_name = "ÎÞÐ¸¿É»÷";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 55:
	{
		card_name = "¶·Ö¾";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 56:
	{
		card_name = "¿ñ±©";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 57:
	{
		card_name = "ÒÇÊ½";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 58:
	{
		card_name = "»îÁ¦ÔÙÉú";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 59:
	{
		card_name = "È¼ÉÕ";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 60:
	{
		card_name = "½¹ÍÁ";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 61:
	{
		card_name = "´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 62:
	{
		card_name = "×ÝÕ¶+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 63:
	{
		card_name = "Í´»÷+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 64:
	{
		card_name = "ÉÏÁÃÕ¶+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 65:
	{
		card_name = "Í»´Ì+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 66:
	{
		card_name = "ÏÂÅüÕ¶+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 67:
	{
		card_name = "ºá»Ó+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 68:
	{
		card_name = "Ðý·çÕ¶+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 69:
	{
		card_name = "Í»ÆÆ+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = false;
		break;
	}
	case 70:
	{
		card_name = "¹ý¼çË¤+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 71:
	{
		card_name = "äÎÃð+";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = true;
		break;
	}
	case 72:
	{
		card_name = "ÐîÁ¦Åü¿³+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 73:
	{
		card_name = "ÎÞÄ±´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 74:
	{
		card_name = "É¢»ª+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 75:
	{
		card_name = "È«Á¦´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		break;
	}
	case 76:
	{
		card_name = "ÃÍ³å+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 77:
	{
		card_name = "»ìÕ½+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 78:
	{
		card_name = "±³Ë®Ò»Õ½+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 79:
	{
		card_name = "ÑªÖ®ÈÐ+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 80:
	{
		card_name = "½ßÁ¦´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 81:
	{
		card_name = "×ÆÈÈ´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 82:
	{
		card_name = "·ÐÑª´ò»÷+";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		break;
	}
	case 83:
	{
		card_name = "»ðÑæ·ç±©+";
		card_type = card_type::ATTACK;
		cost = 3;
		require_target = false;
		break;
	}
	case 84:
	{
		card_name = "»ðÑæäöÎÐ+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 85:
	{
		card_name = "»ðÉß+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = false;
		break;
	}
	case 86:
	{
		card_name = "Òý±¬+";
		card_type = card_type::ATTACK;
		cost = 0;
		require_target = true;
		exhaust = true;
		break;
	}
	case 87:
	{
		card_name = "¼ç×²+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		break;
	}
	case 88:
	{
		card_name = "ÉÏ¹´È­+";
		card_type = card_type::ATTACK;
		cost = 2;
		require_target = true;
		vanity = true;
		break;
	}
	case 89:
	{
		card_name = "ÏÂÂíÍþ+";
		card_type = card_type::ATTACK;
		cost = 1;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 90:
	{
		card_name = "·ÀÓù+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 91:
	{
		card_name = "¶ÜÅÆ¸ñµ²+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 92:
	{
		card_name = "Îä×°+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 93:
	{
		card_name = "ÌôÐÆ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 94:
	{
		card_name = "¹ÌÊØ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 95:
	{
		card_name = "Ä¥µ¶+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 96:
	{
		card_name = "ÖØÕûÆì¹Ä+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 97:
	{
		card_name = "Õ½ºð+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 98:
	{
		card_name = "½»·æ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		break;
	}
	case 99:
	{
		card_name = "Õ½Òâ+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 100:
	{
		card_name = "°×ÈÈ»¯+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 101:
	{
		card_name = "Å­ºð+";
		card_type = card_type::SKILL;
		cost = 2;
		require_target = false;
		break;
	}
	case 102:
	{
		card_name = "ÉñÖ®Á¦Á¿+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		exhaust = true;
		break;
	}
	case 103:
	{
		card_name = "Í»ÆÆ¼«ÏÞ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 104:
	{
		card_name = "Ê¢Å­+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		exhaust = true;
		break;
	}
	case 105:
	{
		card_name = "·ÅÑª+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 106:
	{
		card_name = "¼ÀÆ·+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = false;
		break;
	}
	case 107:
	{
		card_name = "ÒýÈ¼+";
		card_type = card_type::SKILL;
		cost = 0;
		require_target = true;
		exhaust = true;
		inherent = true;
		break;
	}
	case 108:
	{
		card_name = "»ðÖ®Ó¡+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		break;
	}
	case 109:
	{
		card_name = "¼¤Å­+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 110:
	{
		card_name = "½ÉÐµ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = true;
		exhaust = true;
		break;
	}
	case 111:
	{
		card_name = "ÍþÏÅ+";
		card_type = card_type::SKILL;
		cost = 1;
		require_target = false;
		break;
	}
	case 112:
	{
		card_name = "ÀûÈÐÑÐÄ¥+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 113:
	{
		card_name = "ÎÞ¾¡·ßÅ­+";
		card_type = card_type::ABILITY;
		cost = 3;
		require_target = false;
		break;
	}
	case 114:
	{
		card_name = "ÎÞÐ¸¿É»÷+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 115:
	{
		card_name = "¶·Ö¾+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 116:
	{
		card_name = "¿ñ±©+";
		card_type = card_type::ABILITY;
		cost = 0;
		require_target = false;
		break;
	}
	case 117:
	{
		card_name = "ÒÇÊ½+";
		card_type = card_type::ABILITY;
		cost = 0;
		require_target = false;
		break;
	}
	case 118:
	{
		card_name = "»îÁ¦ÔÙÉú+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 119:
	{
		card_name = "È¼ÉÕ+";
		card_type = card_type::ABILITY;
		cost = 1;
		require_target = false;
		break;
	}
	case 120:
	{
		card_name = "½¹ÍÁ+";
		card_type = card_type::ABILITY;
		cost = 2;
		require_target = false;
		break;
	}
	case 401:
	{
		card_name = "Æ£±¹";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = true;
		break;
	}
	case 402:
	{
		card_name = "ÉË¿Ú";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = false;
		break;
	}
	case 403:
	{
		card_name = "Ñ£ÔÎ";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = true;
		break;
	}
	case 404:
	{
		card_name = "ÁÑÉË";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = false;
		break;
	}
	case 405:
	{
		card_name = "È±Ñõ";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = true;
		break;
	}
	case 406:
	{
		card_name = "ÎÞÁ¦";
		card_type = card_type::STAT;
		cost = 100;
		require_target = false;
		vanity = false;
		break;
	}
	default:
		break;
	}
}

card::card(const card& copy_card) : id(copy_card.id),
card_name(copy_card.card_name), card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id),
cost(copy_card.cost), is_reserve(copy_card.is_reserve), require_target(copy_card.require_target),
exhaust(copy_card.exhaust), inherent(copy_card.inherent), vanity(copy_card.vanity)
{

}

card & card::operator=(const card & c)
{
	this->is_reserve = c.is_reserve;
	this->id = c.id;
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
	return d.card_effect(id);
}

info_to_battle_sys card::discard(data_sys&d)
{
	return d.card_discard(id);
}

info_to_battle_sys card::remove(data_sys&d)
{
	return d.card_remove(id);
}

info_to_battle_sys card::on_turn_end(data_sys&d)
{
	return d.card_on_turn_end(id);
}

artifact::artifact()
	:id(0)
{
}

artifact::artifact(std::size_t id)
	: id(id)
{
}

void info_to_render_sys::append(info_to_render_sys t)

{
	{
		for (auto &i : t.action_set)
		{
			action_set.push_back(i);
		}
	}
}

info_to_render_sys::info_to_render_sys()
	:info(), action_set() {}

info_to_render_sys::info_to_render_sys(r_action ichange)
	: info()
{
	action_set.push_back(ichange);
}

info_to_render_sys::info_to_render_sys(my_container::my_vector<r_action> ichange) : action_set(std::move(ichange)) {}

r_action::r_action(int id)
	: action_id(id), caller(nullptr), listener(nullptr), type(MEANINGLESS_VALUE), value(MEANINGLESS_VALUE) {}

r_action::r_action(int id, int ttype, int tvalue)
	: action_id(id), caller(nullptr), listener(nullptr), type(ttype), value(tvalue) {}

r_action::r_action(int id, game_entity * tcaller, game_entity * tlistener, std::size_t ttype, std::size_t tvalue)
	: action_id(id), caller(tcaller), listener(tlistener), type(ttype), value(tvalue) {}
