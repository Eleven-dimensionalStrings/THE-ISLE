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
	t_draw_sys dr(d);

	//进入战斗
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));

	for (int i = 0; i < 10; ++i)
		d.cards_pool.push_back(card(0, 0, "打10"));
	d.cards_deck = d.cards_pool;
	while (1)
	{
		d.player_data.on_turn_begin();
		dr.draw();
		i.update();
		b.update();
		d.player_data.on_turn_end();
	}
	return 0;
}