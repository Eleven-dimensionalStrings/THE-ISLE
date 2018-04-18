#include "t_draw_sys.h"
#include <string>
using namespace std;
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
	if (timer >= 5) { timer = 0; is_drawing = 0; if (!draw_queue.empty())draw_queue.pop(); }//TODO
}
void t_draw_sys::__draw_battle_info()
{
	//confirm button
	solidrectangle(gra_size::confirm_button_x, gra_size::confirm_button_y,
		gra_size::confirm_button_x + 100, gra_size::confirm_button_y + 50);
	outtextxy(gra_size::confirm_button_x + 22, gra_size::confirm_button_y + 18, "CONFIRM"); //TODO to be replaced by a compact pic

	//cancel button
	solidrectangle(gra_size::cancel_button_x, gra_size::cancel_button_y,
		gra_size::cancel_button_x + 100, gra_size::cancel_button_y + 50);
	outtextxy(gra_size::cancel_button_x + 25, gra_size::cancel_button_y + 18, "CANCEL"); //TODO to be replaced by a compact pic

	//turn end button
	solidrectangle(gra_size::turn_end_button_x, gra_size::turn_end_button_y,
		gra_size::turn_end_button_x + 100, gra_size::turn_end_button_y + 50);
	outtextxy(gra_size::turn_end_button_x + 18, gra_size::turn_end_button_y + 18, "END TURN"); //TODO to be replaced by a compact pic

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
			solidrectangle(gra_size::map_start_x + (gra_size::map_block_size + gra_size::map_closure) * i,
				gra_size::map_start_y + (gra_size::map_block_size + gra_size::map_closure) * j,
				gra_size::map_start_x + gra_size::map_block_size + (gra_size::map_block_size + gra_size::map_closure) * i,
				gra_size::map_start_y + gra_size::map_block_size + (gra_size::map_block_size + gra_size::map_closure) * j);
		}
	}
}

void t_draw_sys::__draw_buff()
{
	//TODO
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
}

void t_draw_sys::__draw_lines()
{
	solidrectangle(0, 470,
		1500, 475);
	//TODO replace this by background pics
}

void t_draw_sys::__draw_player()
{
	pair<size_t, size_t> drawing;
	if (!draw_queue.empty())drawing = this->draw_queue.front();
	solidrectangle(gra_size::player_x, gra_size::player_y,
		gra_size::player_x + 160, gra_size::player_y + 200);
	if (drawing.first == 666)
	{
		setfillcolor(BLUE);
		solidrectangle(gra_size::player_x, gra_size::player_y,
			gra_size::player_x + 160, gra_size::player_y + 200);
		setfillcolor(LIGHTBLUE);
	}
	else if (drawing.second == 666)
	{

		setfillcolor(BLACK);
		solidrectangle(gra_size::player_x, gra_size::player_y,
			gra_size::player_x + 160, gra_size::player_y + 200);
		setfillcolor(LIGHTBLUE);
	}
	else
	{
		solidrectangle(gra_size::player_x, gra_size::player_y,
			gra_size::player_x + 160, gra_size::player_y + 200);
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
			setfillcolor(BLACK);
			solidrectangle(enemy_pos(pos).first, enemy_pos(pos).second,
				enemy_pos(pos).first + gra_size::enemy_width, enemy_pos(pos).second + 200);
			setfillcolor(LIGHTBLUE);
		}
		else if (p - b == drawing.first)
		{
			setfillcolor(BLUE);
			solidrectangle(enemy_pos(pos).first, enemy_pos(pos).second,
				enemy_pos(pos).first + gra_size::enemy_width, enemy_pos(pos).second + 200);
			setfillcolor(LIGHTBLUE);
		}
		else
		{
			solidrectangle(enemy_pos(pos).first, enemy_pos(pos).second,
				enemy_pos(pos).first + gra_size::enemy_width, enemy_pos(pos).second + 200);

		}
		outtextxy(gra_size::enemy_x + (gra_size::enemy_width + gra_size::enemy_closure) * pos, gra_size::enemy_y - 30,
			&to_string(data.enemies_data[pos].current_hp)[0]);

	}
	else
	{
		solidrectangle(enemy_pos(pos).first, enemy_pos(pos).second + 100,
			enemy_pos(pos).first + gra_size::enemy_width, enemy_pos(pos).second + 200);
	}
}

void t_draw_sys::__draw_a_card(std::size_t pos, int x, int y)
{
	x += gra_size::card_starting_pos;
	if (data.render_select_card[pos])
	{
		setfillcolor(GREEN);
		//TODO
		solidrectangle(x, y - 15, x + gra_size::card_width, y + 185);
		outtextxy(x, y - 15, &data.cards_in_hand[pos].card_name[0]);
		setfillcolor(LIGHTBLUE);
	}
	else
	{
		solidrectangle(x, y, x + gra_size::card_width, y + 200);
		outtextxy(x, y, &data.cards_in_hand[pos].card_name[0]);
	}
	IMAGE t;
	loadimage(&t, "C:\\Users\\Lemon\\Desktop\\作业\\数据结构\\data_structure_hw\\无标题.jpg");
	putimage(x,y,&t);
	//TODO
}

void t_draw_sys::__draw_event_card()
{
	//event card pic
	solidrectangle(gra_size::event_card_x, gra_size::event_card_y, gra_size::event_card_x + 240, gra_size::event_card_y + 300);

	//event card text
	solidrectangle(gra_size::event_text_x, gra_size::event_text_y, gra_size::event_text_x + 240, gra_size::event_text_y + 300);

	//next button
	if (data.event_is_not_mandetory)
		solidrectangle(gra_size::next_x, gra_size::next_y, gra_size::next_x + 200, gra_size::next_y + 100);
}

void t_draw_sys::__draw_player_in_map()
{
	//player pic
	solidrectangle(gra_size::player_x, gra_size::player_y, gra_size::player_x + 160, gra_size::player_y + 200);

	//text
	solidrectangle(gra_size::player_x, gra_size::player_y + 255, gra_size::player_x + 160, gra_size::player_y + 400);
}

void t_draw_sys::__draw_explore_info()
{
	for (int i = 0; i < data.choice_list.size(); ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_a_card(i, x, y);
		if (data.render_select_card[i])
		{
			setfillcolor(GREEN);
			//TODO
			solidrectangle(gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure / 2,
				gra_size::card_y, gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure, gra_size::card_dy);
			setfillcolor(LIGHTBLUE);
		}
	}
	//left arrow pic
	solidrectangle(gra_size::left_arrow_x, gra_size::left_arrow_y,
		gra_size::left_arrow_x + 100, gra_size::left_arrow_y + 100);

	//right arrow pic
	solidrectangle(gra_size::right_arrow_x, gra_size::right_arrow_y,
		gra_size::right_arrow_x + 100, gra_size::right_arrow_y + 100);
}

void t_draw_sys::__draw_player_info()
{
	//hp_pic
	solidrectangle(gra_size::hp_pic_x, gra_size::hp_pic_y,
		gra_size::hp_pic_x + 90, gra_size::hp_pic_y + 120);
	outtextxy(gra_size::hp_x, gra_size::hp_y, &to_string(data.player_data.current_hp)[0]);
	outtextxy(gra_size::hp_x + 25, gra_size::hp_y, '/');
	outtextxy(gra_size::hp_x + 33, gra_size::hp_y, &to_string(data.player_data.max_hp)[0]);

	//gold pic
	solidrectangle(gra_size::gold_pic_x, gra_size::gold_pic_y,
		gra_size::gold_pic_x + 90, gra_size::gold_pic_y + 120);
	outtextxy(gra_size::gold_x, gra_size::gold_y, &to_string(data.gold)[0]);

	//food pic
	solidrectangle(gra_size::food_pic_x, gra_size::food_pic_y,
		gra_size::food_pic_x + 90, gra_size::food_pic_y + 120);
	outtextxy(gra_size::food_x, gra_size::food_y, &to_string(data.food)[0]);
}

void t_draw_sys::__flash_view_cards(std::vector<card>& v, int page)
{
	SetWorkingImage(&this->buffer);
	cleardevice();
	for (int i = page * 16; i < (((page * 16 + 8) < v.size()) ? (page * 16 + 8) : v.size()); ++i)
	{
		//TODO putimage()
		solidrectangle(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y,
			gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8) + gra_size::card_width,
			gra_size::viewcard_firrow_y + 200);
		outtextxy(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y, &data.cards_pool[i].card_name[0]);
		outtextxy(gra_size::viewcard_firrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_firrow_y + 50, &to_string(data.cards_pool[i].card_id)[0]);
	}
	for (int i = page * 16 + 8; i < (((page * 16 + 16) < v.size()) ? (page * 16 + 16) : v.size()); ++i)
	{
		solidrectangle(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y,
			gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8) + gra_size::card_width,
			gra_size::viewcard_secrow_y + 200);
		outtextxy(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y, &data.cards_pool[i].card_name[0]);
		outtextxy(gra_size::viewcard_secrow_x + (gra_size::card_closure + gra_size::card_width)*(i % 8)
			, gra_size::viewcard_secrow_y + 50, &to_string(data.cards_pool[i].card_id)[0]);
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
		default:
			break;
		}
	}
	data.view_cards = 0;
}

t_draw_sys::t_draw_sys(data_sys &d) :data(d),
buffer(gra_size::window_width, gra_size::window_height), timer(0), is_drawing(0)
{
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
					cout << "*";
					break;
				case map_mark_type::KNOWN:
					cout << "K";
					break;
				case map_mark_type::PLAYER:
					cout << "P";
					break;
				case map_mark_type::UNKNOWN:
					cout << "U";
					break;
				case map_mark_type::VISITED:
					cout << "V";
					break;
				}
			}
			cout << "\n";
		}
		cout << "click the map to move" << "\n";
	}
	else
	{
		cout << data.text_to_be_displayed << "\n";
		for (int i = 0; i < 3; i++)
		{
			if (i + 3 * data.current_select_page < data.choice_list.size())
			{
				cout << "press \"" << i << "\"  [" << data.choice_name_list[i + 3 * data.current_select_page] << "]" << "\n";
			}
		}
		if (data.next_event_id > 0)
		{
			cout << "press \"n\"  [跳过选项]" << "\n";
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
	setfillcolor(LIGHTBLUE);
	//TODO putimage(0, 0, image);

	this->check_view();
	this->__draw_player_info();
	this->__draw_card_in_hand();
	this->__draw_entities();
	this->__draw_battle_info();
	this->__draw_guiding_pics();
	this->__draw_lines();
	solidrectangle(gra_size::player_x, gra_size::player_y + 205, gra_size::player_x + 15, gra_size::player_y + 220);
	settextstyle(12, 0, _T("Arial"));
	outtextxy(gra_size::player_x + 11, gra_size::player_y + 214, &to_string(99)[0]);
	settextstyle(20, 0, _T("Arial"));
	solidrectangle(gra_size::player_x, gra_size::player_y + 225, gra_size::player_x + 15, gra_size::player_y + 240);
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
	//TODO putimage(0, 0, image);
	this->__draw_player_info();
	this->__draw_guiding_pics();
	if (data.is_vaccant)
	{
		this->__draw_player_in_map();
		this->__draw_explore_map();
	}
	else
	{
		this->__draw_event_card();
		this->__draw_player();
		this->__draw_explore_info();
		this->__draw_lines();
	}
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void t_draw_sys::draw_begin()
{
}


void t_draw_sys::view_cards(vector<card>& v)
{
	int page = 0;
	__flash_view_cards(v, page);
	while (1)
	{
		auto hit = GetMouseMsg();
		if (hit.mkLButton)
		{
			//TODO next/last page and exit
			if (page < v.size() / 16)++page;
			else page = 0;
			__flash_view_cards(v, page);
		}
		//temp exit
		if (hit.mkRButton)
		{
			break;
		}
	}
}

void t_draw_sys::view_artifacts()
{
}

void t_draw_sys::end_battle()
{
	data.b_to_d.clear();
	while (!draw_queue.empty())draw_queue.pop();
}
