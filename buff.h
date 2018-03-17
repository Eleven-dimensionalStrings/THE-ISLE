#pragma once
#include <string>
#include <cstddef>
#include "message.h"

inline unsigned int get_buff_life(std::size_t value)
{
	return value >> 16;
}

inline unsigned int get_buff_level(std::size_t value)
{
	return value &((1 << 16) - 1);
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
	buff(std::size_t, std::string, std::size_t, std::size_t, std::size_t);
	std::size_t buff_id;
	std::string buff_name;
	std::size_t buff_priority;
	std::size_t buff_life;
	std::size_t buff_level; 
	bool visible;

	//��change����buff֮��,���ظ�change�޸ĺ�Ľ��,�Ͷ�����ɵĲ���
	//�޸ĺ�Ľ������������һ��buff,����info������󷵻ظ�battle_sys
	info_to_battle_sys on_create(game_entity*, game_entity*); //�������������Ǵ���buff�Ķ��󣬱�����buff�Ķ���
	info_to_battle_sys on_delete(game_entity*, game_entity*);
	info_to_battle_sys on_kill();//���ڽ�ɫ����ʱ����
	info_to_battle_sys on_turn_begin();
	info_to_battle_sys on_turn_end();
	info_to_battle_sys on_calling(info_to_battle_sys);
	info_to_battle_sys on_performing(info_to_battle_sys);
	void operator--();
	void operator--(int);
	void operator+=(buff& t);
	//����1��ʾӦ�������buff
	bool operator-=(buff& t);
};
