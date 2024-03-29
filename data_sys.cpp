#include "data_sys.h"
#include <random>
#include <ctime>
#include "battle_system.h"
using namespace std; using namespace my_container;

data_sys::data_sys() :b(nullptr), player_data(*this), all_enemies(*this, MEANINGLESS_VALUE), random_enemy(*this, MEANINGLESS_VALUE)
, select_one_enemy(*this, MEANINGLESS_VALUE), re(this), view_cards(0), cards_thumbnail(420), cards_original(420), cards_mask(10), backgrounds(15)
, components(45), entities(60), artifact_pics(21), buff_pics(22)
{
	background_pic = 0;
	map_text = 0;
}

info_to_battle_sys data_sys::card_effect(std::size_t id)
{
	switch (id)
	{
	case 1://打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 6)});
		break;
	}
	case 2://纵斩
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 3://痛击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2)});
		break;
	}
	case 4://上撩斩
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2)});
		break;
	}
	case 5://突刺
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4)});
		break;
	}
	case 6://下劈斩
	{
		info_to_battle_sys result(action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12));
		if (cards_in_hand.size() > 1)
		{
			result.append(action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, cards_in_hand.size() - 2));
		}
		return result;
		break;
	}
	case 7://横挥
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::NORMAL, 6)});
		break;
	}
	case 8://旋风斩
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 8)});
		break;
	}
	case 9://突破
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 10://过肩摔
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 2)});
		break;
	}
	case 11://湮灭
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 36)});
		break;
	}
	case 12://蓄力劈砍
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::WAR_12, 12)});
		break;
	}
	case 13://无谋打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::ADD_BUFF
							, &player_data, &player_data, buff_type::VULNERABLE, 1)});
		break;
	}
	case 14://散华
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 2)});
		break;
	}
	case 15://全力打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 16://猛冲
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 17://混战
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401)});
		break;
	}
	case 18://背水一战
	{
		info_to_battle_sys temp;
		for (int i = cards_in_hand.size() - 1; i >= 0; --i)
		{
			if (cards_in_hand[i].card_type == card_type::STAT)
			{
				temp.append(action(battle_action_type::P_REMOVE_A_CARD
					, &player_data, &player_data, card_type::STAT, i));
				temp.append(action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::NORMAL, 6));
			}
		}
		return temp;
	}
	case 19://血之刃
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 12)});
		break;
	}
	case 20://竭力打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401)});
		break;
	}
	case 21://灼热打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::FLAME, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 22://沸血打击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::FLAME, 8), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 23://火焰风暴
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::CALLING_ACTION
						, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::ADD_BUFF
							, &player_data, &all_enemies, buff_type::BURN, 4)});
		break;
	}
	case 24://火焰漩涡
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &all_enemies, buff_type::BURN, 1)});
		break;
	}
	case 25://火蛇
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &random_enemy, type_type::FLAME, 3)});
		break;
	}
	case 26://引爆
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::EXPLODE, 3)});
		break;
	}
	case 27://肩撞
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 1)});
		break;
	}
	case 28://上勾拳
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 6) });
		break;
	}
	case 29://下马威
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1) });
		break;
	}
	case 30://防御
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 5) });
		break;
	}
	case 31://盾牌格挡
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1) });
		break;
	}
	case 32://武装
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::REMOVE_BUFF
				, &player_data, &player_data, buff_type::FRAGILE, 999), action(battle_action_type::REMOVE_BUFF
					, &player_data, &player_data, buff_type::VULNERABLE, 999) });
		break;
	}
	case 33://挑衅
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1) });
		break;
	}
	case 34://固守
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 15), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 401), action(battle_action_type::ADD_CARD_TO_DECK
						, MEANINGLESS_VALUE, 401) });
		break;
	}
	case 35://磨刀
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1)});
		break;
	}
	case 36://重整旗鼓
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8), action(battle_action_type::REMOVE_BUFF
				, &player_data, &player_data, buff_type::WEAK, 999), action(battle_action_type::REMOVE_BUFF
					, &player_data, &player_data, buff_type::VULNERABLE, 999), action(battle_action_type::REMOVE_BUFF
						, &player_data, &player_data, buff_type::CHAIN, 999) });
		break;
	}
	case 37://战吼
	{
		if (cards_deck[0].card_type == card_type::ATTACK)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::STRENGTH, 1), action(battle_action_type::ADD_BUFF
						, &player_data, &player_data, buff_type::MOVE_MUSSLE, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
		}
		break;
	}
	case 38://交锋
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1) });

		break;
	}
	case 39://战意
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2) });
		break;
	}
	case 40://白热化
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
			, &player_data, &player_data, MEANINGLESS_VALUE, 3), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 401) });
		break;
	}
	case 41://怒吼
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &all_enemies, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 1), action(battle_action_type::DRAW_CARDS
					, &player_data, &player_data, MEANINGLESS_VALUE, 2) });
		break;
	}
	case 42://神之力量
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 10), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 10) });
		break;
	}
	case 43://突破极限
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, player_data.has_buff(buff_type::STRENGTH)) });
		break;
	}
	case 44://盛怒
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 45://放血
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &player_data, type_type::ADD_AP, 1) });
		break;
	}
	case 46://祭品
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2) });
		break;
	}
	case 47://引燃
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::BURN, 5)});
		break;
	}
	case 48://火之印
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 49://激怒
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 2)});
		break;
	}
	case 50://缴械
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::REMOVE_BUFF
			, &player_data, &select_one_enemy, buff_type::STRENGTH, 2)});
		break;
	}
	case 51://威吓
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 5), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 52://利刃研磨
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2)});
		break;
	}
	case 53://无尽愤怒
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ETERNAL_FURY, 2)});
		break;
	}
	case 54://无懈可击
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::INVULNARABLE, 1)});
		break;
	}
	case 55://斗志
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FIGHTING_SPIRIT, 1)});
		break;
	}
	case 56://狂暴
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FRENZY, 1)});
		break;
	}
	case 57://仪式
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RITE, 1)});
		break;
	}
	case 58://活力再生
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RESUSCITATE, 0)});
		break;
	}
	case 59://燃烧
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ABILITY_BURN, 1)});
		break;
	}
	case 60://焦土
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::SCORCHED_EARTH, 2)});
		break;
	}
	case 61://打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 62://纵斩+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14)});
		break;
	}
	case 63://痛击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 3)});
		break;
	}
	case 64://上撩斩+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2)});
		break;
	}
	case 65://突刺+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 4)});
		break;
	}
	case 66://下劈斩+
	{
		info_to_battle_sys result(action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 16));
		if (cards_in_hand.size() > 1)
		{
			result.append(action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, re.get_num(0, cards_in_hand.size() - 2)));
		}
		return result;
		break;
	}
	case 67://横挥+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 68://旋风斩+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 12)});
		break;
	}
	case 69://突破+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &all_enemies, buff_type::WEAK, 2)});
		break;
	}
	case 70://过肩摔+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 3)});
		break;
	}
	case 71://湮灭+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 42)});
		break;
	}
	case 72://蓄力劈砍+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::WAR_12_PLUS, 12)});
		break;
	}
	case 73://无谋打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::ADD_BUFF
							, &player_data, &player_data, buff_type::VULNERABLE, 1)});
		break;
	}
	case 74://散华+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
							, &player_data, &select_one_enemy, type_type::NORMAL, 2)});
		break;
	}
	case 75://全力打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 76://猛冲+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 16), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 77://混战+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 14), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401)});
		break;
	}
	case 78://背水一战+
	{
		info_to_battle_sys temp;
		for (int i = cards_in_hand.size() - 1; i >= 0; --i)
		{
			if (cards_in_hand[i].card_type == card_type::STAT)
			{
				temp.append(action(battle_action_type::P_REMOVE_A_CARD
					, &player_data, &player_data, card_type::STAT, i));
				temp.append(action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::NORMAL, 8));
			}
		}
		return temp;
	}
	case 79://血之刃+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 16)});
		break;
	}
	case 80://竭力打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 16), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401)});
		break;
	}
	case 81://灼热打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::FLAME, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 82://沸血打击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::FLAME, 10), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 83://火焰风暴+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::CALLING_ACTION
						, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::ADD_BUFF
							, &player_data, &all_enemies, buff_type::BURN, 5)});
		break;
	}
	case 84://火焰漩涡+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
						, &player_data, &all_enemies, buff_type::BURN, 1)});
		break;
	}
	case 85://火蛇+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::FLAME, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::FLAME, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &random_enemy, type_type::FLAME, 4)});
		break;
	}
	case 86://引爆+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::EXPLODE, 3)});
		break;
	}
	case 87://肩撞+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 1)});
		break;
	}
	case 88://上勾拳+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 6) });
		break;
	}
	case 89://下马威+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1) });
		break;
	}
	case 90://防御+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8) });
		break;
	}
	case 91://盾牌格挡+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1) });
		break;
	}
	case 92://武装+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 13), action(battle_action_type::REMOVE_BUFF
				, &player_data, &player_data, buff_type::FRAGILE, 999), action(battle_action_type::REMOVE_BUFF
					, &player_data, &player_data, buff_type::VULNERABLE, 999) });
		break;
	}
	case 93://挑衅+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 15), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1) });
		break;
	}
	case 94://固守+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 20), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 401), action(battle_action_type::ADD_CARD_TO_DECK
						, MEANINGLESS_VALUE, 401) });
		break;
	}
	case 95://磨刀+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1)});
		break;
	}
	case 96://重整旗鼓+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::REMOVE_BUFF
				, &player_data, &player_data, buff_type::WEAK, 999), action(battle_action_type::REMOVE_BUFF
					, &player_data, &player_data, buff_type::VULNERABLE, 999), action(battle_action_type::REMOVE_BUFF
						, &player_data, &player_data, buff_type::CHAIN, 999) });
		break;
	}
	case 97://战吼+
	{
		if (cards_deck[0].card_type == card_type::ATTACK)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::STRENGTH, 3), action(battle_action_type::ADD_BUFF
						, &player_data, &player_data, buff_type::MOVE_MUSSLE, 3)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
		}
		break;
	}
	case 98://交锋+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2) });

		break;
	}
	case 99://战意+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 4), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 4) });
		break;
	}
	case 100://白热化+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::DRAW_CARDS
			, &player_data, &player_data, MEANINGLESS_VALUE, 3), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 401), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 401) });
		break;
	}
	case 101://怒吼+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &all_enemies, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::DRAW_CARDS
					, &player_data, &player_data, MEANINGLESS_VALUE, 3) });
		break;
	}
	case 102://神之力量+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 8) });
		break;
	}
	case 103://突破极限+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, player_data.has_buff(buff_type::STRENGTH)) });
		break;
	}
	case 104://盛怒+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 105://放血+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 106://祭品+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 3) });
		break;
	}
	case 107://引燃+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::BURN, 5)});
		break;
	}
	case 108://火之印+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 109://激怒+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 3)});
		break;
	}
	case 110://缴械+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::REMOVE_BUFF
			, &player_data, &select_one_enemy, buff_type::STRENGTH, 3)});
		break;
	}
	case 111://威吓+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 112://利刃研磨+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 3)});
		break;
	}
	case 113://无尽愤怒+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ETERNAL_FURY, 3)});
		break;
	}
	case 114://无懈可击+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::INVULNARABLE, 1)});
		break;
	}
	case 115://斗志+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FIGHTING_SPIRIT, 2)});
		break;
	}
	case 116://狂暴+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FRENZY, 1)});
		break;
	}
	case 117://仪式+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RITE, 1)});
		break;
	}
	case 118://活力再生+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RESUSCITATE, 0)});
		break;
	}
	case 119://燃烧+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ABILITY_BURN, 2)});
		break;
	}
	case 120://焦土+
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::SCORCHED_EARTH, 3)});
		break;
	}
	default:
		return info_to_battle_sys();
		break;
	}
}

info_to_battle_sys data_sys::card_remove(std::size_t id)
{
	switch (id)
	{
	default:
		return info_to_battle_sys();
		break;
	}
}

info_to_battle_sys data_sys::card_discard(std::size_t id)
{
	switch (id)
	{
	default:
		return info_to_battle_sys();
		break;
	}
}

info_to_battle_sys data_sys::card_on_turn_end(std::size_t id)
{
	switch (id)
	{
	case 404:
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, nullptr, &player_data, type_type::INDEPENDENT, 3));
		break;
	case 405:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, nullptr, &player_data, buff_type::REDUCE_AP, 1));
		break;
	case 406:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, nullptr, &player_data, buff_type::WEAK, 1));
		break;
	default:
		return info_to_battle_sys();
		break;
	}
}

info_to_explore_sys data_sys::event_effect(std::size_t id)
{
	switch (id)
	{
	case 1://篝火
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 0),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 999, 20, 15),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1000, 21, 16, [](data_sys* t)->bool
			{
				for (auto i : t->cards_pool)
				{
					if (i.upgrade_version_id)
					{
						return true;
					}
				}
				return false;
			})});
		break;
	}
	case 999://篝火part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_HIT_POINTS, player_data.max_hp * 0.25, 20, 15),
				e_action(explore_action_type::EVENT_BODY, event_type::PROCEED, END, static_cast<int>(MEANINGLESS_VALUE), 15)});
	}
	case 1000://篝火part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::UPGRADE_CARD_FROM_DECK, 1, 9),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, static_cast<int>(MEANINGLESS_VALUE), 16)});
	}
	case 2://苹果树
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 1),
				e_action(explore_action_type::SELECTION, event_type::AQUIRE_HIT_POINTS, 20, 1, 1),
				e_action(explore_action_type::SELECTION, event_type::AQUIRE_FOOD, 3, 2, 2),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 3),
				e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		break;
	}
	case 3://酒馆
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 2),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1003, 3),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 4), });
		break;
	}
	case 1003://酒馆part2 
	{
		if (re.chance_luck_decrease(30))
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 3),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1004, 4)});
		}
		else
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 4),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1005, 5, MEANINGLESS_VALUE, [](data_sys* d)->bool {if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1006, 6, MEANINGLESS_VALUE, [](data_sys* d)->bool {if (d->gold >= 50)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1007, 7, MEANINGLESS_VALUE, [](data_sys* d)->bool {if (d->gold >= 75 && d->cards_pool.size() > 0)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 5)});
		}
		break;
	}
	case 1004://酒馆part3
	{
		info_to_explore_sys result(my_vector<e_action>{e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(1, 4)),
			e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(12, 15))});
		if (re.chance(50))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(1, 4)));
		}
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(5, 5)));
		}
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(16, 17)));
		}
		result.append(e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, BONUS));
		result.append(e_action(explore_action_type::SELECTION, event_type::START_BATTLE, MEANINGLESS_VALUE, 4));
		return result;
		break;
	}
	case 1005://酒馆part3
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_HIT_POINTS, 15, 5),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 5)});
		break;
	}
	case 1006://酒馆part3
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 50),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_MAX_HIT_POINTS, 8, 6),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 5)});
		break;
	}
	case 1007://酒馆part3
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 75),
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_CARD_FROM_DECK, 1, 7),
			e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, static_cast<int>(MEANINGLESS_VALUE), 6)});

		break;
	}
	case 4://升级神龛
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 8),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1008, 8, MEANINGLESS_VALUE,
					[](data_sys* t)->bool
			{
				for (auto i : t->cards_pool)
				{
					if (i.upgrade_version_id)
					{
						return true;
					}
				}
				return false;
			}),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 7)});
		break;
	}
	case 1008://升级神龛part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::UPGRADE_CARD_FROM_DECK, 1, 9),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, static_cast<int>(MEANINGLESS_VALUE), 8)});
	}
	case 5://遗忘神龛
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 10),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1009, 8, MEANINGLESS_VALUE,
					[](data_sys* t)->bool {if (t->cards_pool.size() >= 0) return true; return false; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 7)});
		break;
	}
	case 1009://遗忘神龛part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_CARD_FROM_DECK, 1, 11),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, static_cast<int>(MEANINGLESS_VALUE), 8)});
	}
	case 6://变化神龛
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 12),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1010, 8, MEANINGLESS_VALUE,
					[](data_sys* t)->bool {if (t->cards_pool.size() >= 0) return true; return false; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 7)});
		break;
	}
	case 1010://变化神龛part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::CHANGE_CARD_FROM_DECK, 1, 13),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, static_cast<int>(MEANINGLESS_VALUE), 8)});
	}
	case 7://战士雕像
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 14),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1011, 9, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 9), });
		break;
	}
	case 1011://战士雕像part2
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_STRENGTH, 1, 15),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 10)});
	}
	case 8://骑士雕像
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 16),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1012, 9, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 9), });
		break;
	}
	case 1012://骑士雕像part2
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_VITALITY, 1, 17),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 10)});
	}
	case 9://盗贼雕像
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 18),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1013, 9, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 9), });
		break;
	}
	case 1013://盗贼雕像part2
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_DEXTERITY, 1, 19),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 10)});
	}
	case 10://吟游诗人雕像
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 20),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1014, 9, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 9), });
		break;
	}
	case 1014://吟游诗人雕像part2
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_LUCK, 1, 21),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 10)});
	}
	case 11://许愿井
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 22),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1015, 10, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 11), });
		break;
	}
	case 1015://许愿井part2
	{
		if (re.chance_luck_increase(25))
		{
			event_is_not_mandetory = true;
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, 23),
					e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT,
						artifact(re.get_num(1, MAX_ARTIFACT_NO)), MEANINGLESS_VALUE, 12),
					e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		}
		else
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, 24),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1016, 11, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 13), });
		}
		break;
	}
	case 1016://许愿井part3
	{
		if (re.chance_luck_increase(25))
		{
			event_is_not_mandetory = true;
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, 23),
					e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT,
						artifact(re.get_num(1, MAX_ARTIFACT_NO)), MEANINGLESS_VALUE, 12),
					e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		}
		else
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, 25),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1016, 11, MEANINGLESS_VALUE, [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 14), });
		}
		break;
	}
	case 12://拥挤的人群
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 26),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1017, 12),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1018, 13)});
		break;
	}
	case 1017://拥挤的人群part2
	{
		if (dexterity >= 1)
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REVEAL_MAP, 3, 27),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 14)});
		}
		else if (re.chance(25))
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REVEAL_MAP, 3, 28),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 14)});
		}
		else
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 50, 29),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 14)});
		}
		break;
	}
	case 1018://拥挤的人群part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_FOOD, 2, 30),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 14)});
	}
	case 13://扳手腕
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 31),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1019, 15),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1020, 16)});
		break;
	}
	case 1019://扳手腕part2
	{
		if (strength >= 1)
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_GOLD, 100, 32),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 17, 17)});
		}
		else if (re.chance(25))
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_GOLD, 100, 32),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 17, 17)});
		}
		else
		{
			return info_to_explore_sys(my_vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_HIT_POINTS, 10, 33),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0, 18)});
		}
		break;
	}
	case 1020://扳手腕part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 50, 34),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0)});
	}
	case 14://瞭望塔
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 35),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1021, 18),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0)});
	}
	case 1021://瞭望塔part2
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REVEAL_MAP, 5, 36),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, 0)});
	}
	case 15://山贼
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 37),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, 1022, 4)});
		break;
	}
	case 1022://山贼part2
	{
		info_to_explore_sys result(my_vector<e_action>{
			e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(1, 1)),
				e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(1, 1)),
				e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(12, 15))});
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(5, 5)));
		}
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(16, 17)));
		}
		result.append(e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, BONUS));
		result.append(e_action(explore_action_type::EVENT_BODY, event_type::START_BATTLE, MEANINGLESS_VALUE, 4));
		return result;
		break;
	}
	case 16://哨所
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 38),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, 1023, 4)});
		break;
	}
	case 1023://哨所part2
	{
		info_to_explore_sys result(my_vector<e_action>{
			e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(6, 9)),
				e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(46, 47))});
		if (re.chance(20))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(48, 48)));
		}
		if (re.chance(20))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(10, 11)));
		}
		if (re.chance(10))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(33, 34)));
		}
		result.append(e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, BONUS));
		result.append(e_action(explore_action_type::EVENT_BODY, event_type::START_BATTLE, MEANINGLESS_VALUE, 4));
		return result;
		break;
	}
	case 17://珊瑚洞窟
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 39),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, 1024, 4)});
		break;
	}
	case 1024://珊瑚洞窟part2
	{
		info_to_explore_sys result(my_vector<e_action>{
			e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(36, 39)),
				e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(41, 44))});
		if (re.chance(40))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(40, 45)));
		}
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(31, 32)));
		}
		if (re.chance(25))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(35, 35)));
		}
		result.append(e_action(explore_action_type::SELECTION, event_type::START_BATTLE, MEANINGLESS_VALUE, 4));
		result.append(e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, BONUS));
		return result;
		break;
	}
	case 18://地窖
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 40),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, 1024, 4)});
		break;
	}
	case 1025://地窖洞窟part2
	{
		info_to_explore_sys result(my_vector<e_action>{
			e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(18, 24)),
				e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(18, 24))});
		if (re.chance(80))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(18, 24)));
		}
		if (re.chance(30))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(25, 30)));
		}
		if (re.chance(20))
		{
			result.append(e_action(explore_action_type::ENEMY, MEANINGLESS_VALUE, re.get_num(25, 30)));
		}
		result.append(e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, BONUS));
		result.append(e_action(explore_action_type::SELECTION, event_type::START_BATTLE, MEANINGLESS_VALUE, 4));
		return result;
		break;
	}
	case 19://珍珠贝
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 41),
			e_action(explore_action_type::SELECTION, event_type::AQUIRE_GOLD, card(309), re.get_num(35, 85)),
			e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT, artifact(re.get_num(1, 15))),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END),
			e_action(explore_action_type::MAX_SELECTION, MEANINGLESS_VALUE, 999),
			e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		break;
	}
	case 20://马车
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 42),
			e_action(explore_action_type::SELECTION, event_type::AQUIRE_FOOD, card(308), re.get_num(2, 5)),
			e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT, artifact(re.get_num(1, 15))),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END),
			e_action(explore_action_type::MAX_SELECTION, MEANINGLESS_VALUE, 999),
			e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		break;
	}
	case 21://皇家图书馆
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 43, 19),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, 1026, 19),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, 1026)});
		break;
	}
	case 1026://皇家图书馆part2
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 44),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_CARD_FROM_SELECTION, 5),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, 1027),
			e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		break;
	}
	case 1027://皇家图书馆part3
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 45),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_CARD_FROM_SELECTION, 5),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, 1028),
			e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		break;
	}
	case 1028://皇家图书馆part4
	{
		return info_to_explore_sys(my_vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 46),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_CARD_FROM_SELECTION, 5),
			e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END),
			e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		break;
	}
	case BONUS:
	{
		return info_to_explore_sys(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_CARD_FROM_SELECTION, 3, 47),
				e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, BONUS_PART2),
				e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
	}
	case BONUS_PART2:
	{
		info_to_explore_sys result(my_vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, 48),
				e_action(explore_action_type::SELECTION, event_type::AQUIRE_GOLD, card(309), re.get_num(35, 85)),
				e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END),
				e_action(explore_action_type::MAX_SELECTION, MEANINGLESS_VALUE, 999),
				e_action(explore_action_type::EVENT_BODY, event_type::SET_MANDETORY, MEANINGLESS_VALUE)});
		if (re.chance_luck_increase(40))
		{
			result.append(e_action(explore_action_type::SELECTION, event_type::AQUIRE_FOOD, card(308), re.get_num(1, 3)));
		}
		if (re.chance_luck_increase(10))
		{
			result.append(e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT, artifact(re.get_num(1, 15))));
		}
		return result;
	}
	case END:
	{
		return info_to_explore_sys(e_action(explore_action_type::END_EVENT));
	}
	default:
		return info_to_explore_sys();
	}
}

info_to_battle_sys data_sys::enemy_battle_start(std::size_t enemy_id)
{
	return info_to_battle_sys();
}

info_to_battle_sys data_sys::enemy_act(std::size_t pos)
{
	switch (enemies_data[pos].enemy_id)
	{
	case 1:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 402)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		}
		break;
	}
	case 2:
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::LOADED, 1)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12));
		}
		break;
	}
	case 3:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
			action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		break;
	}
	case 4:
	{
		if (has_other_enemy(pos))
		{
			if (re.chance(75))
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[re.get_other_enemy(pos)], buff_type::ARMOR, 10)});
			}
			else
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
			}
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));
		}
		break;
	}
	case 5:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		else
		{
			info_to_battle_sys result(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0));
			for (int i = 0; i < enemies_data.size(); ++i)
			{
				if (i != pos)
				{
					result.append(action(battle_action_type::ADD_BUFF, &enemies_data[pos],
						&enemies_data[i], buff_type::STRENGTH, 2));
				}
			}
			return result;
		}
		break;
	}
	case 6:
	{
		if (re.chance(50))
		{
			return action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6);;
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		break;
	}
	case 7:
	{
		if (re.chance(50))
		{
			return action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 7);
			return action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2);
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		}
		break;
	}
	case 8:
	{
		if (has_other_enemy(pos))
		{
			int target = re.get_other_enemy(pos);
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[target], buff_type::ARMOR, 15),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[target], buff_type::STRENGTH, 2)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));
		}
		break;
	}
	case 9:
	{
		if (has_other_enemy(pos))
		{
			if (re.chance(50))
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
					action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &enemies_data[re.get_other_enemy(pos)], type_type::ADD_HP, 16)});
			}
			else
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 1)});
			}
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));
		}
		break;
	}
	case 10:
	{
		if (passed_turns == 0)
		{
			info_to_battle_sys result(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0));
			for (int i = 0; i < enemies_data.size(); ++i)
			{
				result.append(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[i], buff_type::STRENGTH, 2));
			}
			return result;
		}
		else
		{
			if (re.chance(50))
			{
				info_to_battle_sys result(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0));
				for (int i = 0; i < enemies_data.size(); ++i)
				{
					result.append(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &enemies_data[i], type_type::ADD_HP, 10));
				}
				return result;
			}
			else
			{
				return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6));
			}
		}
		break;
	}
	case 11:
	{
		if (has_other_enemy(pos))
		{
			if (passed_turns % 3 == 0)
			{
				for (int i = 0; i < enemies_data.size(); ++i)
				{
					return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
						action(battle_action_type::ADD_BUFF, &enemies_data[i], &enemies_data[i], buff_type::ARMOR, 10),
						action(battle_action_type::ADD_BUFF, &enemies_data[i], &enemies_data[i], buff_type::STRENGTH, 2)});
				}
			}
			else
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 15),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
			}
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10)});;
		}
		break;
	}
	case 12:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 1)});
		}
		break;
	}
	case 13:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 14));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		break;
	}
	case 14:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 2),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 2)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12));
		}
		break;
	}
	case 15:
	{
		if (re.chance(75))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN, 3)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 3),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN, 3)});
		}
		break;
	}
	case 16:
	{
		if (passed_turns % 3 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10)});
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		}
		break;
	}
	case 17:
	{
		if (re.chance(75))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::REDUCE_AP, 1), });
		}
		break;
	}
	case 18:
	{
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6));
		break;
	}
	case 19:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
			action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 402)});
		break;
	}
	case 20:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4)});
		}
		break;
	}
	case 21:
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::LOADED, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 402)});
			break;
		}
		break;
	}
	case 22:
	{
		if (has_other_enemy(pos))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[re.get_other_enemy(pos)], buff_type::STRENGTH, 2)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));
		}
		break;
	}
	case 23:
	{
		if (has_other_enemy(pos))
		{
			if (re.chance(50))
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[re.get_other_enemy(pos)], buff_type::ARMOR, 10)});
			}
			else
			{
				return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
			}
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6));
		}
		break;
	}
	case 24:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		break;
	}
	case 25:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 402),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 402),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 402),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 402)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 20));
		}
		break;
	}
	case 26:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::CULTIST_RITE, 3)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3));
		}
		break;
	}
	case 27:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN_CURSE, 3)});
		}
		else if (re.chance(40))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		break;
	}
	case 28:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::CULTIST_RITE, 3)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1)});
			break;
		}
		break;
	}
	case 29:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN_CURSE, 3)});
		}
		else if (passed_turns == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 99)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 20));
		}
		break;
	}
	case 30:
	{
		if (passed_turns % 4 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 404),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 404),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 404)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 404)});
		}
		break;
	}
	case 31:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));

		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		}
		break;
	}
	case 32:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::FEAST, 5)});
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 2),
				action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::DEXTERITY, 2)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		break;
	}
	case 33:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		break;
	}
	case 34:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 2)});
		break;
	}
	case 35:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 402),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 402)});
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::STRENGTH, 1),
				action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::DEXTERITY, 1),
				action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::VITALITY, 1)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 18));
		}
		break;
	}
	case 36:
	{
		return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 1)});
		break;
	}
	case 37:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 405)});
		}
		break;
	}
	case 38:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 406)});
		}
		break;
	}
	case 39:
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ARMOR, 10)});
		}
		break;
	}
	case 40:
	{
		if (passed_turns % 4 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 14),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::REDUCE_AP, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 405),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 405)});
		}
		break;
	}
	case 41:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::REDUCE_AP, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CHAIN, 3)});
		}
		break;
	}
	case 42:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 15));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8),
				action(battle_action_type::ADD_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 405)});
		}
		break;
	}
	case 43:
	{
		if (re.chance(60))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4)});
		}
		break;
	}
	case 44:
	{
		if (re.chance(60))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ARMOR, 20),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 15));
		}
		break;
	}
	case 45:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::SHELL, 8)});
		}
		else if (re.chance(60))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 20));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		break;
	}
	case 46:
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::MARK, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 3)});
		}
		break;
	}
	case 47:
	{
		if (player_data.has_buff(buff_type::MARK))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 18));
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5));
		}
		break;
	}
	case 48:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ANGER, 1)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 20));
		}
		break;
	}
	case 49:
	{
		if (re.chance(33))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 3)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 0),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 1)});
		}
		break;
	}
	case 50:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::FEAST, 2));
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 4));
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3)});
		}
		break;
	}
	case 51:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::FEAST, 3));
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 4)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		}
	}
	case 52:
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403)});
		}
		break;
	}
	case 53:
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 1)});
		}
		else
		{
			return info_to_battle_sys(my_vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 403)});
		}
		break;
	}
	default:
		break;
	}
	return info_to_battle_sys();
}

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	switch (id)
	{
	case buff_type::STRENGTH:
		return pair<string, size_t>(string("strength"), 1);
	case buff_type::DEXTERITY:
		return pair<string, size_t>(string("agility"), 2);
	case buff_type::VITALITY:
		return pair<string, size_t>(string("vitality"), 1);
	case buff_type::ARMOR:
		return pair<string, size_t>(string("armor"), 2);
	case buff_type::WEAK:
		return pair<string, size_t>(string("weak"), 1);
	case buff_type::VULNERABLE:
		return pair<string, size_t>(string("vulnerable"), 2);
	case buff_type::FRAGILE:
		return pair<string, size_t>(string("fragile"), 2);
	case buff_type::BURN:
		return pair<string, size_t>(string("burn"), 1);
	case buff_type::POISON:
		return pair<string, size_t>(string("poison"), 3);
	case buff_type::BLEED:
		return pair<string, size_t>(string("bleed"), 4);
	case buff_type::USED_ATTACK_CARDS:
		return pair<string, size_t>(string("use_atk_c"), 1);
	case buff_type::USED_SKILL_CARDS:
		return pair<string, size_t>(string("use_ski_c"), 1);
	case buff_type::USED_ABILITY_CARDS:
		return pair<string, size_t>(string("use_abi_c"), 1);
	case buff_type::EXHAUST:
		return pair<string, size_t>(string("exhaust"), 3);
	case buff_type::CHAIN:
		return pair<string, size_t>(string("chain"), 3);
	case buff_type::MOVE_MUSSLE:
		return pair<string, size_t>(string("move_mussle"), 3);
	case buff_type::STUN:
		return pair<string, size_t>(string("stun"), 4);
	case buff_type::STUN_RESIST:
		return pair<string, size_t>(string("stun_resist"), 4);
	case buff_type::EXPLODE:
		return pair<string, size_t>(string("EXPLODE"), 5);
	case buff_type::PASSED_TURNS:
		return pair<string, size_t>(string("PASSED_TURNS"), 4);
	case buff_type::INCREASE_DRAW:
		return pair<string, size_t>(string("INCREASE_DRAW"), 3);
	case buff_type::REDUCE_AP:
		return pair<string, size_t>(string("REDUCE_AP"), 4);
	case buff_type::INCREASE_AP:
		return pair<string, size_t>(string("INCREASE_AP"), 5);
	case buff_type::ETERNAL_FURY:
		return pair<string, size_t>(string("ETERNAL_FURY"), 3);
	case buff_type::INVULNARABLE:
		return pair<string, size_t>(string("invulnarable"), 3);
	case buff_type::FIGHTING_SPIRIT:
		return pair<string, size_t>(string("fighting_spirit"), 3);
	case buff_type::FRENZY:
		return pair<string, size_t>(string("frenzy"), 4);
	case buff_type::RITE:
		return pair<string, size_t>(string("rite"), 4);
	case buff_type::RESUSCITATE:
		return pair<string, size_t>(string("resuscitate"), 5);
	case buff_type::ABILITY_BURN:
		return pair<string, size_t>(string("ability_burn"), 3);
	case buff_type::SCORCHED_EARTH:
		return pair<string, size_t>(string("scorched_earth"), 3);
	case buff_type::SHELL:
		return pair<string, size_t>(string("SHELL"), 5);
	case buff_type::LOADED:
		return pair<string, size_t>(string("LOADED"), 4);
	case buff_type::PAIN:
		return pair<string, size_t>(string("PAIN"), 3);
	case buff_type::CULTIST_RITE:
		return pair<string, size_t>(string("CULTIST_RITE"), 4);
	case buff_type::PAIN_CURSE:
		return pair<string, size_t>(string("PAIN_CURSE"), 5);
	case buff_type::CORRUPT:
		return pair<string, size_t>(string("CORRUPT"), 3);
	case buff_type::FEAST:
		return pair<string, size_t>(string("FEAST"), 3);
	case buff_type::MARK:
		return pair<string, size_t>(string("MARK"), 3);
	case buff_type::ANGER:
		return pair<string, size_t>(string("sANGER"), 3);
	default:
		return pair<string, size_t>(string("id can not found"), 6);
#ifdef _DEBUG
		//throw exception("failed to find buff id");
#endif // _DEBUG

	}
}

bool data_sys::has_other_enemy(std::size_t pos)
{
	for (int i = 0; i < enemies_data.size(); ++i)
	{
		if (enemies_data[i].is_alive() && i != pos)
			return true;
	}
	return false;
}

int data_sys::get_enemy(std::size_t enemy_id)
{
	switch (enemy_id)
	{
	case 1:
	default:
		return 1;
	}
}

IMAGE & data_sys::get_pic(int id, int det)
{
	switch (det)
	{
	case 0:
		return cards_thumbnail[id];
		break;
	case 1:
		return artifact_pics[id];
		break;
	default:
		return cards_thumbnail[402];
	}
}

IMAGE & data_sys::get_mask_pic(int id, int det)
{
	switch (det)
	{
	case 0:
		int mask;
		if ((id > 0 && id <= 29) || (id > 60 && id <= 89))
		{
			mask = 2;
		}
		else if ((id > 29 && id <= 51) || (id > 89 && id <= 111))
		{
			mask = 1;
		}
		else if (id == 308 || id == 309)
		{
			mask = 4;
		}
		else if (id < 400)
		{
			mask = 0;
		}
		else
		{
			mask = 3;
		}
		return cards_mask[mask];
		break;
	case 1:
		return artifact_pics[0];
	default:
		return cards_mask[3];
	}
}

IMAGE & data_sys::get_entity_pic(int id, int status)
{
	switch (id)
	{
	case 0:
		return entities[status];
		break;
	case 1: case 2: case 3:case 4: case 12: case 13: case 14: case 15:
		return entities[10 + status];
		break;
	case 5: case 16: case 17:
		return entities[13 + status];
		break;
	case 6: case 7: case 8: case 9: case 46: case 47: case 33: case 34:
		return entities[4 + status];
		break;
	case 10: case 11: case 48:
		return entities[7 + status];
		break;
	case 18: case 19: case 20: case 21: case 22: case 23: case 24:
		return entities[25 + status];
		break;
	case 25: case 26: case 27: case 28: case 29: case 30:
		return entities[22 + status];
		break;
	case 36: case 37: case 38: case 39: case 41: case 42: case 43: case 44:
		return entities[16 + status];
		break;
	case 40: case 45: case 31: case 32: case 35:
		return entities[19 + status];
		break;
	default:
		return entities[10 + status];
		break;
	}
}

IMAGE & data_sys::get_entity_mask_pic(int id, int status)
{
	switch (id)
	{
	case 0:
		return entities[28 + status];
		break;
	case 1: case 2: case 3:case 4: case 12: case 13: case 14: case 15:
		return entities[37 + status];
		break;
	case 5: case 16: case 17:
		return entities[40 + status];
		break;
	case 6: case 7: case 8: case 9: case 46: case 47: case 33: case 34:
		return entities[31 + status];
		break;
	case 10: case 11: case 48:
		return entities[34 + status];
		break;
	case 18: case 19: case 20: case 21: case 22: case 23: case 24:
		return entities[52 + status];
		break;
	case 25: case 26: case 27: case 28: case 29: case 30:
		return entities[49 + status];
		break;
	case 36: case 37: case 38: case 39: case 41: case 42: case 43: case 44:
		return entities[43 + status];
		break;
	case 40: case 45: case 31: case 32: case 35:
		return entities[46 + status];
		break;
	default:
		return entities[38 + status];
		break;
	}
}

IMAGE & data_sys::get_buff_pic(int id)
{
	switch (id)
	{
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		return buff_pics[id - 1];
		break;
	case 14: case 15:case 16: case 17:case 19: case 22: case 34: case 36: case 37: case 39:
		return buff_pics[8];
		break;
	case 18: case 21: case 23:case 33: case 35:case 38: case 40:
		return buff_pics[10];
		break;
	default:
		return buff_pics[9];
		break;
	}
}

IMAGE & data_sys::get_buff_mask_pic(int id)
{
	switch (id)
	{
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
		return buff_pics[id + 10];
		break;
	case 14: case 15:case 16: case 17:case 19: case 22: case 34: case 36: case 37: case 39:
		return buff_pics[19];
		break;
	case 18: case 21: case 23:case 33: case 35:case 38: case 40:
		return buff_pics[21];
		break;
	default:
		return buff_pics[20];
		break;
	}
}

info_to_explore_sys data_sys::artifact_on_create(std::size_t atf_id)
{
	switch (atf_id)
	{
	case 1:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_STRENGTH, 1));
		break;
	case 2:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_DEXTERITY, 1));
		break;
	case 3:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_VITALITY, 1));
		break;
	case 4:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_LUCK, 1));
		break;
	case 5:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_MAX_HIT_POINTS, 8));
		break;
	default:
		return info_to_explore_sys();
		break;
	}
}

info_to_explore_sys data_sys::artifact_on_remove(std::size_t atf_id)
{
	switch (atf_id)
	{
	case 1:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_STRENGTH, 1));
		break;
	case 2:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_DEXTERITY, 1));
		break;
	case 3:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_VITALITY, 1));
		break;
	case 4:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_LUCK, 1));
		break;
	case 5:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_MAX_HIT_POINTS, 8));
		break;
	default:
		return info_to_explore_sys();
		break;
	}
}

info_to_explore_sys data_sys::artifact_on_encounter_event(std::size_t atf_id)
{
	return info_to_explore_sys();
}

info_to_explore_sys data_sys::artifact_on_event_body(std::size_t atf_id)
{
	return info_to_explore_sys();
}

info_to_battle_sys data_sys::artifact_on_start_battle(std::size_t atf_id)
{
	switch (atf_id)
	{
	case 6:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &player_data, buff_type::STRENGTH, 1));
		break;
	case 7:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &player_data, buff_type::DEXTERITY, 1));
		break;
	case 8:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &player_data, buff_type::VITALITY, 1));
		break;
	case 9:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &player_data, buff_type::ARMOR, 10));
		break;
	case 10:
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &player_data, &player_data, type_type::ADD_HP, 3));
		break;
	case 11:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &all_enemies, buff_type::VULNERABLE, 1));
		break;
	case 12:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &player_data, &all_enemies, buff_type::WEAK, 1));
		break;
	case 13:
		return info_to_battle_sys(action(battle_action_type::DRAW_CARDS, &player_data, &player_data, MEANINGLESS_VALUE, 2));
		break;
	case 14:
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &player_data, &player_data, type_type::ADD_AP, 1));
		break;
	case 15:
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &player_data, &all_enemies, type_type::INDEPENDENT, 5));
		break;
	default:
		return info_to_battle_sys();
		break;
	}
}

info_to_explore_sys data_sys::artifact_on_end_event(std::size_t atf_id)
{
	switch (atf_id)
	{
	case 16:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_GOLD, 25));
		break;
	case 17:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_FOOD, 1));
		break;
	case 18:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_MAX_HIT_POINTS, 1));
		break;
	case 19:
		return info_to_explore_sys();
		break;
	case 20:
		return info_to_explore_sys(e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_HIT_POINTS, 3));
		break;
	default:
		return info_to_explore_sys();
		break;
	}
}

void data_sys::create_starting_deck()
{
	cards_pool.clear();
	cards_pool.push_back(card(1));
	cards_pool.push_back(card(1));
	cards_pool.push_back(card(21));
	cards_pool.push_back(card(2));
	cards_pool.push_back(card(3));
	cards_pool.push_back(card(4));
	cards_pool.push_back(card(4));
	cards_pool.push_back(card(4));
	cards_pool.push_back(card(52));
	cards_pool.push_back(card(7));
	cards_pool.push_back(card(14));
	cards_pool.push_back(card(107));
	artifacts.clear();
	artifacts.push_back(artifact(6));
}

random_engine::random_engine(data_sys * d)
	:data(d), e(static_cast<int>(time(0)))
{
}

size_t random_engine::get_num(int lb, int ub)
{
	uniform_int_distribution<int> ran(lb, ub);
	int result = ran(e);
	return result;
}

size_t random_engine::get_enemy()
{
	uniform_int_distribution<int> ran(0, data->enemies_data.size());
	while (true)
	{
		int result = ran(e);
		if (data->enemies_data[result].is_alive())
		{
			return result;
		}
	}
}

size_t random_engine::get_other_enemy(int pos)
{
	uniform_int_distribution<int> ran(0, data->enemies_data.size() - 1);//<-are you fucking kidding me?
	//fuck!!!
	while (true)
	{
		int result = ran(e);
		if (result != pos && data->enemies_data[result].is_alive())
		{
			return result;
		}
	}
}

bool random_engine::chance(std::size_t target)
{
	uniform_int_distribution<int> ran(0, 100);
	int result = ran(e);
	if (target > result)
	{
		return true;
	}
	return false;
}

bool random_engine::chance_luck_increase(std::size_t target)
{
	uniform_int_distribution<int> ran(0, 100);
	int result = ran(e);
	if (target + (10 * data->luck) > result)
	{
		return true;
	}
	return false;
}

bool random_engine::chance_luck_decrease(std::size_t target)
{
	uniform_int_distribution<int> ran(0, 100);
	int result = ran(e);
	if (target - (10 * data->luck) > result)
	{
		return true;
	}
	return false;
}
