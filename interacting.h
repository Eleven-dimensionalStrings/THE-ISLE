#pragma once
#include <iostream>
#include "message.h"
#include "data_sys.h"
#include "explore_system.h"
class b_state;
class interacting_sys;

class context
{
public:
	context(interacting_sys*);
	virtual ~context();
	virtual void read_input() = 0;
	interacting_sys* i_s;
};

class battle_context : public context
{
public:
	battle_context(interacting_sys*);
	battle_context(interacting_sys*, b_state*);
	virtual ~battle_context();
	void set_state(b_state*);
	void read_input()override;
	void change_to_select_state(info_battle_to_interacting);
	void change_to_vaccant_state();
	data_sys& get_data();
private:
	b_state * cur_state;
};

class e_state;
class explore_context : public context
{
public:
	explore_context(interacting_sys*);
	explore_context(interacting_sys*, e_state*);
	virtual ~explore_context();
	void change_to_select_state(std::size_t tmax);
	void change_to_vaccant_state();
	void set_state(e_state*);
	void read_input()override;
	data_sys& get_data();
private:
	e_state * cur_state;
};

class b_state
{
public:
	b_state(battle_context*);
	virtual void click_a_card(std::size_t) = 0;
	virtual void click_an_enemy(std::size_t) = 0;
	virtual void click_confirm() = 0;
	virtual void click_cancel() = 0;
	virtual void click_turn_end() = 0;
	data_sys& get_data();
	void send_to_battle_sys(info_to_battle_sys);
	battle_context* ctx;
};

class b_vaccant_state : public b_state
{
public:
	b_vaccant_state(battle_context*);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
};

class b_confirm_state : public b_state
{
public:
	b_confirm_state(battle_context*, std::size_t, std::size_t);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
private:
	std::size_t selected_card;
	std::size_t cost;
	bool require_target;
};

class render_sys;
class b_select_state : public b_state
{
public:
	friend class render_sys;
	b_select_state(battle_context*, std::size_t tmax, std::size_t, bool);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
private:
	std::size_t type;
	my_container::my_vector<std::size_t> selected_cards;
	std::size_t max; //indicates the max amount of cards to select
	bool is_mandatory; //indicates if the player is forced to select the max amount of cards
};

//the lock state is the state in the enemies' turn
//all functions are empty in lock state
class b_lock_state : public b_state
{
public:
	b_lock_state(battle_context*);
	void click_a_card(std::size_t card_No);
	void click_an_enemy(std::size_t card_No);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
};

class e_state
{
public:
	e_state(explore_context*);
	virtual void click_an_option(std::size_t) = 0;
	virtual void click_next() = 0;
	virtual void click_left_arrow() = 0;
	virtual void click_right_arrow() = 0;
	virtual void click_map_location(std::size_t, std::size_t) = 0;
	data_sys& get_data();
	void send_to_explore_sys(info_to_explore_sys);
	explore_context* ctx;
};

class e_vaccant_state : public e_state
{
public:
	e_vaccant_state(explore_context*);
	void click_an_option(std::size_t);
	void click_next();
	void click_left_arrow();
	void click_right_arrow();
	void click_map_location(std::size_t x, std::size_t y);
};

class e_select_state : public e_state
{
public:
	e_select_state(explore_context*, std::size_t tmax);
	void click_an_option(std::size_t);
	void click_next();
	void click_left_arrow();
	void click_right_arrow();
	void click_map_location(std::size_t x, std::size_t y);
private:
	std::size_t max_selection;
	std::size_t current;
};

class interacting_sys
{
public:
	interacting_sys(data_sys& d);
	data_sys& data;
	battle_context* present_battle_context;
	explore_context* present_explore_context;
	void move_player(int x, int y);
	void set_map_location(int x, int y, int mark_type);
	void update();
};