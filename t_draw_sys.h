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

	//����,��ģ��
	void __draw_card_in_hand();
	void __draw_entities();
	void __draw_right_hand_info();
	void __draw_artifacts();//top of window
	void __get_atk_entities();//get pair of caller and listener from pipe on data_sys

	void __draw_player();
	void __draw_an_enemy(std::size_t pos);//draw the enemy in pos
	void __draw_a_card(std::size_t pos, int x, int y);
public:
	t_draw_sys(data_sys&);
	void draw();//����̨������
	void draw_battle();
	void draw_explore();
	void draw_begin();//��ʼҳ��
	void view_cards(std::vector<card>&v);//������鿴�����
	void view_artifacts();
};