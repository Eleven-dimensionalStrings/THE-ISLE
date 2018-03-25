#include "cards.h"
using namespace std;
using std::size_t;

card::card()
{
}

card::card(size_t id, size_t up_id, string name) :card_id(id), upgrade_version_id(up_id), card_name(std::move(name))
{
}

card::card(const card& copy_card):is_reserve(copy_card.is_reserve) , card_id(copy_card.card_id),
card_type(copy_card.card_type), upgrade_version_id(copy_card.upgrade_version_id),
card_name(copy_card.card_name)
{
}


info_to_battle_sys card::use_card()
{
	return info_to_battle_sys();
}

info_to_battle_sys card::discard()
{
	return info_to_battle_sys();
}

info_to_battle_sys card::remove()
{
	return info_to_battle_sys();
}

info_to_battle_sys card::on_turn_end()
{
	return info_to_battle_sys();
}
