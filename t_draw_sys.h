#pragma once
#include <iostream>
#include <graphics.h>
#include <queue>
#include "data_sys.h"
#include "message.h"
class t_draw_sys
{
	data_sys& data;
	IMAGE buffer;

	//the caller and listener which means the first is attacking the second
	std::queue<std::pair<std::size_t, std::size_t>> draw_queue;
	std::size_t timer;
	bool is_drawing;

	//绘制,分模块
	void __draw_card_in_hand();
	void __draw_entities();
	void __draw_battle_info();//three buttons on the right and ap on the left
	void __draw_explore_map(); 
	void __draw_buff(); // on below every game_entity, has two rows
	void __draw_artifacts();//on top of window, has two rows
	void __get_atk_entities();//get pair of caller and listener from pipe on data_sys
	void __draw_guiding_pics();//static pics used to remind the player of the hotkeys
	void __draw_lines();

	void __draw_player();
	void __draw_an_enemy(std::size_t pos);//draw the enemy in pos
	void __draw_a_card(std::size_t pos, int x, int y);

	void __draw_event_card();
	void __draw_player_in_map();
	void __draw_explore_info();
	void __draw_an_explore_card(std::size_t pos, int x, int y);
	void __draw_player_info();

	void __flash_view_cards(std::vector<card>&v, int page);
	void check_view();
public:
	t_draw_sys(data_sys&);
	void t_draw_b();//控制台测试战斗用
	void t_draw_e();//控制台测试探索用
	void draw_battle();
	void draw_explore();
	void draw_begin();//开始页面
	void view_cards(std::vector<card>&v);//按键后查看卡组等
	void view_artifacts();
	void end_battle();
};