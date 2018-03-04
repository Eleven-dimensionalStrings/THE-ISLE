#pragma once
#include "message.h"
#include "data_sys.h"
class interacting_sys :public message_manager
{
	data_sys& data;
	bool send_message();
	bool interpret_message();
	//card_pos��ʹ�õ����������д����ҵ�˳��
	std::vector<std::size_t> select_cards(std::size_t card_pos);
	info_to_battle_sys play_a_card(std::size_t card_pos, game_entity* target);

};