#include "managers.h"

namespace card_No
{
	const int COMMON_BATTLE;
	const int COMMON_EFFECT;
	const int COMMON_ABILITY;
	const int RARE_BATTLE;
	const int RARE_EFFECT;
	const int RARE_ABILITY;
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