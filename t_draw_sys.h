#pragma once
#include <iostream>
#include "data_sys.h"
#include "message.h"
class t_draw_sys
{
	data_sys& data;
public:
	t_draw_sys(data_sys&);
	void draw();
};