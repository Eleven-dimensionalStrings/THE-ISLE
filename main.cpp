#include <iostream>
#include "message.h"
#include "interacting.h"
#include "battle_system.h"
#include "t_draw_sys.h"
#include "explore_system.h"
using namespace std;using namespace my_container;
template<class T = int, class Comp = decltype(comp)>
auto get_p_q(Comp comp)
{
	return priority_queue<T, my_vector<T>, Comp>(comp);
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
	dr.load_all();

	//easyx
	initgraph(gra_size::window_width, gra_size::window_height, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();

	d.gold = 100;
	d.food = 5;
	d.player_s_class = player_class::WAR;
	d.is_vaccant = 0;
	d.is_battle = 1;

	//d.enemies_data.push_back(enemy(d, 35));
	//d.enemies_data.push_back(enemy(d, 1));
	//d.enemies_data.push_back(enemy(d, 1));
	//d.enemies_data.push_back(enemy(d, 1));
	d.enemies_data.push_back(enemy(d, 1));

	for (int i = 61; i < 121; ++i)
	{
		d.cards_pool.push_back(i);
	}

	e.create_map();

	//e.send_message(e_action(explore_action_type::ENCOUNTER_EVENT, MEANINGLESS_VALUE, d.explore_map[0][0], ""));
	goto battle;

explore:
	d.is_vaccant = 1;
	d.is_battle = 0;
	//explore loop
	e.end_battle();
	dr.end_battle();
	while (1)
	{
		e.update();
		dr.draw_explore();
		dr.t_draw_e();
		i.update();
		e.update();
		Sleep(100);
		if (!d.enemies_data.empty())
			goto battle;
	}

battle:
	//battle loop
	//explore sys sends message to battle sys through e_to_b_pipe
	//the message is processed in the initiate_battle function
	b.initiate_battle();
	while (1)
	{
		b.update();
		dr.draw_battle();
		dr.t_draw_b();
		i.update();
		//enemy act
		Sleep(30);
		if (d.enemies_data.empty())
		{
			goto explore;
		}
	}
	return 0;
}