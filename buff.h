#pragma once
#include <string>
#include <cstddef>
#define PRIORITY_LEVEL_1 1
#define PRIORITY_LEVEL_2 2
#define PRIORITY_LEVEL_3 3
#define PRIORITY_LEVEL_4 4
#define PRIORITY_LEVEL_5 5



class buff : public message_dispatcher
{
public:
	std::size_t buff_id;
	std::string buff_name;
	std::size_t buff_priority;
	int buff_life;
	int buff_level;  
	info_to_battle_sys create_message_to_battle_sys();

	//��change����buff֮��,���ظ�change�޸ĺ�Ľ��,�Ͷ�����ɵĲ���
	//�޸ĺ�Ľ������������һ��buff,����info������󷵻ظ�battle_sys
	std::pair<change,info_to_battle_sys> on_create();
	std::pair<change, info_to_battle_sys> on_delete();
	std::pair<change, info_to_battle_sys> on_kill();//���ڽ�ɫ����ʱ����
	std::pair<change, info_to_battle_sys> on_calling(change);
	std::pair<change, info_to_battle_sys> on_recieving(change);
};