#include "cards.h"
#include "data_sys.h"
#include <iostream>
using namespace std;
using std::size_t;

card::card()
{
}

card::card(size_t id, size_t up_id, string name, bool r_target) :is_reserve(0),
card_id(id), card_name(std::move(name)), card_type(0), upgrade_version_id(up_id), require_target(r_target)
{
	cout << require_target << endl;
}

card::card(const card& copy_card) : is_reserve(copy_card.is_reserve), card_id(copy_card.card_id),
card_name(copy_card.card_name), card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id),
require_target(copy_card.require_target)
{
}

card & card::operator=(const card & c)
{
	this->is_reserve = c.is_reserve;
	this->card_id = c.card_id;
	this->card_name = c.card_name;
	this->card_type = c.card_type;
	this->upgrade_version_id = c.upgrade_version_id;
	this->require_target = c.require_target;
	return *this;
}


info_to_battle_sys card::use_card(data_sys&d)
{
	return d.card_effect(card_id);
}

info_to_battle_sys card::discard(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::remove(data_sys&)
{
	return info_to_battle_sys();
}

info_to_battle_sys card::on_turn_end(data_sys&)
{
	return info_to_battle_sys();
}

