#include "managers.h"

namespace card_No
{
	const int COMMON_BATTLE=0;
	const int COMMON_EFFECT=1;
	const int COMMON_ABILITY=2;
	const int RARE_BATTLE=3;
	const int RARE_EFFECT=4;
	const int RARE_ABILITY=5;
}

random_engine* random_engine::instantiate_engine()
{
	return new random_engine();
}

bool random_engine::random_event(int success_rate)
{
	std::uniform_int_distribution<int> distribute(0, 100);
	if (distribute(generator) <= success_rate)
		return true;
	else
		return false;
}

int random_engine::random_battle_cards(int number, card_generate_value value)
{

}