#pragma once
#include <iostream>
#include "message.h"
#include "data_sys.h"
class state;
class interacting_sys;

class context
{
public:
	context(interacting_sys*);
	virtual ~context();
	virtual void set_state(state*) = 0;
	virtual void read_input() = 0;
	interacting_sys* i_s;
};

class battle_context : public context
{
public:
	battle_context(interacting_sys*);
	battle_context(interacting_sys*, state*);
	virtual ~battle_context();
	void set_state(state*)override;
	void read_input()override;
	void change_to_select_state(info_battle_to_interacting);
	data_sys& get_data();
	void test_read();
private:
	state *cur_state;
};

class state
{
public:
	state(battle_context*);
	virtual void click_a_card(std::size_t) = 0;
	virtual void click_an_enemy(std::size_t) = 0;
	virtual void click_confirm() = 0;
	virtual void click_cancel() = 0;
	virtual void click_turn_end() = 0;
	virtual ~state();
	data_sys& get_data();
	void send_to_battle_sys(info_to_battle_sys);
	battle_context* ctx;
};

class vaccant_state : public state
{
public:
	vaccant_state(battle_context*);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
};

class confirm_state : public state
{
public:
	confirm_state(battle_context*, std::size_t);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
private:
	std::size_t selected_card;
	bool require_target;
};

class select_state : public state
{
public:
	select_state(battle_context*, std::size_t tmax, std::size_t, bool);
	void click_a_card(std::size_t);
	void click_an_enemy(std::size_t);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
private:
	std::size_t type;
	std::vector<std::size_t> selected_cards;
	std::size_t max; //indicates the max amount of cards to select
	bool is_mandatory; //indicates if the player is forced to select the max amount of cards
};

//the lock state is the state in the enemies' turn
//all functions are empty in lock state
class lock_state : public state
{
public:
	lock_state(battle_context*);
	void click_a_card(std::size_t card_No);
	void click_an_enemy(std::size_t card_No);
	void click_confirm();
	void click_cancel();
	void click_turn_end();
};

class interacting_sys
{
public:
	interacting_sys(data_sys& d);
	data_sys& data;
	context* present_context;
	bool send_message();
	bool interpret_message();
	info_to_battle_sys play_a_card(std::size_t card_pos, game_entity* target);//没用的,出牌操作在context中完成
	void update();
};