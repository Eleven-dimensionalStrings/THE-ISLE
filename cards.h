#pragma once
#include <string>
#include <cstdlib>
#include <cstddef>
#include "message.h"
class card
{
public:
	card();
	card(std::size_t id, std::size_t up_id, std::string name);
	card(card& copy_card);
	card(card&& move_card);

	bool is_reserve;

	std::size_t card_id;
	std::string card_name;
	std::size_t card_type;
	std::size_t upgrade_version_id;
	bool require_target; //true代表需要选择目标，false代表不用

	info_to_battle_sys use_card();
	info_to_battle_sys discard();
	info_to_battle_sys remove();
	info_to_battle_sys on_turn_end();
};