#pragma once
#include "artifacts.h"
#include "cards.h"
#include <vector> 
#include <map>
class battle_sys_data
{
public:
	battle_sys_data(std::vector<card>& t1,std::vector<card>& t2, std::vector<card>& t3,
		std::vector<card>& t4, std::vector<card>& t5, std::vector<card>& t6, std::vector<buff>& t7,
		std::vector<artifact>&t8, player& player_t, std::size_t& tgold,std::size_t& tfood, std::vector<enemy>& enemies_t);

	player& player_data;
	std::vector<enemy>& enemies_data;

};


class data_sys
{
	public:
	//保存buff的优先度和名字,根据下标(buff_id)访问
	std::vector<std::pair<std::string, std::size_t>> buff_data;
	//保存卡片的效果，根据键值（card_id）访问
	std::map<std::size_t, std::vector<action>> card_effect;

	std::vector<card> cards_pool;//永久牌库
	std::vector<artifact> artifacts;//宝物
	player player_data;
	std::vector<enemy> enemies_data;
	enemy all_enemies, random_enemy, select_one_enemy;
	std::pair<std::string, std::size_t> get_buff(std::size_t);

	std::size_t gold;
	std::size_t food;
	std::vector<card> cards_deck;//战斗时牌库
	std::vector<card> cards_grave;//弃牌堆
	std::vector<card> cards_in_hand;//手牌
	std::vector<card> cards_removed;//除外区
	std::vector<card> cards_equiped;//装备区
	std::array<char, 10> reserve_cards;//手牌中的卡片是否保留
};