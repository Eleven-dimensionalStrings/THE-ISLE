#pragma once
#include <string>
#include <cstdlib>
#include <cstddef>
class card
{
public:
	card();
	card(std::size_t id, std::size_t up_id, std::string name);
	card(card& copy_card);
	card(card&& move_card);
	std::size_t card_id;
	std::string card_name;
	std::size_t card_type;
	std::size_t upgrade_version_id;
	bool reserve;
	std::size_t target_type;
	info_to_battle_sys use();
	info_to_battle_sys discard();
	info_to_battle_sys remove();
	info_to_battle_sys on_turn_end();
};