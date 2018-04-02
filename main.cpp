#include <iostream>
#include "message.h"
#include "interacting.h"
#include "battle_system.h"
#include "t_draw_sys.h"
using namespace std;
int main()
{
	data_sys d;
	battle_system b(d);
	interacting_sys i(d);
	IMAGE buffer(window_unit_size::window_width, window_unit_size::window_height);
	t_draw_sys dr(d, buffer);


	/*easyx
	initgraph(window_unit_size::window_width, window_unit_size::window_height);
	setbkcolor(WHITE);
	cleardevice();*/
	


	d.enemies_data.push_back(enemy(d));
	//d.enemies_data.push_back(enemy(d));
	//d.enemies_data.push_back(enemy(d));
	//d.enemies_data.push_back(enemy(d));
	d.cards_pool.push_back(card(0, 0, "打10", 1));
	d.cards_pool.push_back(card(1, 1, "加100力量", 0));
	d.cards_pool.push_back(card(2, 2, "加100易伤", 1));
	d.cards_pool.push_back(card(3, 3, "加100毒", 1));
	d.cards_deck = d.cards_pool;
	//进入战斗
	while (1)
	{

		b.send_message(d.player_data.on_turn_begin());
		dr.draw();
		i.update();
		b.update();
		b.send_message(d.player_data.on_turn_end());
		b.update();
	}
	return 0;
}