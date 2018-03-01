#pragma once
#include <string>
#include <cstddef>
#include "message.h"
namespace BUFF_PRIORITY
{
	const size_t PRIORITY_LEVEL_1 = 1;
	const size_t PRIORITY_LEVEL_2 = 2;
	const size_t PRIORITY_LEVEL_3 = 3;
	const size_t PRIORITY_LEVEL_4 = 4;
	const size_t PRIORITY_LEVEL_5 = 5;
}



class buff : public message_dispatcher
{
public:
	std::size_t buff_id;
	std::string buff_name;
	std::size_t buff_priority;
	std::size_t buff_life;
	std::size_t buff_level;  
	info_to_battle_sys create_message_to_battle_sys();

	//��change����buff֮��,���ظ�change�޸ĺ�Ľ��,�Ͷ�����ɵĲ���
	//�޸ĺ�Ľ������������һ��buff,����info������󷵻ظ�battle_sys
	info_to_battle_sys on_create();
	info_to_battle_sys on_delete();
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