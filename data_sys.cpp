#include "data_sys.h"
using namespace std;

data_sys::data_sys() :player_data(*this), all_enemies(*this), random_enemy(*this), select_one_enemy(*this)
{
}

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	return buff_data[id];
}
