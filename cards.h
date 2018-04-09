#pragma once
#include <string>
#include <cstdlib>
#include <cstddef>
#include "message.h"
class data_sys;
class card
{
public:
	card();
	card(std::size_t id, std::size_t up_id, std::string name,bool r_target);
	card(const card& copy_card);
	card& operator=(const card& copy_card);

	bool is_reserve;

	std::size_t card_id;
	std::string card_name;
	std::size_t card_type;
	std::size_t upgrade_version_id; //0 means the card has no upgrade version(already upgraded);
	bool require_target; //true代表需要选择目标，false代表不用

	
	info_to_battle_sys use_card(data_sys&);
	info_to_battle_sys discard(data_sys&);
	info_to_battle_sys remove(data_sys&);
	info_to_battle_sys on_turn_end(data_sys&);
};