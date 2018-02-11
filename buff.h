#define PRIORITY_LEVEL_1 1
#define PRIORITY_LEVEL_2 2
#define PRIORITY_LEVEL_3 3
#define PRIORITY_LEVEL_4 4
#define PRIORITY_LEVEL_5 5

#pragma once
#include <string>

class buff
{
public:
	size_t buff_id;
	std::string buff_name;
	size_t buff_priority;
	int buff_life;
	int buff_level;  

	virtual void on_create() = 0;
	virtual void on_delete() = 0;
	virtual void on_dealing_damage() = 0;
	virtual void on_recieving_damage() = 0;
};

class buff_burning : public buff
{
public:
	void on_create() ;
	void on_delete() ;
	void 
};