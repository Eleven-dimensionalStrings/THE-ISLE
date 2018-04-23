#include "t_draw_sys.h"
#include <string>
using namespace std; using namespace my_container;
inline pair<int, int> enemy_pos(size_t pos)
{
	return pair<int, int>(gra_size::enemy_x + pos * (gra_size::enemy_width + gra_size::enemy_closure), gra_size::enemy_y);
}
void t_draw_sys::__draw_card_in_hand()
{
	for (int i = 0; i < data.cards_in_hand.size(); ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_a_card(i, x, y);
	}
}
void t_draw_sys::__draw_entities()
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
	if (timer >= 7) { timer = 0; is_drawing = 0; if (!draw_queue.empty())draw_queue.pop(); }//TODO
}
void t_draw_sys::__draw_battle_info()
{
	putimage(gra_size::confirm_button_x, gra_size::confirm_button_y, &data.components[1]);

	putimage(gra_size::cancel_button_x, gra_size::cancel_button_y, &data.components[2]);

	putimage(gra_size::turn_end_button_x, gra_size::turn_end_button_y, &data.components[3]);

	//ap_pic
	solidcircle(gra_size::ap_pic_x, gra_size::ap_pic_y, gra_size::ap_pic_radius);
	outtextxy(gra_size::ap_x, gra_size::ap_y, &to_string(data.player_data.current_ap)[0]);
	outtextxy(gra_size::ap_x + 20, gra_size::ap_y, '/');
	outtextxy(gra_size::ap_x + 28, gra_size::ap_y, &to_string(data.player_data.max_ap)[0]); //TODO to be replaced by a compact pic
}

void t_draw_sys::__draw_explore_map()
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
				else if (data.explore_map[i][j] == 2)
				{
					putimage(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
						gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
						&data.components[19]);
					break;
				}
				else if (data.explore_map[i][j] == 3)
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

void t_draw_sys::__draw_buff()
{
	//player
	int unv = 0;
	//TODO visible
	auto pool = data.player_data.buff_pool;
	for (int i = 0; i <= (static_cast<int>(pool.size()) - 1) / 8; ++i)
	{
		for (int j = 0; j < ((pool.size() >= (i + 1) * 8)
			? 8 : pool.size() % 8); ++j)
		{
			solidrectangle(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
				gra_size::player_x + gra_size::buff_side_len*(j + 1) + gra_size::buff_closure*j,
				gra_size::player_y + 205 + gra_size::buff_side_len*(i + 1) + gra_size::buff_closure*i);
			settextstyle(12, 0, _T("Arial"));
			outtextxy(gra_size::player_x + (gra_size::buff_side_len + gra_size::buff_closure)*j + 10,
				gra_size::player_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i + 8,
				&to_string(pool[i * 8 + j].buff_level)[0]);
			settextstyle(20, 0, _T("Arial"));
		}
	}

	//enemy
	for (int pos = 0; pos < data.enemies_data.size(); ++pos)
	{
		//TODO visible
		pool.clear();
		pool = data.enemies_data[pos].buff_pool;
		for (int i = 0; i <= (static_cast<int>(pool.size()) - 1) / 8; ++i)
		{
			for (int j = 0; j < (pool.size() - i * 8) % 8; ++j)
			{
				solidrectangle(pos*(gra_size::enemy_width + gra_size::enemy_closure) + gra_size::enemy_x +
					(gra_size::buff_side_len + gra_size::buff_closure)*j,
					gra_size::enemy_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i,
					pos*(gra_size::enemy_width + gra_size::enemy_closure) +
					gra_size::enemy_x + gra_size::buff_side_len*(j + 1) + gra_size::buff_closure*j,
					gra_size::enemy_y + 205 + gra_size::buff_side_len*(i + 1) + gra_size::buff_closure*i);
				settextstyle(12, 0, _T("Arial"));
				outtextxy(pos*(gra_size::enemy_width + gra_size::enemy_closure) +
					gra_size::enemy_x + (gra_size::buff_side_len + gra_size::buff_closure)*j + 10,
					gra_size::enemy_y + 205 + (gra_size::buff_side_len + gra_size::buff_closure)*i + 8,
					&to_string(pool[i * 8 + j].buff_level)[0]);
				settextstyle(20, 0, _T("Arial"));
			}
		}
	}
}

void t_draw_sys::__draw_artifacts()
{
	for (auto&i : data.artifacts)
	{
		//TODO
	}
}

void t_draw_sys::__get_atk_entities()
{
	for (auto i = data.b_to_d.rbegin(); i != data.b_to_d.rend(); ++i)
	{
		draw_queue.push(*i);
	}
	data.b_to_d.clear();
}

void t_draw_sys::__draw_guiding_pics()
{
	//deck_pic
	solidrectangle(gra_size::deck_pic_x, gra_size::deck_pic_y,
		gra_size::deck_pic_x + 45, gra_size::deck_pic_y + 50);

	//remaining_deck_pic
	solidrectangle(gra_size::r_deck_pic_x, gra_size::r_deck_pic_y,
		gra_size::r_deck_pic_x + 45, gra_size::r_deck_pic_y + 50);

	//grave_pic
	solidrectangle(gra_size::grave_pic_x, gra_size::grave_pic_y,
		gra_size::grave_pic_x + 45, gra_size::grave_pic_y + 50);

	//remove_area_pic
	solidrectangle(gra_size::remove_pic_x, gra_size::remove_pic_y,
		gra_size::remove_pic_x + 45, gra_size::remove_pic_y + 50);

	solidrectangle(gra_size::view_artifact_x, gra_size::view_artifact_y
		, gra_size::view_artifact_x + gra_size::deck_width, gra_size::view_artifact_y + gra_size::deck_height);
}

void t_draw_sys::__draw_player()
{
	pair<size_t, size_t> drawing;
	if (!draw_queue.empty())drawing = this->draw_queue.front();
	if (drawing.first == 666)
	{
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[11], NOTSRCERASE);
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[2], SRCINVERT);
	}
	else if (drawing.second == 666)
	{
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[12], NOTSRCERASE);
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[3], SRCINVERT);
	}
	else
	{
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[10], NOTSRCERASE);
		putimage(gra_size::player_x, gra_size::player_y, &data.entities[1], SRCINVERT);
	}
}

void t_draw_sys::__draw_an_enemy(std::size_t pos)
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
			if (p->enemy_id <= 20)
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[15], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[6], SRCINVERT);
			}
			else
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[18], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[9], SRCINVERT);
			}
		}
		else if (p - b == drawing.first)
		{
			if (p->enemy_id <= 20)
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[14], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[5], SRCINVERT);
			}
			else
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[17], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[8], SRCINVERT);
			}
		}
		else
		{
			if (p->enemy_id <= 20)
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[13], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[4], SRCINVERT);
			}
			else
			{
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[16], NOTSRCERASE);
				putimage(enemy_pos(pos).first, enemy_pos(pos).second, &data.entities[7], SRCINVERT);
			}

		}
		outtextxy(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos, gra_size::enemy_y - 30,
			&to_string(data.enemies_data[pos].current_hp)[0]);

	}
}

void t_draw_sys::__draw_a_card(std::size_t pos, int x, int y)
{
	x += gra_size::card_starting_pos;
	if (data.render_select_card[pos])
	{
		putimage(x, y - 15, &data.get_pic(data.cards_in_hand[pos].id), NOTSRCERASE);
		putimage(x, y - 15, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCINVERT);
	}
	else
	{
		putimage(x, y, &data.get_pic(data.cards_in_hand[pos].id), NOTSRCERASE);
		putimage(x, y, &data.get_mask_pic(data.cards_in_hand[pos].id), SRCINVERT);

	}
}

void t_draw_sys::__draw_event_card()
{
	//event card pic
	//TODO
	putimage(gra_size::event_card_x, gra_size::event_card_y, &data.body[data.text_to_be_displayed]);

	//next button
	if (data.event_is_not_mandetory)
		solidrectangle(gra_size::next_x, gra_size::next_y, gra_size::next_x + 200, gra_size::next_y + 100);
}

void t_draw_sys::__draw_player_in_map()
{
	//player pic
	putimage(gra_size::player_x, gra_size::player_y, &data.entities[20], NOTSRCERASE);
	putimage(gra_size::player_x, gra_size::player_y, &data.entities[19], SRCINVERT);
}

void t_draw_sys::__draw_ending_text()
{
	//TODO
	if (data.map_text != -1)
		putimage(gra_size::player_x, gra_size::player_y + 255, &data.end[data.map_text]);
}

void t_draw_sys::__draw_explore_info()
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
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y, &data.components[5], NOTSRCERASE);
	putimage(gra_size::left_arrow_x, gra_size::left_arrow_y, &data.components[4], SRCINVERT);

	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y, &data.components[7], NOTSRCERASE);
	putimage(gra_size::right_arrow_x, gra_size::right_arrow_y, &data.components[6], SRCINVERT);
}

void t_draw_sys::__draw_an_explore_card(std::size_t pos, int x, int y)
{
	x += gra_size::card_starting_pos;
	if (data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id != 0)
	{
		putimage(x, y, &data.get_mask_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id, 0), NOTSRCERASE);
		putimage(x, y, &data.get_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].selected_card.id, 0), SRCINVERT);
	}
	else if (data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id != 0)
	{
		putimage(x, y, &data.get_mask_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id, 1), NOTSRCERASE);
		putimage(x, y, &data.get_pic(data.choice_list[data.current_select_page * MAX_CARDS_IN_HAND + pos].atf.id, 1), SRCINVERT);
	}
	else
	{
		putimage(x, y, &data.cards_mask[3], NOTSRCERASE);
		putimage(x, y, &data.cards_thumbnail[400], SRCINVERT);
		//TODO
		putimage(x, y, &data.select[data.choice_name_list[data.current_select_page * MAX_CARDS_IN_HAND + pos]]);
		//this->__format_wl(x + 22, y + 117, data.choice_name_list[data.current_select_page * MAX_CARDS_IN_HAND + pos]);
	}
}

void t_draw_sys::__draw_player_info()
{
	//hp_pic
	putimage(gra_size::hp_pic_x, gra_size::hp_pic_y, &data.components[15], NOTSRCERASE);
	putimage(gra_size::hp_pic_x, gra_size::hp_pic_y, &data.components[8], SRCINVERT);
	outtextxy(gra_size::hp_x, gra_size::hp_y, &to_string(data.player_data.current_hp)[0]);
	outtextxy(gra_size::hp_x + 25, gra_size::hp_y, '/');
	outtextxy(gra_size::hp_x + 33, gra_size::hp_y, &to_string(data.player_data.max_hp)[0]);

	//gold pic
	putimage(gra_size::gold_pic_x, gra_size::gold_pic_y, &data.components[15], NOTSRCERASE);
	putimage(gra_size::gold_pic_x, gra_size::gold_pic_y, &data.components[9], SRCINVERT);
	outtextxy(gra_size::gold_x, gra_size::gold_y, &to_string(data.gold)[0]);

	//food pic
	putimage(gra_size::food_pic_x, gra_size::food_pic_y, &data.components[15], NOTSRCERASE);
	putimage(gra_size::food_pic_x, gra_size::food_pic_y, &data.components[10], SRCINVERT);
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

void t_draw_sys::__draw_background()
{
	putimage(0, 0, &data.back_grounds[background_pic]);
	putimage(0, 470, &data.components[0]);
}

void t_draw_sys::__format_wl(int x, int y, string ss)
{
	int i = 0;
	settextstyle(20, 0, "Arial");
	string s("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	while (s.size() > i * 10)
	{
		string str;
		for (int j = i * 10; j < ((1 + i) * 10 < s.size() ? (1 + i) * 10 : s.size() - 1); ++j)
			str += s[j];
		str += '\0';
		outtextxy(x, y + i * 22, &str[0]);
		++i;
	}
}

template<class T>
void t_draw_sys::__flash_view(T& v, int page, int is_artifact)
{
	SetWorkingImage(&this->buffer);
	cleardevice();
	solidrectangle(gra_size::left_arrow_x, gra_size::left_arrow_y,
		gra_size::left_arrow_x + 100, gra_size::left_arrow_y + 100);
	solidrectangle(gra_size::right_arrow_x, gra_size::right_arrow_y,
		gra_size::right_arrow_x + 100, gra_size::right_arrow_y + 100);
	for (int i = page * 16; i < (((page * 16 + 8) < v.size()) ? (page * 16 + 8) : v.size()); ++i)
	{
		//TODO putimage()
		putimage(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y, &data.get_mask_pic(v[i].id, is_artifact), NOTSRCERASE);
		putimage(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y, &data.get_pic(v[i].id, is_artifact), SRCINVERT);

	}
	for (int i = page * 16 + 8; i < (((page * 16 + 16) < v.size()) ? (page * 16 + 16) : v.size()); ++i)
	{
		putimage(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y, &data.get_mask_pic(v[i].id, is_artifact), NOTSRCERASE);
		putimage(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y, &data.get_pic(v[i].id, is_artifact), SRCINVERT);
	}
	SetWorkingImage();
	putimage(0, 0, &buffer);
}

void t_draw_sys::check_view()
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
			this->view_cards(data.artifacts, 2);
			break;
		default:
			break;
		}
	}
	data.view_cards = 0;
}

t_draw_sys::t_draw_sys(data_sys &d) :data(d),
buffer(gra_size::window_width, gra_size::window_height), timer(0), is_drawing(0), background_pic(0)
{
	// settextstyle(20, 0, _T("Arial"));
}

void t_draw_sys::load_all()
{
	for (int i = 0; i < 4; ++i)
	{
		auto s = (".\\resource\\cards_thumbnail\\mask"
			+ to_string(i) + ".bmp" + '\0');
		loadimage(&data.cards_mask[i], &(".\\resource\\cards_thumbnail\\mask"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 4; ++i)
	{
		loadimage(&data.cards_mask[i + 4], &(".\\resource\\cards_original\\mask"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 1; i < 10; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\00"
			+ to_string(i) + ".bmp" + '\0')[0]);
		loadimage(&data.cards_original[i], &(".\\resource\\cards_original\\00"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 10; i < 100; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\0"
			+ to_string(i) + ".bmp" + '\0')[0]);
		loadimage(&data.cards_original[i], &(".\\resource\\cards_original\\0"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 100; i < 121; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
		loadimage(&data.cards_original[i], &(".\\resource\\cards_original\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 400; i < 407; ++i)
	{
		loadimage(&data.cards_thumbnail[i], &(".\\resource\\cards_thumbnail\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
		loadimage(&data.cards_original[i], &(".\\resource\\cards_original\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 7; ++i)//TODO, change 7 when new backgrounds are added;
	{
		loadimage(&data.back_grounds[i], &(".\\resource\\backgrounds\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 24; ++i)//TODO to replace 8
	{
		loadimage(&data.components[i], &(".\\resource\\components\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i < 21; ++i)
	{
		loadimage(&data.entities[i], &(".\\resource\\entities\\"
			+ to_string(i) + ".bmp" + '\0')[0]);
	}
	for (int i = 0; i <= 30; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\body\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.body.push_back(std::move(t));
	}
	for (int i = 1; i <= 14; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\end\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.end.push_back(std::move(t));
	}
	for (int i = 0; i <= 14; ++i)
	{
		IMAGE t;
		loadimage(&t, &(".\\resource\\explore\\select\\" + to_string(i) + ".bmp" + '\0')[0]);
		data.select.push_back(std::move(t));
	}
}

void t_draw_sys::t_draw_b()
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

void t_draw_sys::t_draw_e()
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
					cout << " ";
					break;
				}
				case map_mark_type::KNOWN:
				{
					cout << "K";
					break;
				}
				case map_mark_type::PLAYER:
				{
					cout << "P";
					break;
				}
				case map_mark_type::UNKNOWN:
				{
					cout << data.explore_map[j][i];
					break;
				}
				case map_mark_type::VISITED:
				{
					cout << "V";
					break;
				}
				}
			}
			cout << "\n";
		}
		cout << "click the map to move" << "\n";
		cout << data.player_location.first << " " << data.player_location.second << endl;
	}
	else
	{
		cout << data.text_to_be_displayed << "\n";
		for (int i = 0; i < 3; i++)
		{
			if (i + 3 * data.current_select_page < data.choice_list.size())
			{
				//TODO
//				cout << "press \"" << i << "\"  [" << data.choice_name_list[i + 3 * data.current_select_page] << "]" << "\n";
			}
		}
		if (data.next_event_id > 0)
		{
			cout << "press \"n\"  [����ѡ��]" << "\n";
		}
	}
}

void t_draw_sys::draw_battle()
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
	this->__draw_artifacts();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void t_draw_sys::draw_explore()
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

void t_draw_sys::draw_begin()
{
}


template<class Container>
void t_draw_sys::view_cards(Container&v, int is_art)
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


void t_draw_sys::end_battle()
{
	data.b_to_d.clear();
	while (!draw_queue.empty())draw_queue.pop();
}
