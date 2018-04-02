#pragma once
#include <iostream>
#include <graphics.h>
#include "data_sys.h"
#include "message.h"
class t_draw_sys
{
	data_sys& data;
	IMAGE buffer;

	//����,��ģ��
	void __draw_card_in_hand();
	void __draw_entities();
	void __draw_right_hand_select();

	void __draw_player();
	void __draw_an_enemy(std::size_t pos);//draw the enemy in pos
	void __draw_a_card(std::size_t pos);
public:
	t_draw_sys(data_sys&);
	void draw();//����̨������
	void draw_battle();
};