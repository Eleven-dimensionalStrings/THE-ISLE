#include "cards.h"
#include "data_sys.h"
using namespace std;
using std::size_t;

card::card()
{
}

card::card(size_t id, size_t up_id, string name) :is_reserve(0),
card_id(id), card_name(std::move(name)), card_type(0), upgrade_version_id(up_id), require_target(1)
{
}

card::card(const card& copy_card) : is_reserve(copy_card.is_reserve), card_id(copy_card.card_id),
card_name(copy_card.card_name),card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id)
{
}

card & card::operator=(const card & c)
{
	this->is_reserve = c.is_reserve;
	this->card_id = c.card_id;
	this->card_name = c.card_name;
	this->card_type = c.card_type;
	this->upgrade_version_id = c.upgrade_version_id;
	return *this;
}


info_to_battle_sys card::use_card(data_sys&d)
{
	return info_to_battle_sys(d.card_effect.find(card_id)->second);
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

