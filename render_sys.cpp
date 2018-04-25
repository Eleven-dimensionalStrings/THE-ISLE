#include "render_sys.h"
#include <string>
#include <iomanip>
using namespace std; using namespace my_container;
inline pair<int, int> enemy_pos(size_t pos)
{
	return pair<int, int>(gra_size::enemy_x + pos * (gra_size::enemy_width + gra_size::enemy_closure), gra_size::enemy_y);
}
void render_sys::process()
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
void render_sys::__draw_card_in_hand()
{
	for (int i = 0; i < data.cards_in_hand.size(); ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_a_card(i, x, y);
	}
}
void render_sys::__draw_entities()
{
	if (draw_queue.size())
		is_drawing = 1;
	if (is_drawing)
		++timer;
	for (int i = 0; i < data.enemies_data.size(); ++i)
	{
		this->__draw_an_enemy(i);
	}
	this->__draw_player();
	if (timer >= 7)
	{
		timer = 0;
		is_drawing = 0;
		if (!draw_queue.empty())
			draw_queue.pop();
	}
}
void render_sys::__draw_battle_info()
{
	putimage(gra_size::confirm_button_x, gra_size::confirm_button_y, &data.components[1]);

	putimage(gra_size::cancel_button_x, gra_size::cancel_button_y, &data.components[2]);

	putimage(gra_size::turn_end_button_x, gra_size::turn_end_button_y, &data.components[3]);

	//ap_pic
	putimage(gra_size::ap_pic_x, gra_size::ap_pic_y, &data.components[33]);
	outtextxy(gra_size::ap_x, gra_size::ap_y, &to_string(data.player_data.current_ap)[0]);
	outtextxy(gra_size::ap_x + 20, gra_size::ap_y, '/');
	outtextxy(gra_size::ap_x + 38, gra_size::ap_y, &to_string(data.player_data.max_ap)[0]);
}

void render_sys::__draw_explore_map()
{
	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			switch (data.map_marks[i][j])
			{
			case map_mark_type::EMPTY:
				break;
			case map_mark_type::PLAYER:
				putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
					gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
					&data.components[16]);
				break;
			case map_mark_type::UNKNOWN:
				putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
					gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
					&data.components[17]);
				break;
			case map_mark_type::VISITED:
				putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
					gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
					&data.components[18]);
				break;
			case map_mark_type::KNOWN:
			{
				if (data.explore_map[i][j] == 1)
				{
					putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
						gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
						&data.components[22]);
					break;
				}
				else if (data.explore_map[i][j] >= 15 && data.explore_map[i][j] <= 18)
				{
					putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
						gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
						&data.components[19]);
					break;
				}
				else if (data.explore_map[i][j] >= 19 && data.explore_map[i][j] <= 21)
				{
					putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
						gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
						&data.components[21]);
					break;
				}
				else
				{
					putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
						gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
						&data.components[20]);
					break;
				}
			}
			default:
				break;
			}

		}
	}
}

void render_sys::__draw_buff()
{
	//player
	int unv = 0;
	my_vector<buff> pool;
	for (auto& i : data.player_data.buff_pool)
	{
		if (i.visible)
		{
			pool.push_back(i);
		}
	}
	for (int i = 0; i <= (static_cast<int>(pool.size()) - 1) / 4; ++i)
	{
		for (int j = 0; j < ((pool.size() >= (i + 1) * 4)
			? 4 : pool.size() % 4); ++j)
		{
			/*solidrectangle(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
				gra_size::player_x + gra_size::buff_side_len*(j + 1) + gra_size::buff_closure*j,
				gra_size::player_y + 205 + gra_size::buff_side_len*(i + 1) + gra_size::buff_closure*i);*/
			putimage(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
				&data.get_buff_mask_pic(pool[i * 4 + j].buff_id), SRCPAINT);
			putimage(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
				&data.get_buff_pic(pool[i * 4 + j].buff_id), SRCAND);

			settextstyle(12, 0, _T("Arial"));
			outtextxy(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j + 25,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i + 23,
				&to_string(pool[i * 4 + j].buff_level)[0]);
			settextstyle(20, 0, _T("Arial"));
		}
	}

	//enemy
	for (int pos = 0; pos < data.enemies_data.size(); ++pos)
	{
		pool.clear();
		if (data.enemies_data[pos].is_alive())
		{
			for (auto& i : data.enemies_data[pos].buff_pool)
			{
				if (i.visible)
				{
					pool.push_back(i);
				}
			}
			for (int i = 0; i <= (static_cast<int>(pool.size()) - 1) / 4; ++i)
			{
				for (int j = 0; j < (pool.size() - i * 4) % 4; ++j)
				{
					putimage(pos*(gra_size::enemy_width + gra_size::enemy_closure) + gra_size::enemy_x +
						(gra_size::buff_side_len + gra_size::buff_closure)*j,
						gra_size::enemy_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
						&data.get_buff_mask_pic(pool[i * 4 + j].buff_id), SRCPAINT);
					putimage(pos*(gra_size::enemy_width + gra_size::enemy_closure) + gra_size::enemy_x +
						(gra_size::buff_side_len + gra_size::buff_closure)*j,
						gra_size::enemy_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
						&data.get_buff_pic(pool[i * 4 + j].buff_id), SRCAND);

					settextstyle(12, 0, _T("Arial"));
					outtextxy(pos*(gra_size::enemy_width + gra_size::enemy_closure) +
						gra_size::enemy_x + (gra_size::buff_side_len + gra_size::buff_closure)*j + 25,
						gra_size::enemy_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i + 23,
						&to_string(pool[i * 4 + j].buff_level)[0]);
					settextstyle(20, 0, _T("Arial"));
				}
			}
		}
	}
}

void render_sys::__get_atk_entities()
{
	for (auto i = data.b_to_d.rbegin(); i != data.b_to_d.rend(); ++i)
	{
		draw_queue.push(*i);
	}
	data.b_to_d.clear();
}

void render_sys::__draw_guiding_pics()
{
	//deck_pic
	putimage(gra_size::deck_pic_x, gra_size::deck_pic_y, &data.components[29], SRCPAINT);
	putimage(gra_size::deck_pic_x, gra_size::deck_pic_y, &data.components[28], SRCAND);

	//remaining_deck_pic
	putimage(gra_size::r_deck_pic_x, gra_size::r_deck_pic_y, &data.components[27], SRCPAINT);
	putimage(gra_size::r_deck_pic_x, gra_size::r_deck_pic_y, &data.components[24], SRCAND);

	//grave_pic
	putimage(gra_size::grave_pic_x, gra_size::grave_pic_y, &data.components[27], SRCPAINT);
	putimage(gra_size::grave_pic_x, gra_size::grave_pic_y, &data.components[25], SRCAND);

	//remove_area_pic
	putimage(gra_size::remove_pic_x, gra_size::remove_pic_y, &data.components[27], SRCPAINT);
	putimage(gra_size::remove_pic_x, gra_size::remove_pic_y, &data.components[26], SRCAND);

	//artifact_pic
	putimage(gra_size::view_artifact_x, gra_size::view_artifact_y, &data.components[31], SRCPAINT);
	putimage(gra_size::view_artifact_x, gra_size::view_artifact_y, &data.components[30], SRCAND);
}

void render_sys::__draw_player()
{
	pair<size_t, size_t> drawing;
	if (!draw_queue.empty())drawing = this->draw_queue.front();
	if (drawing.first == 666)
	{
		switch (timer)
		{
		case 1:
			putimage(gra_size::player_x + 8, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 8, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 2:
			putimage(gra_size::player_x + 16, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 16, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 3:
			putimage(gra_size::player_x + 24, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 24, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 4:
			putimage(gra_size::player_x + 32, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 32, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 5:
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 6:
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		case 7:
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[29], SRCPAINT);
			putimage(gra_size::player_x + 40, gra_size::player_y, &data.entities[2], SRCAND);
			break;
		}
	}
	else if (drawing.second == 666)
	{
		switch (timer)
		{
		case 1:
			putimage(gra_size::player_x - 4, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 4, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 2:
			putimage(gra_size::player_x - 8, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 8, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 3:
			putimage(gra_size::player_x - 12, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 12, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 4:
			putimage(gra_size::player_x - 16, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 16, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 5:
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 6:
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		case 7:
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[30], SRCPAINT);
			putimage(gra_size::player_x - 20, gra_size::player_y, &data.entities[3], SRCAND);
			break;
		}
	}
	else
	{
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[28], SRCPAINT);
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[1], SRCAND);
	}
}

void render_sys::__draw_an_enemy(std::size_t pos)
{
	auto p = data.enemies_data.begin() + pos;
	auto b = data.enemies_data.begin();
	pair<size_t, size_t>drawing = pair<size_t, size_t>(999, 999);
	if (!draw_queue.empty())
		drawing = draw_queue.front();
	if (p->is_alive())
	{

		if (p - b == drawing.second)
		{
			switch (timer)
			{
			case 1:
				putimage(enemy_pos(pos).first + 4, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 4, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 2:
				putimage(enemy_pos(pos).first + 8, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 8, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 3:
				putimage(enemy_pos(pos).first + 12, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 12, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 4:
				putimage(enemy_pos(pos).first + 16, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 16, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 5:
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 6:
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			case 7:
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 2), SRCPAINT);
				putimage(enemy_pos(pos).first + 20, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 2), SRCAND);
				break;
			}
		}
		else if (p - b == drawing.first)
		{
			switch (timer)
			{
			case 1:
				putimage(enemy_pos(pos).first - 3, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 3, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 2:
				putimage(enemy_pos(pos).first - 6, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 6, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 3:
				putimage(enemy_pos(pos).first - 9, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 9, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 4:
				putimage(enemy_pos(pos).first - 12, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 12, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 5:
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 6:
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			case 7:
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 1), SRCPAINT);
				putimage(enemy_pos(pos).first - 15, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 1), SRCAND);
				break;
			}
		}
		else
		{
			putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.get_entity_mask_pic(p->enemy_id, 0), SRCPAINT);
			putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.get_entity_pic(p->enemy_id, 0), SRCAND);
		}
		outtextxy(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos, gra_size::enemy_y - 30,
			&to_string(data.enemies_data[pos].current_hp)[0]);
		outtextxy(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 25, gra_size::enemy_y - 30,
			"/");
		outtextxy(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 35, gra_size::enemy_y - 30,
			&to_string(data.enemies_data[pos].max_hp)[0]);
		setfillcolor(RED);
		solidrectangle(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 60, gra_size::enemy_y - 25,
			gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 180, gra_size::enemy_y - 15);
		setfillcolor(LIGHTGREEN);
		solidrectangle(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 60, gra_size::enemy_y - 25,
			gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos + 60 +
			((static_cast<double>(data.enemies_data[pos].current_hp) / static_cast<double>(data.enemies_data[pos].max_hp)) * 120)
			, gra_size::enemy_y - 15);
		setfillcolor(LIGHTBLUE);
	}
}

void render_sys::__draw_a_card(std::size_t pos, int x, int y)
{
	x += gra_size::card_starting_pos;
	switch (render_card_manifest[pos])
	{
	case NOT_IN_HAND:
		break;
	case HOLD_ONE:
		putimage(x, y - 5, &data.get_pic(data.cards_in_hand[pos].id), SRCPAINT);
		putimage(x, y - 5, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCAND);
		break;
	case HOLD_TWO:
		putimage(x, y - 10, &data.get_pic(data.cards_in_hand[pos].id), SRCPAINT);
		putimage(x, y - 10, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCAND);
		break;
	case HOLD_UP:
		putimage(x, y - 15, &data.get_pic(data.cards_in_hand[pos].id), SRCPAINT);
		putimage(x, y - 15, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCAND);
		break;
	case IN_HAND:
		putimage(x, y, &data.get_pic(data.cards_in_hand[pos].id), SRCPAINT);
		putimage(x, y, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCAND);
		break;
	default:
		break;
	}
}

void render_sys::__draw_event_card()
{
	putimage(gra_size::event_card_x, gra_size::event_card_y, &data.components[32], SRCPAINT);
	putimage(gra_size::event_card_x, gra_size::event_card_y, &data.body[data.text_to_be_displayed], SRCAND);

	if (data.event_is_not_mandetory)
	{
		if (data.choice_list.empty())
		{
			putimage(gra_size::next_x, gra_size::next_y, &data.components[40], SRCPAINT);
			putimage(gra_size::next_x, gra_size::next_y, &data.components[39], SRCAND);
		}
		else
		{
			putimage(gra_size::next_x, gra_size::next_y, &data.components[38], SRCPAINT);
			putimage(gra_size::next_x, gra_size::next_y, &data.components[37], SRCAND);
		}
	}
}

void render_sys::__draw_player_in_map()
{
	//player pic
	putimage(gra_size::player_x, gra_size::player_y, &data.entities[56], SRCPAINT);
	putimage(gra_size::player_x, gra_size::player_y, &data.entities[55], SRCAND);
}

void render_sys::__draw_ending_text()
{
	if (data.map_text != MEANINGLESS_VALUE)
	{
		putimage(gra_size::player_x, gra_size::player_y + 255, &data.end[data.map_text]);
	}
}

void render_sys::__draw_explore_info()
{
	int temp = data.choice_list.size() - data.current_select_page * MAX_CARDS_IN_HAND;
	if (temp > MAX_CARDS_IN_HAND)
	{
		temp = MAX_CARDS_IN_HAND;
	}
	for (int i = 0; i < temp; ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_an_explore_card(i, x, y);
	}
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y, &data.components[5], SRCPAINT);
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y, &data.components[4], SRCAND);

	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y, &data.components[7], SRCPAINT);
	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y, &data.components[6], SRCAND);
}

void render_sys::__draw_an_explore_card(std::size_t pos, int x, int y)
{
	x += gra_size::card_starting_pos;
	if (data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id != 0)
	{
		putimage(x, y, &data.get_mask_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id, 0), SRCPAINT);
		putimage(x, y, &data.get_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id, 0), SRCAND);
	}
	else if (data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id != 0)
	{
		putimage(x, y, &data.get_mask_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id, 1), SRCPAINT);
		putimage(x, y, &data.get_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id, 1), SRCAND);
	}
	else
	{
		putimage(x, y, &data.cards_mask[3], SRCPAINT);
		putimage(x, y, &data.select[data.choice_name_list[data.current_select_page * MAX_CARDS_IN_HAND + pos]], SRCAND);
	}
}

void render_sys::__draw_player_info()
{
	//hp_pic
	putimage(gra_size::hp_pic_x, gra_size::hp_pic_y, &data.components[34], SRCPAINT);
	putimage(gra_size::hp_pic_x, gra_size::hp_pic_y, &data.components[8], SRCAND);
	outtextxy(gra_size::hp_x, gra_size::hp_y, &to_string(data.player_data.current_hp)[0]);
	outtextxy(gra_size::hp_x + 25, gra_size::hp_y, '/');
	outtextxy(gra_size::hp_x + 33, gra_size::hp_y, &to_string(data.player_data.max_hp)[0]);

	//gold pic
	putimage(gra_size::gold_pic_x, gra_size::gold_pic_y, &data.components[35], SRCPAINT);
	putimage(gra_size::gold_pic_x, gra_size::gold_pic_y, &data.components[9], SRCAND);
	outtextxy(gra_size::gold_x, gra_size::gold_y, &to_string(data.gold)[0]);

	//food pic
	putimage(gra_size::food_pic_x, gra_size::food_pic_y, &data.components[36], SRCPAINT);
	putimage(gra_size::food_pic_x, gra_size::food_pic_y, &data.components[10], SRCAND);
	outtextxy(gra_size::food_x, gra_size::food_y, &to_string(data.food)[0]);

	settextcolor(LIGHTRED);
	outtextxy(gra_size::ability_num_x, gra_size::ability_num_y, &("strength:  " + to_string(data.strength))[0]);
	putimage(gra_size::ability_num_x - 25, gra_size::ability_num_y - 1, &data.components[11]);
	settextcolor(GREEN);
	outtextxy(gra_size::ability_num_x, gra_size::ability_num_y + 30, &("dexterity:  " + to_string(data.dexterity))[0]);
	putimage(gra_size::ability_num_x - 25, gra_size::ability_num_y + 29, &data.components[12]);
	settextcolor(LIGHTBLUE);
	outtextxy(gra_size::ability_num_x, gra_size::ability_num_y + 60, &("vitality:  " + to_string(data.vitality))[0]);
	putimage(gra_size::ability_num_x - 25, gra_size::ability_num_y + 59, &data.components[13]);
	settextcolor(MAGENTA);
	outtextxy(gra_size::ability_num_x, gra_size::ability_num_y + 90, &("luck:  " + to_string(data.luck))[0]);
	putimage(gra_size::ability_num_x - 25, gra_size::ability_num_y + 89, &data.components[14]);
	settextcolor(BLACK);
}

void render_sys::__draw_background()
{
	setfillcolor(BLACK);
	solidrectangle(0, 400, 1450, 500);
	setfillcolor(LIGHTBLUE);
	putimage(0, -90, &data.backgrounds[data.background_pic]);
	putimage(0, 470, &data.components[0]);
}

template<class T>
void render_sys::__flash_view(T& v, int page, int is_artifact)
{
	SetWorkingImage(&this->buffer);
	cleardevice();
	putimage(0, 0, &data.backgrounds[0]);
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y - 230, &data.components[5], SRCPAINT);
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y - 230, &data.components[4], SRCAND);

	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y - 230, &data.components[7], SRCPAINT);
	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y - 230, &data.components[6], SRCAND);
	for (int i = page * 16; i < (((page * 16 + 8) < v.size()) ? (page * 16 + 8) : v.size()); ++i)
	{
		putimage(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y, &data.get_mask_pic(v[i].id, is_artifact), SRCPAINT);
		putimage(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y, &data.get_pic(v[i].id, is_artifact), SRCAND);

	}
	for (int i = page * 16 + 8; i < (((page * 16 + 16) < v.size()) ? (page * 16 + 16) : v.size()); ++i)
	{
		putimage(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y, &data.get_mask_pic(v[i].id, is_artifact), SRCPAINT);
		putimage(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y, &data.get_pic(v[i].id, is_artifact), SRCAND);
	}
	SetWorkingImage();
	putimage(0, 0, &buffer);
}

void render_sys::check_view()
{
	if (data.view_cards)
	{
		switch (data.view_cards)
		{
		case 1:
			this->view_cards(data.cards_pool);
			break;
		case 2:
			this->view_cards(data.cards_deck);
			break;
		case 3:
			this->view_cards(data.cards_grave);
			break;
		case 4:
			this->view_cards(data.cards_removed);
			break;
		case 5:
			this->view_cards(data.artifacts, 1);
			break;
		default:
			break;
		}
	}
	data.view_cards = 0;
}

render_sys::render_sys(data_sys &d) :data(d),
buffer(gra_size::window_width, gra_size::window_height), timer(0), p_timer(0), is_drawing(0), render_card_manifest(MAX_CARDS_IN_HAND), current_rendered_cards(0)
{

}

void render_sys::update()
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

void render_sys::load_all()
{
	for (int i = 0; i < 5; ++i)
	{
		auto s = (".\\resource\\cards_thumbnail\\mask"
			+ to_string(i) + ".bmp" + '\0');
		loadimage(&data.cards_mask[i], &(".\\resource\\cards_thumbnail\\mask"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 1; i < 10; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\00"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 10; i < 100; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\0"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 100; i < 121; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 308; i < 407; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 15; ++i)
	{
		loadimage(&data.backgrounds[i], &(".\\resource\\backgrounds\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 41; ++i)
	{
		loadimage(&data.components[i], &(".\\resource\\components\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 57; ++i)
	{
		loadimage(&data.entities[i], &(".\\resource\\entities\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 49; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\body\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.body.push_back(std::move(t));
	}
	for (int i = 0; i < 20; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\end\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.end.push_back(std::move(t));
	}
	for (int i = 0; i < 22; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\select\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.select.push_back(std::move(t));
	}
	for (int i = 0; i < 21; ++i)
	{
		loadimage(&data.artifact_pics[i], &(".\\resource\\artifacts\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 22; ++i)
	{
		loadimage(&data.buff_pics[i], &(".\\resource\\buff\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
}

void render_sys::t_draw_b()
{
	system("cls");
	cout << "enemy:\n";
	for (auto&i : data.enemies_data)
	{
		cout << "enemy id:" << i.enemy_id << endl;
		cout << "hp:" << i.current_hp << '/' << i.max_hp << endl;
		for (auto& j : i.buff_pool)
		{
			cout << j.buff_name << "  " << j.buff_level << endl;
		}
	}
	cout << "card:\n";
	for (auto& i : data.cards_in_hand)
	{
		cout << i.card_name << endl;
	}
	for (auto& i : data.player_data.buff_pool)
	{
		cout << i.buff_name << "  " << i.buff_level << endl;
	}
	cout << "player:\n";
	cout << "hp:" << data.player_data.current_hp << '/' << data.player_data.max_hp << endl
		<< "ap:" << data.player_data.current_ap << '/' << data.player_data.max_ap << endl;

	/*while (!draw_queue.empty())
	{
		cout << (draw_queue.front().first) << ' ' << (draw_queue.front().second) << endl;
		draw_queue.pop();
	}*/
	cout << "cards remaining in deck:" << data.cards_deck.size() << endl;
	cout << "draw_queue.size()=" << draw_queue.size() << endl;
}

void render_sys::t_draw_e()
{
	system("cls");
	cout << "player status:\n";
	cout << "hp: " << data.player_data.current_hp << "/" << data.player_data.max_hp << "    ";
	cout << "ap: " << data.player_data.current_ap << "/" << data.player_data.max_ap << "\n";
	cout << "gold: " << data.gold << "      ";
	cout << "food: " << data.food << "\n";
	cout << "strength: " << data.strength << "    ";
	cout << "dexterity: " << data.dexterity << "\n";
	cout << "vitality: " << data.vitality << "    ";
	cout << "luck: " << data.luck << "\n";
	cout << "deck: " << data.cards_pool.size() << "       ";
	cout << "artifacts: " << data.artifacts.size() << "\n\n";
	if (data.is_vaccant)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			for (int j = 0; j < MAP_LENGTH; j++)
			{
				switch (data.map_marks[j][i])
				{
				case map_mark_type::EMPTY:
				{
					cout << setw(3) << " ";
					break;
				}
				case map_mark_type::KNOWN:
				{
					cout << setw(3) << "K";
					break;
				}
				case map_mark_type::PLAYER:
				{
					cout << setw(3) << "P";
					break;
				}
				case map_mark_type::UNKNOWN:
				{
					cout << setw(3) << data.explore_map[j][i];
					break;
				}
				case map_mark_type::VISITED:
				{
					cout << setw(3) << "V";
					break;
				}
				}
			}
			cout << "\n";
		}
		cout << "click the map to move" << "\n";
		cout << data.player_location.first << " " << data.player_location.second << endl;
	}
}

void render_sys::draw_battle()
{
	__get_atk_entities();
	SetWorkingImage(&buffer);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	settextstyle(20, 0, "Airial");
	setfillcolor(LIGHTBLUE);
	settextstyle(20, 0, "Arial");
	this->__draw_background();
	this->check_view();
	this->__draw_player_info();
	this->__draw_card_in_hand();
	this->__draw_entities();
	this->__draw_battle_info();
	this->__draw_guiding_pics();
	this->__draw_buff();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void render_sys::draw_explore()
{
	SetWorkingImage(&buffer);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setfillcolor(LIGHTBLUE);
	this->__draw_background();
	this->check_view();
	this->__draw_player_info();
	this->__draw_guiding_pics();
	if (data.is_vaccant)
	{
		this->__draw_player_in_map();
		this->__draw_explore_map();
		this->__draw_ending_text();
	}
	else
	{
		this->__draw_event_card();
		this->__draw_player_in_map();
		this->__draw_explore_info();
	}
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void render_sys::draw_begin()
{
}


template<class Container>
void render_sys::view_cards(Container&v, int is_art)
{
	int page = 0;
	__flash_view(v, page, is_art);
	while (1)
	{
		auto hit = GetMouseMsg();
		if (hit.mkRButton)
		{
			FlushMouseMsgBuffer();
			Sleep(50);
			break;
		}
		if (hit.mkLButton)
		{
			FlushMouseMsgBuffer();
			Sleep(50);
			if (hit.x > gra_size::left_arrow_x && hit.x < gra_size::left_arrow_x + 100
				&& hit.y > gra_size::left_arrow_y && hit.y < gra_size::left_arrow_y + 100)
			{
				if (page > 0)--page;
				__flash_view(v, page, is_art);
			}
			//检测点击右箭头
			else if (hit.x > gra_size::right_arrow_x && hit.x < gra_size::right_arrow_x + 100
				&& hit.y > gra_size::right_arrow_y && hit.y < gra_size::right_arrow_y + 100)
			{
				if (page < v.size() / 16)++page;
				__flash_view(v, page, is_art);
			}
		}
	}
}

void render_sys::end_battle()
{
	data.b_to_d.clear();
	current_rendered_cards = 0;
	for (int i = 0; i < MAX_CARDS_IN_HAND; ++i)
	{
		render_card_manifest[i] = NOT_IN_HAND;
	}
	while (!draw_queue.empty())draw_queue.pop();
}

void render_sys::game_over()
{
	cleardevice();
	putimage(0, 0, &data.backgrounds[14]);
	auto hit = GetMouseMsg();
	while (!hit.mkLButton)
	{
		hit = GetMouseMsg();
	}
}
