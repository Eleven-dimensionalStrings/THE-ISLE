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


	//easyx
	initgraph(gra_size::window_width, gra_size::window_height, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();



	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.enemies_data.push_back(enemy(d));
	d.cards_pool.push_back(card(0));
	d.cards_pool.push_back(card(1));
	d.cards_pool.push_back(card(2));
	d.cards_pool.push_back(card(3));
	d.cards_pool.push_back(card(4));

explore:
	//explore loop
	while (1)
	{
		e.update();


		if (!d.enemies_data.empty())
			goto battle;
	}


battle:
	//����ս��
	d.cards_deck = d.cards_pool;
	//explore gives battle some info
	b.send_message(d.player_data.on_turn_begin());
	while (1)
	{

		//b.send_message(d.player_data.on_turn_begin());
		b.update();
		dr.draw_battle();
		dr.draw();
		i.update();
		b.update();
		//b.send_message(d.player_data.on_turn_end());
		b.update();
		//enemy act
		Sleep(30);
		if (d.enemies_data.empty())
			goto explore;
	}
	return 0;
}