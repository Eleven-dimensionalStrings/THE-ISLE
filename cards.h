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
	std::size_t upgrade_version_id;
	std::string card_name;
};