#include <iostream>
#include "message.h"
#include "interacting.h"
#include "battle_system.h"
#include "t_draw_sys.h"
#include "explore_system.h"
using namespace std;
template<class T = int, class Comp = decltype(comp)>
auto get_p_q(Comp comp)
{
	return priority_queue<T, vector<T>, Comp>(comp);
}
template<class T = int>
auto get_p_q()
{
	return priority_queue<T>();
}
int main()
{
	data_sys d;
	battle_system b(d);
	interacting_sys i(d);
	explore_system e(d);
	IMAGE buffer(gra_size::window_width, gra_size::window_height);
	t_draw_sys dr(d);
	d.b = &b;


	//easyx
	initgraph(gra_size::window_width, gra_size::window_height, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();



	d.enemies_data.push_back(enemy(d, 1));
	d.enemies_data.push_back(enemy(d, 1));
	d.enemies_data.push_back(enemy(d, 1));
	d.enemies_data.push_back(enemy(d, 1));
	d.enemies_data.push_back(enemy(d, 1));
	for (int i = 1; i <= 60; ++i)
	{
		d.cards_pool.push_back(card(i));

	}

	/*d.cards_pool.push_back(card(34));
	d.cards_pool.push_back(card(17));
	d.cards_pool.push_back(card(55));
	d.cards_pool.push_back(card(1));
	d.cards_pool.push_back(card(30));
	d.cards_pool.push_back(card(7));*/


explore:
	//explore loop
	while (1)
	{
		e.update();

		i.update();
		Sleep(100);
		if (!d.enemies_data.empty())
			goto battle;
	}


battle:

	d.cards_deck = my_random_engine::xipai(d.cards_pool);
	d.cards_deck.push_back(card(40));
	//explore gives battle some info
	b.send_message(d.player_data.on_turn_begin());
	while (1)
	{
		b.update();
		dr.draw_battle();
		dr.t_draw_b();
		i.update();
		b.update();
		//enemy act
		Sleep(100);
		if (d.enemies_data.empty())
			goto explore;
	}
	return 0;
}