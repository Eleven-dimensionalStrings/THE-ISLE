#include "data_sys.h"
#include <random>
#include <ctime>
#include "battle_system.h"
using namespace std;

//TODO 6, 8，9, 12

data_sys::data_sys() :b(nullptr), player_data(*this), all_enemies(*this, MEANINGLESS_VALUE), random_enemy(*this, MEANINGLESS_VALUE)
, select_one_enemy(*this, MEANINGLESS_VALUE), re(this)
{
	for (auto&i : render_select_card)i = 0;
}

info_to_battle_sys data_sys::card_effect(std::size_t id)
{
	switch (id)
	{
	case 1://打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 6)});
		break;
	}
	case 2://纵斩
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 3://痛击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2)});
		break;
	}
	case 4://上撩斩
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2)});
		break;
	}
	case 5://突刺
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4)});
		break;
	}
	case 6://下劈斩
	{
		info_to_battle_sys result(action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12));
		if (cards_in_hand.size() > 0)
		{
			result.append(action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, re.get_num(0, cards_in_hand.size() - 1)));
		}
		return result;
		break;
	}
	case 7://横挥
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &all_enemies, type_type::NORMAL, 6)});
		break;
	}
	case 8://旋风斩
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 8)});
		break;
	}
	case 9://突破
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 10://过肩摔
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 2)});
		break;
	}
	case 11://湮灭
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 36)});
		break;
	}
	case 12://蓄力劈砍
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::WAR_12, 12)});
		break;
	}
	case 13://无谋打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::ADD_BUFF
							, &player_data, &player_data, buff_type::VULNERABLE, 1)});
		break;
	}
	case 14://散华
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 2)});
		break;
	}
	case 15://全力打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 16://猛冲
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 17://混战
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001)});
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 12)});
		break;
	}
	case 20://竭力打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001)});
		break;
	}
	case 21://灼热打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::FLAME, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 22://沸血打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::FLAME, 8), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 23://火焰风暴
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::ADD_BUFF
						, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
							, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::ADD_BUFF
								, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
									, &player_data, &all_enemies, type_type::FLAME, 4), action(battle_action_type::ADD_BUFF
										, &player_data, &all_enemies, buff_type::BURN, 2)});
		break;
	}
	case 24://火焰漩涡
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::BURN, 1), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
						, &player_data, &all_enemies, buff_type::BURN, 1)});
		break;
	}
	case 25://火蛇
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &random_enemy, type_type::FLAME, 3)});
		break;
	}
	case 26://引爆
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::EXPLODE, 3)});
		break;
	}
	case 27://肩撞
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 1)});
		break;
	}
	case 28://上勾拳
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 6) });
		break;
	}
	case 29://下马威
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1) });
		break;
	}
	case 30://防御
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 5) });
		break;
	}
	case 31://盾牌格挡
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1) });
		break;
	}
	case 32://武装
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10) });
		break;
	}
	case 33://挑衅
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1) });
		break;
	}
	case 34://固守
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 15), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 1001), action(battle_action_type::ADD_CARD_TO_DECK
						, MEANINGLESS_VALUE, 1001) });
		break;
	}
	case 35://磨刀
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1)});
		break;
	}
	case 36://重整旗鼓
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::STRENGTH, 1), action(battle_action_type::ADD_BUFF
						, &player_data, &player_data, buff_type::MOVE_MUSSLE, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
		}
		break;
	}
	case 38://交锋
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1) });

		break;
	}
	case 39://战意
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2) });
		break;
	}
	case 40://白热化
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
			, &player_data, &player_data, MEANINGLESS_VALUE, 3), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 1001) });
		break;
	}
	case 41://怒吼
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &all_enemies, buff_type::VULNERABLE, 1), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1) });
		break;
	}
	case 42://神之力量
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 10), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 10) });
		break;
	}
	case 43://突破极限
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, player_data.has_buff(buff_type::STRENGTH)) });
		break;
	}
	case 44://盛怒
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 45://放血
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &player_data, type_type::ADD_AP, 1) });
		break;
	}
	case 46://祭品
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2) });
		break;
	}
	case 47://引燃
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::BURN, 5)});
		break;
	}
	case 48://火之印
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 2)});
		break;
	}
	case 49://激怒
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 2)});
		break;
	}
	case 50://缴械
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::REMOVE_BUFF
			, &player_data, &select_one_enemy, buff_type::STRENGTH, 2)});
		break;
	}
	case 51://威吓
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 5), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 52://利刃研磨
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2)});
		break;
	}
	case 53://无尽愤怒
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ETERNAL_FURY, 2)});
		break;
	}
	case 54://无懈可击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::INVULNARABLE, 10)});
		break;
	}
	case 55://斗志
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FIGHTING_SPIRIT, 1)});
		break;
	}
	case 56://狂暴
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FRENZY, 1)});
		break;
	}
	case 57://仪式
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RITE, 1)});
		break;
	}
	case 58://活力再生
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RESUSCITATE, 0)});
		break;
	}
	case 59://燃烧
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ABILITY_BURN, 1)});
		break;
	}
	case 60://焦土
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::SCORCHED_EARTH, 2)});
		break;
	}
	case 61://打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 62://纵斩+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14)});
		break;
	}
	case 63://痛击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 3)});
		break;
	}
	case 64://上撩斩+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2)});
		break;
	}
	case 65://突刺+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 4)});
		break;
	}
	case 66://下劈斩+
	{
		info_to_battle_sys result(action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 16));
		if (cards_in_hand.size() > 0)
		{
			result.append(action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, re.get_num(0, cards_in_hand.size() - 1)));
		}
		return result;
		break;
	}
	case 67://横挥+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 10)});
		break;
	}
	case 68://旋风斩+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10)});
		break;
	}
	case 69://突破+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &all_enemies, buff_type::WEAK, 2)});
		break;
	}
	case 70://过肩摔+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 3)});
		break;
	}
	case 71://湮灭+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 42)});
		break;
	}
	case 72://蓄力劈砍+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::WAR_12_PLUS, 12)});
		break;
	}
	case 73://无谋打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::ADD_BUFF
							, &player_data, &player_data, buff_type::VULNERABLE, 1)});
		break;
	}
	case 74://散华+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 2), action(battle_action_type::CALLING_ACTION
							, &player_data, &select_one_enemy, type_type::NORMAL, 2)});
		break;
	}
	case 75://全力打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 76://猛冲+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 16), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::EXHAUST, 4)});
		break;
	}
	case 77://混战+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 14), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001)});
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 16)});
		break;
	}
	case 80://竭力打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 16), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001)});
		break;
	}
	case 81://灼热打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::FLAME, 10), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 82://沸血打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::FLAME, 10), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 83://火焰风暴+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::ADD_BUFF
						, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
							, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::ADD_BUFF
								, &player_data, &all_enemies, buff_type::BURN, 2), action(battle_action_type::CALLING_ACTION
									, &player_data, &all_enemies, type_type::FLAME, 5), action(battle_action_type::ADD_BUFF
										, &player_data, &all_enemies, buff_type::BURN, 2)});
		break;
	}
	case 84://火焰漩涡+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::BURN, 1), action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
						, &player_data, &all_enemies, buff_type::BURN, 1), action(battle_action_type::CALLING_ACTION
							, &player_data, &all_enemies, type_type::FLAME, 2), action(battle_action_type::ADD_BUFF
								, &player_data, &all_enemies, buff_type::BURN, 1)});
		break;
	}
	case 85://火蛇+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &random_enemy, type_type::FLAME, 3), action(battle_action_type::CALLING_ACTION
						, &player_data, &random_enemy, type_type::FLAME, 3)});
		break;
	}
	case 86://引爆+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::EXPLODE, 3)});
		break;
	}
	case 87://肩撞+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, 1)});
		break;
	}
	case 88://上勾拳+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 6) });
		break;
	}
	case 89://下马威+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::STUN, 1) });
		break;
	}
	case 90://防御+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8) });
		break;
	}
	case 91://盾牌格挡+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 10), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1) });
		break;
	}
	case 92://武装+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 13) });
		break;
	}
	case 93://挑衅+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 15), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1) });
		break;
	}
	case 94://固守+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 20), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 1001), action(battle_action_type::ADD_CARD_TO_DECK
						, MEANINGLESS_VALUE, 1001) });
		break;
	}
	case 95://磨刀+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 2), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::VULNERABLE, 1)});
		break;
	}
	case 96://重整旗鼓+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::STRENGTH, 3), action(battle_action_type::ADD_BUFF
						, &player_data, &player_data, buff_type::MOVE_MUSSLE, 3)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
		}
		break;
	}
	case 98://交锋+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::VULNERABLE, 1), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2) });

		break;
	}
	case 99://战意+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 4), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 4) });
		break;
	}
	case 100://白热化+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::DRAW_CARDS
			, &player_data, &player_data, MEANINGLESS_VALUE, 3), action(battle_action_type::ADD_CARD_TO_DECK
				, MEANINGLESS_VALUE, 1001), action(battle_action_type::ADD_CARD_TO_DECK
					, MEANINGLESS_VALUE, 1001) });
		break;
	}
	case 101://怒吼+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &all_enemies, buff_type::VULNERABLE, 1), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 2) });
		break;
	}
	case 102://神之力量+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 12), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::MOVE_MUSSLE, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, 8) });
		break;
	}
	case 103://突破极限+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, player_data.has_buff(buff_type::STRENGTH)) });
		break;
	}
	case 104://盛怒+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 105://放血+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &player_data, type_type::ADD_AP, 2) });
		break;
	}
	case 106://祭品+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 3) });
		break;
	}
	case 107://引燃+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::BURN, 5)});
		break;
	}
	case 108://火之印+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &select_one_enemy, buff_type::VULNERABLE, 2), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::BURN, 3)});
		break;
	}
	case 109://激怒+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &player_data, type_type::PURE, 3), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::STRENGTH, 3)});
		break;
	}
	case 110://缴械+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::REMOVE_BUFF
			, &player_data, &select_one_enemy, buff_type::STRENGTH, 3)});
		break;
	}
	case 111://威吓+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ARMOR, 8), action(battle_action_type::ADD_BUFF
				, &player_data, &all_enemies, buff_type::WEAK, 1)});
		break;
	}
	case 112://利刃研磨+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::STRENGTH, 3)});
		break;
	}
	case 113://无尽愤怒+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ETERNAL_FURY, 3)});
		break;
	}
	case 114://无懈可击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::INVULNARABLE, 12)});
		break;
	}
	case 115://斗志+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FIGHTING_SPIRIT, 2)});
		break;
	}
	case 116://狂暴+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::FRENZY, 1)});
		break;
	}
	case 117://仪式+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RITE, 1)});
		break;
	}
	case 118://活力再生+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::RESUSCITATE, 0)});
		break;
	}
	case 119://燃烧+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
			, &player_data, &player_data, buff_type::ABILITY_BURN, 2)});
		break;
	}
	case 120://焦土+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF
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
	case 1004:
		return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, nullptr, &player_data, type_type::INDEPENDENT, 3));
		break;
	case 1005:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, nullptr, &player_data, buff_type::REDUCE_AP, 1));
		break;
	case 1006:
		return info_to_battle_sys(action(battle_action_type::ADD_BUFF, nullptr, &player_data, buff_type::WEAK, 1));
		break;
	default:
		return info_to_battle_sys();
		break;
	}
}

//TODO
info_to_explore_sys data_sys::event_effect(std::size_t id)
{
	switch (id)
	{
	case 1://TODO bonfire
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY
			, event_type::AQUIRE_GOLD, 100, string("天上掉下了金币.")), e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "proceed...")});
		break;
	}
	case 2://苹果树
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "你来到一颗苹果树前，树上结满了青色的苹果."),
				e_action(explore_action_type::SELECTION, event_type::AQUIRE_HIT_POINTS, 20, "吃掉.", "苹果很美味，你感觉到你恢复了一些体力."),
				e_action(explore_action_type::SELECTION, event_type::AQUIRE_FOOD, 3, "收集.", "你收集了一些苹果，然后迅速的离开了."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "\"路边的果子一定不会是甜的\"，你喃喃道."),
				e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		break;
	}
	case 3://酒馆
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "天色渐暗，一间亮着灯的酒馆引起了你的注意."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1003, "推开门."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你很快打消了休息的想法，快步走向黑暗中."), });
		break;
	}
	case 1003://酒馆part2 //TODO ENEMY
	{
		if (re.chance_luck_decrease(25))
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "酒馆里空无一人，你却能感受到视线从阴影中看向你。你熟练地拔出武器."),
					//TODO
					e_action(explore_action_type::SELECTION, event_type::START_BATTLE, 1004, "战斗!")});
		}
		else
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "酒馆里充满了快乐的氛围，你在一个火堆边找了个位置坐下."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1005, "25金币  要一份茴香豆.", "", [](data_sys* d)->bool {if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1006, "50金币  要一只烤鸡.", "", [](data_sys* d)->bool {if (d->gold >= 50)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1007, "75金币  要一桶好酒.", "", [](data_sys* d)->bool {if (d->gold >= 75 && d->cards_pool.size() > 0)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "身体暖和之后，你重新踏上了旅途.")});
		}
		break;
	}
	case 1004://酒馆part3
	{
		//TODO
		break;
	}
	case 1005://酒馆part3
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_HIT_POINTS, 15, "酒馆里的诗人一直在哼哼些奇怪的调子，不过茴香豆很好吃，你的体力恢复了."),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "身体暖和之后，你重新踏上了旅途.")});
		break;
	}
	case 1006://酒馆part3
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 50),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_MAX_HIT_POINTS, 8, "你抓起一只鸡腿，大口地吃了起来，你的生命值上限增加了."),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "身体暖和之后，你重新踏上了旅途.")});
		break;
	}
	case 1007://酒馆part3
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 75),
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_CARD_FROM_DECK, 1, "清晨的第一缕日光唤醒了你，你却怎么也想不起来昨天发生了什么."),
			e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "你的头还是有些晕，不过你很快就收拾好装备继续上路.")});
		break;
	}
	case 4://升级神龛
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "你来到一座红色的神龛前，你感觉到能量不断从神龛中涌出."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1008, "触摸.", "",
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
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "你对这类祭祀器具没有兴趣.")});
		break;
	}
	case 1008://升级神龛part2
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::UPGRADE_CARD_FROM_DECK, 1, "红光环绕你的身体，你感到力量从体内不断涌出."),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "神龛的光渐渐熄灭，你继续踏上旅程.")});
	}
	case 5://遗忘神龛
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "你来到一座绿色的神龛前，你感觉到能量不断从向神龛中灌注."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1009, "触摸.", "",
					[](data_sys* t)->bool {if (t->cards_pool.size() >= 0) return true; return false; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "你对这类祭祀器具没有兴趣.")});
		break;
	}
	case 1009://遗忘神龛part2
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_CARD_FROM_DECK, 1, "绿光环绕你的身体，你感到一些思绪从你的身体中被抽出，吸入神龛中."),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "神龛的光渐渐熄灭，你继续踏上旅程.")});
	}
	case 6://变化神龛
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "你来到一座蓝色的神龛前，你感觉到能量在神龛周围流动."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1010, "触摸.", "",
					[](data_sys* t)->bool {if (t->cards_pool.size() >= 0) return true; return false; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开.", "你对这类祭祀器具没有兴趣.")});
		break;
	}
	case 1010://变化神龛part2
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::CHANGE_CARD_FROM_DECK, 1, "蓝光环绕你的身体，天花板和地板在你的眼前交换了位置."),
				e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "神龛的光渐渐熄灭，你继续踏上旅程.")});
	}
	case 7://战士雕像
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "在前路中央有一座巍峨的战士雕像，雕像手持巨斧怒视前方"),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1011, "献上85金币.", "", [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你对艺术没有兴趣."), });
		break;
	}
	case 1011://战士雕像part2
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_STRENGTH, 1, "你站在雕像前，仰望雕像手中的巨斧。你的脑海中浮现出一位名叫鲍德温的国王的传奇故事。当你回过神来，你发现你的力量增加了."),
			e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "雕像静静的伫在那里，等待着下一个渴望成为传奇的人")});
	}
	case 8://骑士雕像
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "在路边的破庙中有一座华美的骑士雕像，雕像手持长剑好似在为人加冕."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1012, "献上85金币.", "", [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你对艺术没有兴趣."), });
		break;
	}
	case 1012://骑士雕像part2
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_VITALITY, 1, "你跪在雕像前，让长剑贴在你的肩上。你的脑海中浮现出一位名叫雷诺德的十字军的传奇故事。当你回过神来，你发现你的体质增加了."),
			e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "雕像静静的伫在那里，等待着下一个渴望成为传奇的人")});
	}
	case 9://盗贼雕像
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "在路旁的树丛中有一座破旧的盗贼雕像，雕像上隐约还刻着些小字."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1011, "献上85金币.", "", [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你对艺术没有兴趣."), });
		break;
	}
	case 1013://盗贼雕像part2
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_DEXTERITY, 1, "你拨开缠绕着雕像的杂草，尝试解读雕像上的文字。你的脑海中浮现出一位名叫迪斯玛的盗贼的传奇故事。当你回过神来，你发现你的敏捷增加了."),
			e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "雕像静静的伫在那里，等待着下一个渴望成为传奇的人")});
	}
	case 10://吟游诗人雕像
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "一座喷泉的中央伫立着一座吟游诗人的雕像，潺潺的水声好似诗人的吟唱."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1011, "献上85金币.", "", [](data_sys* d)->bool { if (d->gold >= 85)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你对艺术没有兴趣."), });
		break;
	}
	case 1014://吟游诗人雕像part2
	{
		return info_to_explore_sys(vector<e_action>{e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 85),
			e_action(explore_action_type::EVENT_BODY, event_type::AQUIRE_LUCK, 1, "你向喷泉中丢了几枚银币，霎时间，一道彩虹划过了天空。你的脑海中浮现出一位名叫法兰恩的神明的传奇故事， 当你回过神来，你发现你的幸运增加了."),
			e_action(explore_action_type::NEXT_PHASE, MEANINGLESS_VALUE, END, "", "雕像静静的伫在那里，等待着下一个渴望成为传奇的人")});
	}
	case 11://许愿井
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "你来到一口井的边上，井上雕刻着歌唱的天使。看起来这像是一个许愿井."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1015, "投入25金币.", "", [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "只有傻子才会把金币丢进水里."), });
		break;
	}
	case 1015://许愿井part2
	{
		if (re.chance_luck_increase(25))
		{
			event_is_not_mandetory = true;
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, "随着金币沉入水中，一个精致的小物件浮出水面."),
					e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT, artifact(re.get_num(1, MAX_ARTIFACT_NO)), "", "你将宝物装进了包里，继续向前进发."),
					e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		}
		else
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, "金币很快沉入水中，然而并没有什么特殊的事情发生."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1016, "再投入25金币.", "", [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你觉得一口普通的井不值得你浪费时间和金钱."), });
		}
		break;
	}
	case 1016://许愿井part3
	{
		if (re.chance_luck_increase(25))
		{
			event_is_not_mandetory = true;
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, "随着金币沉入水中，一个精致的小物件浮出水面."),
					e_action(explore_action_type::SELECTION, event_type::AQUIRE_ARTIFACT, artifact(re.get_num(1, MAX_ARTIFACT_NO)), "", "你将宝物装进了包里，继续向前进发."),
					e_action(explore_action_type::NEXT_PHASE, event_type::PROCEED, END)});
		}
		else
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 25, "你静静地看着金币沉入水中，这是你第一次意识到金币沉入水中的速度竟然如此之快."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, 1016, "再投入25金币.", "", [](data_sys* d)->bool { if (d->gold >= 25)return 1; return 0; }),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, END, "离开", "你决定在浪费更多金币之前离开这口可恶的井."), });
		}
		break;
	}
	case 12://拥挤的人群
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::PURE_TEXT, MEANINGLESS_VALUE, "前方的关卡排起了长队，拥挤的人群堵住了你的去路."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1017, "强行穿过."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, 1018, "绕路.")});
		break;
	}
	case 1017://拥挤的人群part2
	{
		if (dexterity >= 1)
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REVEAL_MAP, 3, "你迅捷的爬上屋顶，避开了人流。同时，你看清了前方的道路."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, MEANINGLESS_VALUE, "继续前进")});
		}
		else if (re.chance(25))
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REVEAL_MAP, 3, "你很快穿过了人流，同时从一些商人的耳语中了解了附近的情况."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, MEANINGLESS_VALUE, "继续前进")});
		}
		else
		{
			return info_to_explore_sys(vector<e_action>{
				e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_GOLD, 50, "你在人群中艰难的前进，当你最终走出关卡时，你发现你的一部分金币被偷了."),
					e_action(explore_action_type::SELECTION, event_type::PROCEED, MEANINGLESS_VALUE, "继续前进")});
		}
		break;
	}
	case 1018://
	{
		return info_to_explore_sys(vector<e_action>{
			e_action(explore_action_type::EVENT_BODY, event_type::REMOVE_FOOD, 2, "你穿过了一片人迹罕至的森林，这消耗了你的许多物资."),
				e_action(explore_action_type::SELECTION, event_type::PROCEED, MEANINGLESS_VALUE, "继续前进")});
	}

	case END:
	{
		return info_to_explore_sys(e_action(explore_action_type::END_EVENT));
	}
	default:
		break;
	}
}

info_to_battle_sys data_sys::enemy_battle_start(std::size_t enemy_id)
{
	return info_to_battle_sys();
}

//TODO
info_to_battle_sys data_sys::enemy_act(std::size_t pos)
{
	switch (enemies_data[pos].enemy_id)
	{
	case 1:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1002)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8));
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2));
		}
		break;
	}
	case 2:
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::LOADED, 1));
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12));
		}
		break;
	}
	case 3:
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
			action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		break;
	}
	case 4:
	{
		if (has_other_enemy(pos))
		{
			if (re.chance(75))
			{
				return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos],
					&enemies_data[re.get_other_enemy(pos)], buff_type::ARMOR, 10));
			}
			else
			{
				return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		else
		{
			info_to_battle_sys result;
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
			return action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2);
		}
		else
		{
			return action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2);
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos],
				&enemies_data[target], buff_type::ARMOR, 15), action(battle_action_type::ADD_BUFF, &enemies_data[pos],
					&enemies_data[target], buff_type::STRENGTH, 2)});
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
				return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos],
					&enemies_data[re.get_other_enemy(pos)], type_type::ADD_HP, 16));
			}
			else
			{
				return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
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
			info_to_battle_sys result;
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
				info_to_battle_sys result;
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
					return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[i], &enemies_data[i], buff_type::ARMOR, 10),
						action(battle_action_type::ADD_BUFF, &enemies_data[i], &enemies_data[i], buff_type::STRENGTH, 2)});
				}
			}
			else
			{
				return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 15),
					action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
			}
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10)});;
		}
		break;
	}
	case 12:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		break;
	}
	case 14:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 2),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 2)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN, 3)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 3),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN, 3)});
		}
		break;
	}
	case 16:
	{
		if (passed_turns % 3 == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10)});
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16),
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
			action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1002)});
		break;
	}
	case 20:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4)});
		}
		break;
	}
	case 21:
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::LOADED, 1));
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1002)});
			break;
		}
		break;
	}
	case 22:
	{
		if (has_other_enemy(pos))
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos],
				&enemies_data[re.get_other_enemy(pos)], buff_type::STRENGTH, 2));
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
				return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos],
					&enemies_data[re.get_other_enemy(pos)], buff_type::ARMOR, 10));
			}
			else
			{
				return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		break;
	}
	case 25:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1002),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1002),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1002),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1002)});
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
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::CULTIST_RITE, 3));
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
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN_CURSE, 3));
		}
		else if (re.chance(40))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 16));
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		break;
	}
	case 28:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::CULTIST_RITE, 3));
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1)});
			break;
		}
		break;
	}
	case 29:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::PAIN_CURSE, 3));
		}
		else if (passed_turns == 1)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 99));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1004),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1004),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1004)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1004)});
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
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2));
		}
		break;
	}
	case 32:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::FEAST, 5));
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 2),
				action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::DEXTERITY, 2)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6)});
		}
		break;
	}
	case 33:
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2)});
		break;
	}
	case 34:
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
			action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 2)});
		break;
	}
	case 35:
	{
		if (passed_turns == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1002),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1002)});
		}
		else if (passed_turns % 3 == 1)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::REMOVE_BUFF, &enemies_data[pos], &player_data, buff_type::STRENGTH, 1),
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8),
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
			return info_to_battle_sys(action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1005));
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
			return info_to_battle_sys(action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1006));
		}
		break;
	}
	case 39:
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ARMOR, 10)});
		}
		break;
	}
	case 40:
	{
		if (passed_turns % 4 == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::WEAK, 2),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 14),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::REDUCE_AP, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1005),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1005)});
		}
		break;
	}
	case 41:
	{
		if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::REDUCE_AP, 1)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CHAIN, 3));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 8),
				action(battle_action_type::PURIFIED_MOVE_A_CARD_TO_GRAVE, &enemies_data[pos], &player_data, card_type::STAT, 1005)});
		}
		break;
	}
	case 43:
	{
		if (re.chance(60))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 6),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 4)});
		}
		break;
	}
	case 44:
	{
		if (re.chance(60))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ARMOR, 20),
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
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::SHELL, 8));
		}
		else if (re.chance(60))
		{
			return info_to_battle_sys(action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 20));
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 2)});
		}
		break;
	}
	case 46:
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::MARK, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
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
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::ANGER, 1));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 3)});
		}
		else if (re.chance(50))
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 1),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 1)});
		}
		else
		{
			return info_to_battle_sys(action(battle_action_type::ADD_BUFF, &enemies_data[pos], &enemies_data[pos], buff_type::STRENGTH, 1));
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 3),
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
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 10),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::CORRUPT, 4)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5),
				action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 5)});
		}
		break;
		break;
	}
	case 52: //TODO REGENERATE
	{
		if (passed_turns % 2 == 1)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::VULNERABLE, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003)});
		}
		break;
	}
	case 53: //TODO REGENERATE
	{
		if (passed_turns % 2 == 0)
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION, &enemies_data[pos], &player_data, type_type::NORMAL, 12),
				action(battle_action_type::ADD_BUFF, &enemies_data[pos], &player_data, buff_type::FRAGILE, 1)});
		}
		else
		{
			return info_to_battle_sys(vector<action>{action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003),
				action(battle_action_type::ADD_CARD_TO_DECK, &enemies_data[pos], &player_data, card_type::STAT, 1003)});
		}
		break;
		break;
	}
	default:
		return info_to_battle_sys();
		break;
	}
}

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	//TODO set buff priority
	switch (id)
	{
	case buff_type::STRENGTH:
		return pair<string, size_t>(string("strength"), 1);
	case buff_type::DEXTERITY:
		return pair<string, size_t>(string("agility"), 1);
	case buff_type::VITALITY:
		return pair<string, size_t>(string("vitality"), 1);
	case buff_type::ARMOR:
		return pair<string, size_t>(string("armor"), 1);
	case buff_type::WEAK:
		return pair<string, size_t>(string("weak"), 1);
	case buff_type::VULNERABLE:
		return pair<string, size_t>(string("vulnerable"), 1);
	case buff_type::FRAGILE:
		return pair<string, size_t>(string("fragile"), 1);
	case buff_type::BURN:
		return pair<string, size_t>(string("burn"), 1);
	case buff_type::POISON:
		return pair<string, size_t>(string("poison"), 1);
	case buff_type::BLEED:
		return pair<string, size_t>(string("bleed"), 1);
	case buff_type::USED_ATTACK_CARDS:
		return pair<string, size_t>(string("use_atk_c"), 1);
	case buff_type::USED_SKILL_CARDS:
		return pair<string, size_t>(string("use_ski_c"), 1);
	case buff_type::USED_ABILITY_CARDS:
		return pair<string, size_t>(string("use_abi_c"), 1);
	case buff_type::EXHAUST:
		return pair<string, size_t>(string("exhaust"), 1);
	case buff_type::CHAIN:
		return pair<string, size_t>(string("chain"), 1);
	case buff_type::MOVE_MUSSLE:
		return pair<string, size_t>(string("move_mussle"), 1);
	case buff_type::STUN:
		return pair<string, size_t>(string("stun"), 1);
	case buff_type::STUN_RESIST:
		return pair<string, size_t>(string("stun_resist"), 1);
	case buff_type::ETERNAL_FURY:
		return pair<string, size_t>(string("eternal_fury"), 1);
	case buff_type::INVULNARABLE:
		return pair<string, size_t>(string("invulnarable"), 1);
	case buff_type::FIGHTING_SPIRIT:
		return pair<string, size_t>(string("fighting_spirit"), 1);
	case buff_type::FRENZY:
		return pair<string, size_t>(string("frenzy"), 1);
	case buff_type::RITE:
		return pair<string, size_t>(string("rite"), 1);
	case buff_type::RESUSCITATE:
		return pair<string, size_t>(string("resuscitate"), 1);
	case buff_type::ABILITY_BURN:
		return pair<string, size_t>(string("ability_burn"), 1);
	case buff_type::SCORCHED_EARTH:
		return pair<string, size_t>(string("scorched_earth"), 1);
	default:
		return pair<string, size_t>(string("fuck"), 2);
		//throw exception("failed to find buff id");
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

info_to_explore_sys data_sys::artifact_on_create(std::size_t atf_id)
{
	return info_to_explore_sys();
}

info_to_explore_sys data_sys::artifact_on_remove(std::size_t atf_id)
{
	return info_to_explore_sys();
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
	return info_to_battle_sys();
}

info_to_explore_sys data_sys::artifact_on_end_event(std::size_t atf_id)
{
	return info_to_explore_sys();
}

random_engine::random_engine(data_sys * d)
	:data(d)
{
}

size_t random_engine::get_num(int lb, int ub)
{
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(lb, ub);
	int result = ran(e);
	return result;
}

size_t random_engine::get_enemy()
{
	default_random_engine e(static_cast<unsigned>(time(0)));
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
	default_random_engine e(static_cast<unsigned>(time(0)));
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
	default_random_engine e(static_cast<unsigned>(time(0)));
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
	default_random_engine e(static_cast<unsigned>(time(0)));
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
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(0, 100);
	int result = ran(e);
	if (target - (10 * data->luck) > result)
	{
		return true;
	}
	return false;
}
