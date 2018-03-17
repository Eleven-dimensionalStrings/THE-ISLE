#include "interacting.h"
using namespace std;

context::context(interacting_sys * i_s)
	:i_s(i_s)
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
}

info_to_battle_sys interacting_sys::play_a_card(std::size_t card_pos, game_entity* target)
{
	info_to_battle_sys result(action(battle_action_type::USE_A_CARD, &data.player_data, target,
		data.cards_in_hand[card_pos].card_type, card_pos));
	result.append(data.cards_in_hand[card_pos].use());
	return result;
}

void interacting_sys::update()
{

}

state::state(battle_context * b_c)
	:ctx(b_c)
{

}

data_sys & state::get_data()
{
	return ctx->i_s->data;
}

void state::send_to_battle_sys(info_to_battle_sys t)
{
	ctx->i_s->next_info = t;
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
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::NEXT_TURN)));
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
			info_to_battle_sys temp;
			temp.action_set = get_data().card_effect[get_data().cards_in_hand[selected_card].card_id];
			for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
			{
				if (i->listener == &get_data().select_one_enemy)
				{
					i->listener = &get_data().enemies_data[enemy_pos];
				}
			}
			send_to_battle_sys(temp);
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
		info_to_battle_sys temp;
		temp.action_set = get_data().card_effect[get_data().cards_in_hand[selected_card].card_id];
		for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
		{
			if (i->listener == &get_data().all_enemies)
			{
				auto temp_action = *i;
				for (int j = 0; j < MAX_ENEMIES; +j)
				{
					if (get_data().enemies_data[j].is_alive())
					{
						temp_action.listener = &get_data().enemies_data[j];
						i = temp.action_set.insert(i, temp_action);
						++i;
					}
				}
				temp.action_set.erase(i++);
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
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::NEXT_TURN)));
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

select_state::select_state(battle_context * b_c, size_t num, bool mdy)
	:state(b_c), max(num), is_mandatory(mdy)
{
}

void select_state::click_a_card(std::size_t card_pos)
{
	if()
}
