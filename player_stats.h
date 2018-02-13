#pragma once
#include "artifacts.h"
#include "cards.h"
#include <list> 
#include <queue>

class player_stats
{
public:

private:
	int player_max_hit_points;
	int player_current_hit_points;
	size_t gold;
	std::list<artifact> artifact_list; //to be replaced
	std::priority_queue<card> deck; //to be replaced
};