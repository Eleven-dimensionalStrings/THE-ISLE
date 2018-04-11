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
			setfillcolor(BLUE);
			//TODO
			//˵��ѡ�������λ�õĿ�
			solidrectangle(gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure / 2,
				gra_size::card_y, gra_size::card_x + i * (gra_size::card_closure + gra_size::card_width) + gra_size::card_closure, gra_size::card_dy);
			setfillcolor(BLACK);
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
	outtextxy(gra_size::hp_x, gra_size::hp_y, &to_string(data.player_data.current_hp)[0]);
	outtextxy(gra_size::hp_x + 70, gra_size::hp_y, '/');
	outtextxy(gra_size::hp_x + 80, gra_size::hp_y, &to_string(data.player_data.max_hp)[0]);

	outtextxy(gra_size::ap_x, gra_size::ap_y, &to_string(data.player_data.current_ap)[0]);
	outtextxy(gra_size::ap_x + 70, gra_size::ap_y, '/');
	outtextxy(gra_size::ap_x + 80, gra_size::ap_y, &to_string(data.player_data.max_ap)[0]);

	solidrectangle(gra_size::confirm_button_x, gra_size::confirm_button_y,
		gra_size::confirm_button_x + 100, gra_size::confirm_button_y + 50);

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
t_draw_sys::t_draw_sys(data_sys &d) :data(d),
buffer(gra_size::window_width, gra_size::window_height), timer(0), is_drawing(0)
{
}

void t_draw_sys::draw()
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
}

void t_draw_sys::draw_battle()
{
	__get_atk_entities();
	SetWorkingImage(&buffer);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(BLACK);
	setfillcolor(BLACK);
	//TODO �ñ���ͼƬ���� putimage(0, 0, image);
	this->__draw_card_in_hand();
	this->__draw_entities();
	this->__draw_right_hand_info();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}

void t_draw_sys::draw_explore()
{
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
