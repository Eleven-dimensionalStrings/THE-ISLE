#include "player_stats.h"

void player_stats::set_player_max_hit_points(int input)
{
	player_max_hit_points = input;
}

int player_stats::get_player_max_hit_points()
{
	return player_max_hit_points;
}

void player_stats::set_player_current_hit_points(int input)
{
	player_current_hit_points = input;
}

int player_stats::get_player_current_hit_points()
{
	return player_current_hit_points;
}

void player_stats::set_player_gold(int input)
{
	gold = input;
}

int player_stats::get_player_gold()
{
	return gold;
}

void player_stats::add_artifact(artifact* input)
{
	artifact_list.push_back(*input);
}

void player_stats::delete_artifact(int input)
{
	artifact_list.erase(artifact_list.begin(), artifact_list.begin() + input);
}

void player_stats::add_card(card* input)
{
	deck.push(*input);
}

void player_stats::delete_card(int input)
{
	deck.pop();
}

void player_stats::upgrade_card(int input)
{
	
}

void player_stats::change_card(int input)
{

}