#include "interacting.h"
using namespace std;
using std::size_t;
using std::size_t;

context::context(interacting_sys * i_s)
	:i_s(i_s)
{

}

context::~context()
{
}

battle_context::battle_context(interacting_sys* i_s)
	: context(i_s), cur_state(new vaccant_state(this))
{

}

battle_context::battle_context(interacting_sys* i_s, state * pstate)
	: context(i_s), cur_state(pstate)
{

}

battle_context::~battle_context()
{
	delete cur_state;
}

void battle_context::set_state(state * pstate)
{
	delete cur_state;
	cur_state = pstate;
}

void battle_context::read_input()
{
	//²âÊÔ
	test_read();
}

void battle_context::change_to_select_state(info_battle_to_interacting t)
{
	set_state(new select_state(this, t.num, t.type, t.is_m));
}

data_sys & battle_context::get_data()
{
	return i_s->data;
}

void battle_context::test_read()
{
	size_t card_pos, target_pos;
	cin >> card_pos;
	set_state(new confirm_state(this, card_pos));
	if (get_data().cards_in_hand[card_pos].require_target)
	{
		cin >> target_pos;
		cur_state->click_an_enemy(target_pos);
		return;
	}
	cur_state->click_confirm();
}

interacting_sys::interacting_sys(data_sys & d) :data(d),
present_context(new battle_context(this))
{
}

bool interacting_sys::send_message()
{
	return false;
}

bool interacting_sys::interpret_message()
{
	return false;
}

info_to_battle_sys interacting_sys::play_a_card(std::size_t card_pos, game_entity* target)
{
	info_to_battle_sys result(action(battle_action_type::USE_A_CARD, &data.player_data, target,
		data.cards_in_hand[card_pos].card_type, card_pos));
	auto ef = data.card_effect(data.cards_in_hand[card_pos].card_id);
	result.append(ef);
	for (auto& i : result.action_set)
		i.caller = &data.player_data;
	return result;
}

void interacting_sys::update()
{
	if (data.b_to_i_pipe)
	{
		(dynamic_cast<battle_context*>(present_context))->change_to_select_state(data.b_to_i_pipe);
		data.b_to_i_pipe.clear();
		return;
	}
	//´ý¶¨
	//else if (from_explore_sys)
	{
		//Í¬ÉÏ
	}
	present_context->read_input();
}

state::state(battle_context * b_c)
	:ctx(b_c)
{

}

state::~state()
{
}

data_sys & state::get_data()
{
	return ctx->i_s->data;
}

void state::send_to_battle_sys(info_to_battle_sys t)
{
	get_data().i_to_b_pipe = t;
}

vaccant_state::vaccant_state(battle_context * b_c)
	:state(b_c)
{

}

void vaccant_state::click_a_card(size_t card_pos)
{
	ctx->set_state(new confirm_state(ctx, card_pos));
}

void vaccant_state::click_an_enemy(size_t enemy_No)
{
	//nothing happens
}

void vaccant_state::click_confirm()
{
	//nothing happens
}

void vaccant_state::click_cancel()
{
	//nothing happens
}

void vaccant_state::click_turn_end()
{
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::TURN_END)));
	ctx->set_state(new lock_state(ctx));
}

confirm_state::confirm_state(battle_context * b_c, size_t card_pos)
	:state(b_c), selected_card(card_pos), require_target(false)
{
	if (get_data().cards_in_hand[card_pos].require_target)
	{
		require_target = true;
	}
}

void confirm_state::click_a_card(size_t card_pos)
{
	if (card_pos == selected_card)
	{
		ctx->set_state(new vaccant_state(ctx));
	}
	else
	{
		ctx->set_state(new confirm_state(ctx, card_pos));
	}
}

void confirm_state::click_an_enemy(size_t enemy_pos)
{
	if (require_target)
	{
		game_entity* target;
		if (get_data().enemies_data[enemy_pos].is_alive())
		{
			target = &get_data().enemies_data[enemy_pos];
			info_to_battle_sys temp = get_data().cards_in_hand[selected_card].use_card(get_data());
			for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
			{
				i->caller = &get_data().player_data;
				if (i->listener == &get_data().select_one_enemy)
				{
					i->listener = target;
				}
			}
			send_to_battle_sys(temp);
			ctx->set_state(new vaccant_state(ctx));
		}
		else
		{
			ctx->set_state(new vaccant_state(ctx));
		}
	}
}

void confirm_state::click_confirm()
{
	if (!require_target)
	{
		info_to_battle_sys temp(get_data().card_effect(get_data().cards_in_hand[selected_card].card_id));
		for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
		{
			if (i->listener == &get_data().all_enemies)
			{
				auto temp_action = *i;
				for (size_t j = 0; j < MAX_ENEMIES; ++j)
				{
					if (get_data().enemies_data[j].is_alive())
					{
						temp_action.listener = &get_data().enemies_data[j];
						i = temp.action_set.insert(i, temp_action);
						++i;
					}
				}
				temp.action_set.erase(i);
			}
		}
		send_to_battle_sys(temp);
	}
}

void confirm_state::click_cancel()
{
	ctx->set_state(new vaccant_state(ctx));
}

void confirm_state::click_turn_end()
{
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::TURN_END)));
	ctx->set_state(new lock_state(ctx));
}

lock_state::lock_state(battle_context * b_c)
	:state(b_c)
{
}

void lock_state::click_a_card(size_t card_pos)
{
	//nothing happens
}

void lock_state::click_an_enemy(size_t card_pos)
{
	//nothing happens
}

void lock_state::click_confirm()
{
	//nothing happens
}

void lock_state::click_cancel()
{
	//nothing happens
}

void lock_state::click_turn_end()
{
	//nothing happens
}

select_state::select_state(battle_context * b_c, size_t num, size_t ttype, bool mdy)
	:state(b_c), type(ttype), max(num), is_mandatory(mdy)
{
}


void select_state::click_a_card(std::size_t card_pos)
{
	bool is_selected = 0;
	for (auto i = selected_cards.begin(); i != selected_cards.end(); ++i)
	{
		if (*i == card_pos)
		{
			selected_cards.erase(i);
			return;
		}
	}
	if (selected_cards.size() == max)return;
	selected_cards.push_back(card_pos);
}

void select_state::click_an_enemy(std::size_t)
{
	//nothing happens
}

void select_state::click_confirm()
{
	info_to_battle_sys t;
	for (auto& i : selected_cards)
	{
		t.append(action(type + TYPE_TO_P_TYPE, 0, i));
	}
	send_to_battle_sys(t);
	ctx->set_state(new vaccant_state(ctx));
}

void select_state::click_cancel()
{
	//nothing happens
}

void select_state::click_turn_end()
{
	//nothing happened
}
