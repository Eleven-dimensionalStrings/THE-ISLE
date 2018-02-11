#pragma once
#include <string>
#include <sstream>

class message_handler
{
public:
	virtual bool send_message() = 0;
protected:
	virtual std::string create_message() = 0;
	virtual bool interpret_message() = 0;
};

class buff_handler
{
	std::string add_buff();
	std::string remove_buff();
	std::string next_turn();
	bool has_buff();
};