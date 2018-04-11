#include "data_sys.h"
#include <random>
#include <ctime>
using namespace std;

//TODO 弃牌，消耗牌时，会爆炸； aoe会爆炸；各种莫名其妙爆炸
//TODO 6, 8，9, 12

data_sys::data_sys() :player_data(*this), all_enemies(*this), random_enemy(*this), select_one_enemy(*this)
{
	for (auto&i : draw_select_card)i = 0;
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 12), action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, random_engine().get_num(0, cards_in_hand.size()))});
		break;
	}
	case 7://横挥
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 8), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
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
			, &player_data, &select_one_enemy, type_type::NORMAL, 30)});
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
		for (int i = 0; i < cards_in_hand.size(); ++i)
		{
			if (cards_in_hand[i].card_type == card_type::STAT)
			{
				temp.append(action(battle_action_type::P_REMOVE_A_CARD
					, MEANINGLESS_VALUE, i));
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::PURE, 2 * player_data.has_buff(buff_type::BURN))});
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 16), action(battle_action_type::P_DISCARD_A_CARD
				, MEANINGLESS_VALUE, random_engine().get_num(0, cards_in_hand.size()))});
		break;
	}
	case 67://横挥+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 10), action(battle_action_type::DRAW_CARDS
				, &player_data, &player_data, MEANINGLESS_VALUE, 1)});
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
			, &player_data, &select_one_enemy, type_type::NORMAL, 40)});
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
		for (int i = 0; i < cards_in_hand.size(); ++i)
		{
			if (cards_in_hand[i].card_type == card_type::STAT)
			{
				temp.append(action(battle_action_type::P_REMOVE_A_CARD
					, MEANINGLESS_VALUE, i));
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
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::PURE, 2 * player_data.has_buff(buff_type::BURN))});
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
	case buff_type::AGILITY:
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

size_t random_engine::get_num(int lb, int ub)
{
	default_random_engine e(static_cast<unsigned>(time(0)));
	uniform_int_distribution<int> ran(lb, ub);
	int result = ran(e);
	return result;
}
