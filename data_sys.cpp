#include "data_sys.h"
#include <random>
#include <ctime>
using namespace std;

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
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, fix_buff_value(2, 2))});
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
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, fix_buff_value(1, 1)), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::WEAK, fix_buff_value(1, 1))});
		break;
	}
	case 10://过肩摔
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::WEAK, fix_buff_value(2, 2))});
		break;
	}
	case 11://湮灭
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 30)});
		break;
	}
	case 12://蓄力劈砍
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 12)});
		break;
	}
	case 13://无谋打击
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 3), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::VULNERABLE, fix_buff_value(1, 1))});
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
					, &player_data, &player_data, buff_type::EXHAUST, fix_buff_value(1, 4))});
		break;
	}
	case 16://猛冲
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 12), action(battle_action_type::ADD_BUFF
					, &player_data, &player_data, buff_type::EXHAUST, fix_buff_value(1, 4))});
		break;
	}
	case 17://混战
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 10), action(battle_action_type::ADD_CARD_TO_DECK
				,MEANINGLESS_VALUE, 1001)});
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
					,MEANINGLESS_VALUE, i));
				temp.append(action(battle_action_type::CALLING_ACTION
					, &player_data, &all_enemies, type_type::NORMAL, 6));
			}
		}
		return temp;
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
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, fix_buff_value(3, 3))});
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
				, &player_data, &select_one_enemy, buff_type::VULNERABLE, fix_buff_value(2, 2)), action(battle_action_type::ADD_BUFF
					, &player_data, &select_one_enemy, buff_type::WEAK, fix_buff_value(2, 2))});
		break;
	}
	case 70://过肩摔+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 14), action(battle_action_type::ADD_BUFF
				, &player_data, &select_one_enemy, buff_type::WEAK, fix_buff_value(3, 3))});
		break;
	}
	case 71://湮灭+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 40)});
		break;
	}
	case 72://蓄力劈砍+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &all_enemies, type_type::NORMAL, 12)});
		break;
	}
	case 73://无谋打击+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
				, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
					, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::CALLING_ACTION
						, &player_data, &select_one_enemy, type_type::NORMAL, 4), action(battle_action_type::ADD_BUFF
							, &player_data, &player_data, buff_type::VULNERABLE, fix_buff_value(1, 1))});
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
					, &player_data, &player_data, buff_type::EXHAUST, fix_buff_value(1, 4))});
		break;
	}
	case 76://猛冲+
	{
		return info_to_battle_sys(vector<action>{action(battle_action_type::CALLING_ACTION
			, &player_data, &random_enemy, type_type::NORMAL, 16), action(battle_action_type::ADD_BUFF
				, &player_data, &player_data, buff_type::EXHAUST, fix_buff_value(1, 4))});
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

	case 2874://�����
	{
		info_to_battle_sys t;
		for (int i = 0; i < 10; ++i)
		{
			t.append(action(battle_action_type::CALLING_ACTION
				, &player_data, &random_enemy, type_type::NORMAL, 10));
		}
		return t;
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
	case buff_type::VULNERABLE:
		return pair<string, size_t>(string("strength"), 1);
	case buff_type::POISON:
		return pair<string, size_t>(string("poison"), 1);
	default:
		throw exception("failed to find buff id");
	}
}

size_t random_engine::get_num(size_t lb, size_t ub)
{
		default_random_engine e(static_cast<unsigned>(time(0)));
		uniform_int_distribution<int> ran(lb, ub);
		int result = ran(e);
		return result;
}
