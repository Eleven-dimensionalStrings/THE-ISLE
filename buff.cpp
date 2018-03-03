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

buff::buff(std::size_t id, std::size_t life, std::size_t level)
	:buff_id(id), buff_name(""), buff_priority(0), buff_life(life), buff_level(level)
{
}

buff::buff(std::size_t id, std::string name, std::size_t priority, std::size_t life, std::size_t level)
	: buff_id(id), buff_name(name), buff_priority(priority), buff_life(life), buff_level(level)
{
}

info_to_battle_sys buff::on_create(game_entity* creater, game_entity* receiver)
{
	//switch
	return info_to_battle_sys();
}

info_to_battle_sys buff::on_delete(game_entity *, game_entity *)
{
	//switch
	return info_to_battle_sys();
}
