#pragma once
#include "artifacts.h"
#include "cards.h"
#include "message.h"
#include <vector> 
#include <map>
#include <functional>
/*class battle_sys_data
{
public:
	battle_sys_data(std::vector<card>& t1,std::vector<card>& t2, std::vector<card>& t3,
		std::vector<card>& t4, std::vector<card>& t5, std::vector<card>& t6, std::vector<buff>& t7,
		std::vector<artifact>&t8, player& player_t, std::size_t& tgold,std::size_t& tfood, std::vector<enemy>& enemies_t);

	player& player_data;
	std::vector<enemy>& enemies_data;

};*/


class data_sys
{
public:
	data_sys();
	//����buff�����ȶȺ�����,�����±�(buff_id)����
	std::vector<std::pair<std::string, std::size_t>> buff_data;
	//���濨Ƭ��Ч�������ݼ�ֵ��card_id������
	std::map<std::size_t, std::vector<action>> card_effect;
	std::map<std::size_t, std::string> card_name;
	std::map<std::size_t, std::size_t> card_upgrade_id;
	std::vector<card> cards_pool;//�����ƿ�
	std::vector<artifact> artifacts;//����
	player player_data;
	std::vector<enemy> enemies_data;
	enemy all_enemies, random_enemy, select_one_enemy;
	std::pair<std::string, std::size_t> get_buff(std::size_t);

	std::size_t gold;
	std::size_t food;
	std::size_t strength;
	std::size_t dexterity;
	std::size_t vitality;
	std::size_t luck;
	std::vector<card> cards_deck;//ս��ʱ�ƿ�
	std::vector<card> cards_grave;//���ƶ�
	std::vector<card> cards_in_hand;//����
	std::vector<card> cards_removed;//������
	std::vector<card> cards_equiped;//װ����
	std::array<char, 10> reserve_cards;//�����еĿ�Ƭ�Ƿ���
	info_to_battle_sys i_to_b_pipe;
	info_battle_to_interacting b_to_i_pipe;
	info_to_explore_sys i_to_e_pipe;
	info_explore_to_interacting e_to_i_pipe;
	std::size_t explore_map[6][6];
	int map_marks[6][6];
	std::pair<int, int> player_location;
	std::vector<explore_selection> choice_list;
	std::map<std::size_t, event_card> event_effect;

	std::vector<std::function<info_to_battle_sys(info_to_battle_sys)>>v;
	/*
	��Ҫ��¼����:
	�������ƶ�ӦЧ��,����ÿ����action(����ʹ����
	buff��ӦЧ��(��buff��on_calling�Ⱥ�����ʹ��
	*/
};