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

	//将change传给buff之后,返回该change修改后的结果,和额外造成的操作
	//修改后的结果将被传给下一个buff,所有info被打包后返回给battle_sys
	std::pair<change,info_to_battle_sys> on_create();
	std::pair<change, info_to_battle_sys> on_delete();
	std::pair<change, info_to_battle_sys> on_kill();//所在角色死亡时调用
	std::pair<change, info_to_battle_sys> on_calling(change);
	std::pair<change, info_to_battle_sys> on_recieving(change);
};