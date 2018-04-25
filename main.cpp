#include <iostream>
#include "message.h"
#include "interacting.h"
#include "battle_system.h"
#include "render_sys.h"
#include "explore_system.h"
using namespace std; using namespace my_container;
int main()
{
	data_sys d;
	battle_system b(d);
	interacting_sys i(d);
	explore_system e(d);
	IMAGE buffer(gra_size::window_width, gra_size::window_height);
	render_sys dr(d);
	d.b = &b;

	//easyx
	initgraph(gra_size::window_width, gra_size::window_height);
	settextstyle(20, 0, "Airial");
	cleardevice();
	setbkcolor(WHITE);
	IMAGE timage;
	loadimage(&timage, ".\\resource\\cover\\loading.bmp\0");
	putimage(0, 0, &timage);

	dr.load_all();
	d.gold = 120;
	d.food = 5;
	d.player_s_class = player_class::WAR;
	d.create_starting_deck();
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
		//dr.t_draw_e();
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
		i.update();
		dr.update();
		dr.draw_battle();

		//enemy act
		Sleep(40);
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