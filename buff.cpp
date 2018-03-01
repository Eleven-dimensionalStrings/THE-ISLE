#include "buff.h"
using namespace std;

void buff::operator--()
{
	--buff_life;
}

void buff::operator--(int)
{
	--buff_life;
}

void buff::operator+=(buff & t)
{
	buff_life += t.buff_life;
	buff_level += t.buff_level;
}

bool buff::operator-=(buff & t)
{
	buff_life -= t.buff_life;
	buff_level -= t.buff_level;
	if (buff_life <= 0 || buff_level <= 0)return 1;
	return 0;
}
