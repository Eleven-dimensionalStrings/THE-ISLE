#include "t_draw_sys.h"
#include <string>
using namespace std;
inline pair<int, int> enemy_pos(size_t pos)
{
	return pair<int, int>(gra_size::enemy_x + pos * gra_size::enemy_width, gra_size::enemy_y);
}
void t_draw_sys::__draw_card_in_hand()
{
	for (int i = 0; i < data.cards_in_hand.size(); ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_a_card(i, x, y);
		if (data.draw_select_card[i])
		{
			setfillcolor(GREEN);
			//TODO
			solidrectangle(gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure / 2,
				gra_size::card_y, gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure, gra_size::card_dy);
			setfillcolor(LIGHTBLUE);
		}
	}
}
void t_draw_sys::__draw_entities()
{
	if (is_drawing)
		++timer;
	for (int i = 0; i < data.enemies_data.size(); ++i)
	{
		this->__draw_an_enemy(i);
	}
	this->__draw_player();
	if (timer >= 20) { timer = 0; is_drawing = 0; }//TODO
}
void t_draw_sys::__draw_right_hand_info()
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

void t_draw_sys::__draw_player()
{
	pair<size_t, size_t> drawing;
	if (!draw_queue.empty())drawing = this->draw_queue.front();
	solidrectangle(gra_size::player_x, gra_size::player_y, gra_size::player_x + 160, gra_size::player_y + 200);
	if (drawing.first == 666)
	{

	}
	else if (drawing.second == 666)
	{

	}
	else
	{

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
		solidrectangle(enemy_pos(pos).first, enemy_pos(pos).second, enemy_pos(pos).first + gra_size::enemy_width, enemy_pos(pos).second + 200);
		if (p - b == drawing.second)
		{

		}
		else if (p - b == drawing.first)
		{

		}
		else
		{

		}
		outtextxy(gra_size::enemy_x + gra_size::enemy_width * pos, gra_size::enemy_y - 30,
			&to_string(data.enemies_data[pos].current_hp)[0]);

	}
	else
	{

	}
}

void t_draw_sys::__draw_a_card(std::size_t pos, int x, int y)
{
	solidrectangle(x, y, x + gra_size::card_width, y + 200);
	//putimage(x,y,image path);
	//TODO
}

void t_draw_sys::__draw_selections()
{
	for (int i = 0; i < data.choice_list.size(); ++i)
	{
		int y = gra_size::card_y, x = gra_size::card_closure * (i + 1)
			+ gra_size::card_width * i + gra_size::card_x;
		__draw_a_card(i, x, y);
		if (data.draw_select_card[i])
		{
			setfillcolor(GREEN);
			//TODO
			solidrectangle(gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure / 2,
				gra_size::card_y, gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure, gra_size::card_dy);
			setfillcolor(LIGHTBLUE);
		}
	}
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

t_draw_sys::t_draw_sys(data_sys &d) :data(d),
buffer(gra_size::window_width, gra_size::window_height), timer(0), is_drawing(0)
{
}

void t_draw_sys::t_draw_b()
{
	for (auto& i : data.b_to_d)
	{
		draw_queue.push(i);
	}
	data.b_to_d.clear();
	system("cls");
	cout << "enemy:\n";
	for (auto&i : data.enemies_data)
	{
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

	while (!draw_queue.empty())
	{
		cout << (draw_queue.front().first) << ' ' << (draw_queue.front().second) << endl;
		draw_queue.pop();
	}
	cout << "cards remaining in deck:" << data.cards_deck.size() << endl;
}

void t_draw_sys::t_draw_e()
{
	system("cls");
	cout << "player status:\n";
	cout << "hp: " << data.player_data.current_hp << "/" << data.player_data.max_hp << "    ";
	cout << "ap: " << data.player_data.current_ap << "/" << data.player_data.max_ap << "\n";
	cout << "gold: " << data.gold << "    ";
	cout << "food: " << data.food << "\n";
	cout << "str: " << data.strength << "    ";
	cout << "dex: " << data.dexterity << "    ";
	cout << "vit: " << data.vitality << "\n";
	cout << "deck: " << data.cards_pool.size() << "    ";
	cout << "artifacts: " << data.artifacts.size() << "\n\n";
	if (data.is_vaccant)
	{
		for (int i = MAP_LOWER_EDGE; i < MAP_UPPER_EDGE; i++)
		{
			for (int j = MAP_LOWER_EDGE; j < MAP_UPPER_EDGE; j++)
			{
				switch (data.map_marks[i][j])
				{
				case map_mark_type::EMPTY:
					cout << " ";
				case map_mark_type::KNOWN:
					cout << "K";
				case map_mark_type::PLAYER:
					cout << "*";
				case map_mark_type::UNKNOWN:
					cout << "U";
				case map_mark_type::VISITED:
					cout << "V";
				}
			}
			cout << "\n";
		}
		cout << "press \"w\"  [move upwards]" << "\n";
		cout << "press \"a\"  [move towards left]" << "\n";
		cout << "press \"s\"  [move downwards]" << "\n";
		cout << "press \"d\"  [move towards right]" << "\n";
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
			cout << "press \"n\"  [Ìø¹ýÑ¡Ïî]" << "\n";
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
	this->__draw_player_info();
	this->__draw_card_in_hand();
	this->__draw_entities();
	this->__draw_right_hand_info();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void t_draw_sys::draw_explore()
{
	SetWorkingImage(&buffer);
	setbkcolor(BLUE);
	cleardevice();
	settextcolor(YELLOW);
	setfillcolor(YELLOW);
	//TODO putimage(0, 0, image);
	//TODO this->__draw_event_card();
	//TODO this->__draw_entities();
	//TODO this->__draw_right_hand_info();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void t_draw_sys::draw_begin()
{
}

void t_draw_sys::view_cards(vector<card>& v)
{
}

void t_draw_sys::view_artifacts()
{
}
