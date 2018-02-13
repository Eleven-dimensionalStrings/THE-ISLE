#pragma once
#include <string>

class card
{
public:
	virtual size_t get_card_id() = 0;
	virtual size_t get_upgrade_version_id() = 0;
	virtual std::string get_card_name() = 0;
	virtual bool is_upgraded() = 0;
private:
	size_t card_id;
	size_t upgrade_version_id;
	std::string card_name;
};