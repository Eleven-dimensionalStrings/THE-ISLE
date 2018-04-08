#include <iostream>
#include "message.h"
#include "interacting.h"
using namespace std;
int main()
{
	info_battle_to_interacting b_to_i_pipe;
	info_to_battle_sys i_to_b_pipe;
	data_sys d;
	interacting_sys i;

	while (1)
	{
		i.update();
	}
	return 0;
}