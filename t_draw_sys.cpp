#include "t_draw_sys.h"
using namespace std;
t_draw_sys::t_draw_sys(data_sys &d) :data(d)
{
}

void t_draw_sys::draw()
{
	system("cls");
	for (auto&i : data.enemies_data)
	{
		cout << "hp:" << i.current_hp << '/' << i.max_hp << endl;
	}
	for (auto& i : data.cards_in_hand)
	{
		cout << i.card_name << endl;
	}
	cout << "hp:" << data.player_data.current_hp << '/' << data.player_data.max_hp << endl
		<< "ap:" << data.player_data.current_ap << '/' << data.player_data.max_hp << endl;
}
