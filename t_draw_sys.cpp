#include "t_draw_sys.h"
using namespace std;
void t_draw_sys::__draw_card_in_hand()
{
}
void t_draw_sys::__draw_entities()
{
	for (int i = 0; i < data.enemies_data.size(); ++i)
	{
		this->__draw_an_enemy(i);
	}
	this->__draw_player();
}
void t_draw_sys::__draw_right_hand_select()
{
}
void t_draw_sys::__draw_player()
{
}
void t_draw_sys::__draw_an_enemy(std::size_t pos)
{
	if (data.enemies_data[pos].is_alive())
	{
		if (is_drawing && pos == this->pos)
		{
			//TODO
			++timer;
			if (timer >= 20) {}//TODO
		}
	}
	else
	{
		//TODO
	}
}
void t_draw_sys::__draw_a_card(std::size_t pos)
{
	int up = window_unit_size::card_up,
		left = window_unit_size::card_closure * (pos + 1) + window_unit_size::card_width * pos;
	//putimage(up,left,image path);
	//TODO
}
t_draw_sys::t_draw_sys(data_sys &d) :data(d),
buffer(window_unit_size::window_width, window_unit_size::window_height), pos(0), timer(0), is_drawing(0)
{
}

void t_draw_sys::draw()
{
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
		cout << i.buff_name << "  " << i.buff_level << ' ' << i.buff_life << endl;
	}
	cout << "player:\n";
	cout << "hp:" << data.player_data.current_hp << '/' << data.player_data.max_hp << endl
		<< "ap:" << data.player_data.current_ap << '/' << data.player_data.max_ap << endl;
}

void t_draw_sys::draw_battle()
{
	SetWorkingImage(&buffer);
	//TODO ÓÃ±³¾°Í¼Æ¬¸²¸Ç putimage(0, 0, image);
	this->__draw_card_in_hand();
	this->__draw_entities();
	this->__draw_right_hand_select();
	SetWorkingImage(0);
	putimage(0, 0, &buffer);
}
