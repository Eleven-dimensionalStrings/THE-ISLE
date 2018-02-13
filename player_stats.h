#pragma once
#include "artifacts.h"
#include "cards.h"
#include <vector> 
#include <queue>

class player_stats
{
public:
	static void set_player_max_hit_points(int);
	static int get_player_max_hit_points();

	static void set_player_current_hit_points(int);
	static int get_player_current_hit_points();

	static void set_player_gold(int);
	static int get_player_gold();

	static void add_artifact(artifact*);
	static void delete_artifact(int);

	static void add_card(card*);
	static void delete_card(int);
	static void upgrade_card(int);
	static void change_card(int);

private:
	static int player_max_hit_points;
	static int player_current_hit_points;
	static size_t gold;
	static std::vector<artifact> artifact_list; //to be replaced
	static std::priority_queue<card> deck; //to be replaced
};