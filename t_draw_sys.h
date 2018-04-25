#pragma once
#include <iostream>
#include <graphics.h>
#include "data_sys.h"
#include "message.h"
#include "container.h"

using namespace render_functions;
using namespace render_marks;

class t_draw_sys
{
	int current_rendered_cards;
	my_container::my_vector<int> render_card_manifest;
	my_container::my_queue<r_action> render_queue;
	void process()
	{
		if (!render_queue.empty())
		{
			p_timer++;
			switch (render_queue.front().action_id)
			{
			case DRAW_A_CARD:
			{
				if (current_rendered_cards == MAX_CARDS_IN_HAND)
				{
					render_queue.pop();
				}
				else if (p_timer == 1)
				{
					render_card_manifest[current_rendered_cards] = HOLD_UP;
				}
				else if (p_timer == 2)
				{
					render_card_manifest[current_rendered_cards] = HOLD_TWO;
				}
				else if (p_timer == 3)
				{
					render_card_manifest[current_rendered_cards] = HOLD_ONE;
				}
				else if (p_timer == 4)
				{
					render_card_manifest[current_rendered_cards] = IN_HAND;
					current_rendered_cards++;
					p_timer = 0;
					render_queue.pop();
				}

				break;
			}
			case LOSE_A_CARD:
			{
				if (p_timer == 2)
				{
					render_card_manifest[render_queue.front().value] = NOT_IN_HAND;
					for (int i = render_queue.front().value; i < render_card_manifest.size(); ++i)
					{
						if (i == 0)
						{
							render_card_manifest[i] = NOT_IN_HAND;
						}
						else if (i == render_card_manifest.size() - 1)
						{
							render_card_manifest[i] = NOT_IN_HAND;
						}
						else
						{
							render_card_manifest[i] = render_card_manifest[i + 1];
						}
					}
					current_rendered_cards--;
					p_timer = 0;
					render_queue.pop();
				}
				break;
			}
			case SELECT_A_CARD:
			{
				if (p_timer == 1)
				{
					render_card_manifest[render_queue.front().value] = HOLD_ONE;
				}
				else if (p_timer == 2)
				{
					render_card_manifest[render_queue.front().value] = HOLD_TWO;
				}
				else if (p_timer == 3)
				{
					render_card_manifest[render_queue.front().value] = HOLD_UP;
					p_timer = 0;
					render_queue.pop();
				}
				break;
			}
			case DE_SELECT_A_CARD:
			{
				if (p_timer == 1)
				{
					render_card_manifest[render_queue.front().value] = HOLD_TWO;
				}
				else if (p_timer == 2)
				{
					render_card_manifest[render_queue.front().value] = HOLD_ONE;
				}
				else if (p_timer == 3)
				{
					render_card_manifest[render_queue.front().value] = IN_HAND;
					p_timer = 0;
					render_queue.pop();
				}
				break;
			}
			case IMMEDIATE_DE_SELECT:
			{
				if (p_timer == 1)
				{
					render_card_manifest[render_queue.front().value] = IN_HAND;
					current_rendered_cards--;
					p_timer = 0;
					render_queue.pop();
				}
				break;
			}
			case CLEAR_DRAW:
			{
				for (int i = 0; i < MAX_CARDS_IN_HAND; ++i)
				{
					render_card_manifest[i] = NOT_IN_HAND;
				}
				p_timer = 0;
				render_queue.pop();
				break;
			}
			case RESET:
			{
				current_rendered_cards = 0;
				p_timer = 0;
				render_queue.pop();
				break;
			}
			default:
				break;
			}
		}
	}



	data_sys& data;
	IMAGE buffer;

	//the caller and listener which means the first is attacking the second
	my_container::my_queue<std::pair<std::size_t, std::size_t>> draw_queue;
	std::size_t timer;
	std::size_t p_timer;
	bool is_drawing;

	//绘制,分模块
	void __draw_card_in_hand();
	void __draw_entities();
	void __draw_battle_info();//three buttons on the right and ap on the left
	void __draw_explore_map();
	void __draw_buff(); // on below every game_entity, has two rows
	void __get_atk_entities();//get pair of caller and listener from pipe on data_sys
	void __draw_guiding_pics();//static pics used to remind the player of the hotkeys

	void __draw_player();
	void __draw_an_enemy(std::size_t pos);//draw the enemy in pos
	void __draw_a_card(std::size_t pos, int x, int y);

	void __draw_event_card();
	void __draw_player_in_map();
	void __draw_ending_text();
	void __draw_explore_info();
	void __draw_an_explore_card(std::size_t pos, int x, int y);
	void __draw_player_info();
	void __draw_background();

	template<class T>
	void __flash_view(T&v, int page, int is_art = 0);
	void check_view();
public:
	t_draw_sys(data_sys&);
	void update()
	{
		while (!data.render_pipe.empty())
		{
			for (int i = 0; i < data.render_pipe.front().action_set.size(); ++i)
			{
				render_queue.push(data.render_pipe.front().action_set[i]);
			}
			data.render_pipe.pop();
		}
		this->process();
	}
	void load_all();
	void t_draw_b();//控制台测试战斗用
	void t_draw_e();//控制台测试探索用
	void draw_battle();
	void draw_explore();
	void draw_begin();//开始页面
	template<class Container>
	void view_cards(Container&v, int is_art = 0);//按键后查看卡组等
	void end_battle();
	void game_over();

};