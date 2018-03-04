#pragma once
#include "artifacts.h"
#include "cards.h"
#include <vector> 
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
	//保存buff的优先度和名字,根据下标(buff_id)访问
	std::vector<std::pair<std::string, std::size_t>>buff_data;

public:
	std::vector<card> cards_pool;//永久牌库
	std::vector<artifact> artifacts;//宝物
	player player_data;
	std::vector<enemy> enemies_data;
	std::pair<std::string, std::size_t> get_buff(std::size_t);
};