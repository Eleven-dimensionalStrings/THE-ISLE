#include "data_sys.h"
using namespace std;

pair<std::string, std::size_t> data_sys::get_buff(std::size_t id)
{
	return buff_data[id];
}
