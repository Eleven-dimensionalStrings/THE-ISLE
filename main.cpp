#include <iostream>
#include "message.h"
#include "interacting.h"
#include "battle_system.h"
#include "t_draw_sys.h"
#include "explore_system.h"
using namespace std; using namespace my_container;
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
	settextstyle(20, 0, "Airial");
	cleardevice();

	d.gold = 200;
	d.food = 5;
	d.player_s_class = player_class::WAR;
	/*d.strength = 20;
	d.vitality = 20;
	d.dexterity = 20;*/

	//d.enemies_data.push_back(enemy(d, 35));
	//d.enemies_data.push_back(enemy(d, 1));
	//d.enemies_data.push_back(enemy(d, 1));
	//d.enemies_data.push_back(enemy(d, 1));
	//d.enemies_data.push_back(enemy(d, 1));

	d.cards_pool.push_back(card(4));
	d.cards_pool.push_back(card(4));
	d.cards_pool.push_back(card(4));
	d.cards_pool.push_back(card(61));
	d.cards_pool.push_back(card(62));
	d.cards_pool.push_back(card(63));
	d.cards_pool.push_back(card(90));
	d.cards_pool.push_back(card(90));
	d.cards_pool.push_back(card(90));
	d.cards_pool.push_back(card(71));

	d.artifacts.push_back(artifact(16));
	d.artifacts.push_back(artifact(17));
	d.artifacts.push_back(artifact(18));
	d.artifacts.push_back(artifact(19));
	d.artifacts.push_back(artifact(20));

	e.create_map();

explore:
	//explore loop
	if (!(d.next_event_id && d.next_event_id != MEANINGLESS_VALUE))
	{
		d.is_vaccant = 1;
		d.is_battle = 0;
	}
	d.background_pic = random_engine(&d).get_num(1, 13);
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
	d.is_vaccant = 0;
	d.is_battle = 1;
	i.present_battle_context->set_state(new b_vaccant_state(i.present_battle_context));
	b.initiate_battle();
	d.background_pic = random_engine(&d).get_num(1, 13);
	while (1)
	{
		settextstyle(20, 0, "Airial");
		b.update();
		dr.update();
		dr.draw_battle();
		dr.t_draw_b();
		i.update();
		dr.update();
		dr.draw_battle();
		dr.t_draw_b();

		//enemy act
		Sleep(30);
		if (d.enemies_data.empty())
		{
			e.end_battle();
			dr.end_battle();
			b.update();
			goto explore;
		}
		if (b.battle_fail())break;
	}

	//game over
	dr.game_over();
	return 0;
}