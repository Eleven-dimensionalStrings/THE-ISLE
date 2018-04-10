#pragma once
#include <string>
#include <cstddef>
#include "message.h"

inline std::size_t get_buff_life(std::size_t value)
{
	return value >> 16;
}

inline std::size_t get_buff_level(std::size_t value)
{
	return value &((1 << 16) - 1);
}

inline std::size_t fix_buff_value(std::size_t life, std::size_t level)
{
	return (life << 16) + level;
}

namespace BUFF_PRIORITY
{
	const std::size_t PRIORITY_LEVEL_1 = 1;
	const std::size_t PRIORITY_LEVEL_2 = 2;
	const std::size_t PRIORITY_LEVEL_3 = 3;
	const std::size_t PRIORITY_LEVEL_4 = 4;
	const std::size_t PRIORITY_LEVEL_5 = 5;
}

class buff
{
public:
	buff(std::size_t, std::size_t, std::size_t);
	buff(std::size_t id, std::string name, std::size_t priority, std::size_t life, int level);
	std::size_t buff_id;
	std::string buff_name;
	std::size_t buff_priority;
	std::size_t buff_life;
	int buff_level; 
	bool visible;

	//将change传给buff之后,返回该change修改后的结果,和额外造成的操作
	//修改后的结果将被传给下一个buff,所有info被打包后返回给battle_sys
	info_to_battle_sys on_create(game_entity*, game_entity*); //两个参数依次是创建buff的对象，被创建buff的对象
	info_to_battle_sys on_delete(game_entity*, game_entity*);
	info_to_battle_sys on_kill();//所在角色死亡时调用
	info_to_battle_sys on_turn_begin(game_entity*);
	info_to_battle_sys on_turn_end(game_entity*);
	info_to_battle_sys on_calling(info_to_battle_sys);
	info_to_battle_sys on_performing(info_to_battle_sys);
	void operator--();
	void operator--(int);
	void operator+=(buff t);
	//返回1表示应该清除该buff
	bool operator-=(buff& t);
};
