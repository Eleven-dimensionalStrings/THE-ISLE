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
	while (1)
	{
		i.update();
		b.update();
		dr.draw();
	}
	return 0;
}