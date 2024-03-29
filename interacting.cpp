#include "interacting.h"
#include <random>
#include <ctime>
#include <graphics.h>
#include <Windows.h>
#include "battle_system.h"
using namespace std; using namespace my_container;
using std::size_t;
//写easyx的不知道哪个弱智把这宏放出来了,为什么要用这种垃圾
#undef max

context::context(interacting_sys * i_s)
	:i_s(i_s)
{

}

context::~context()
{
}

battle_context::battle_context(interacting_sys* i_s)
	: context(i_s), cur_state(new b_vaccant_state(this))
{

}

battle_context::battle_context(interacting_sys* i_s, b_state * pstate)
	: context(i_s), cur_state(pstate)
{

}

battle_context::~battle_context()
{
	delete cur_state;
}

void battle_context::set_state(b_state * pstate)
{
	delete cur_state;
	cur_state = dynamic_cast<b_state*>(pstate);
}

void battle_context::read_input()
{
	while (MouseHit())
	{
		auto hit = GetMouseMsg();
		if (hit.mkLButton)
		{
			//检测点击卡
			if (hit.x > gra_size::card_x + gra_size::card_starting_pos && hit.x < gra_size::card_x + gra_size::card_starting_pos + gra_size::card_rx
				&& hit.y > gra_size::card_y && hit.y < gra_size::card_dy)
			{
				size_t pos = (hit.x - gra_size::card_closure - gra_size::card_starting_pos) / (gra_size::card_width + gra_size::card_closure);
				if (pos <= get_data().cards_in_hand.size())
				{
					cur_state->click_a_card(pos);
				}
			}
			//检测点击敌人
			else if (hit.x > gra_size::enemy_x && hit.x < gra_size::enemy_x + gra_size::enemy_width*gra_size::max_enemies
				&& hit.y > gra_size::enemy_y && hit.y < gra_size::enemy_y + 200)//需要改为敌人高度
			{
				size_t pos = (hit.x - gra_size::enemy_x) / gra_size::enemy_width;
				if (pos < get_data().enemies_data.size())
				{
					cur_state->click_an_enemy(pos);
				}
			}
			//检测点击confirm
			else if (hit.x > gra_size::confirm_button_x && hit.y > gra_size::confirm_button_y
				&& hit.x < gra_size::confirm_button_x + 100 && hit.y < gra_size::confirm_button_y + 50)
			{
				cur_state->click_confirm();
			}
			//检测点击cancel
			else if (hit.x > gra_size::cancel_button_x && hit.y > gra_size::cancel_button_y
				&& hit.x < gra_size::cancel_button_x + 100 && hit.y < gra_size::cancel_button_y + 50)
			{
				cur_state->click_cancel();
			}
			//检测点击turn end
			else if (hit.x > gra_size::turn_end_button_x && hit.y > gra_size::turn_end_button_y
				&& hit.x < gra_size::turn_end_button_x + 100 && hit.y < gra_size::turn_end_button_y + 50)
			{
				cur_state->click_turn_end();
			}
			//点击card_deck等
			else if (hit.x > gra_size::deck_pic_x && hit.y > gra_size::deck_pic_y
				&& hit.x < gra_size::deck_pic_x + gra_size::deck_width && hit.y < gra_size::deck_pic_y + gra_size::deck_height)
			{
				get_data().view_cards = 1;
			}
			else if (hit.x > gra_size::r_deck_pic_x && hit.y > gra_size::r_deck_pic_y
				&& hit.x < gra_size::r_deck_pic_x + gra_size::deck_width && hit.y < gra_size::r_deck_pic_y + gra_size::deck_height)
			{
				get_data().view_cards = 2;
			}
			else if (hit.x > gra_size::grave_pic_x && hit.y > gra_size::grave_pic_y
				&& hit.x < gra_size::grave_pic_x + gra_size::deck_width && hit.y < gra_size::grave_pic_y + gra_size::deck_height)
			{
				get_data().view_cards = 3;
			}
			else if (hit.x > gra_size::remove_pic_x && hit.y > gra_size::remove_pic_y
				&& hit.x < gra_size::remove_pic_x + gra_size::deck_width && hit.y < gra_size::remove_pic_y + gra_size::deck_height)
			{
				get_data().view_cards = 4;
			}
			else if (hit.x > gra_size::view_artifact_x && hit.y > gra_size::view_artifact_y
				&& hit.x < gra_size::view_artifact_x + gra_size::deck_width && hit.y < gra_size::view_artifact_y + gra_size::deck_height)
			{
				get_data().view_cards = 5;
			}

			Sleep(100);
			FlushMouseMsgBuffer();
		}
	}
}

void battle_context::change_to_select_state(info_battle_to_interacting t)
{
	set_state(new b_select_state(this, t.num, t.type, t.is_m));
}

void battle_context::change_to_vaccant_state()
{
	set_state(new b_vaccant_state(this));
}

explore_context::explore_context(interacting_sys* i_s)
	: context(i_s), cur_state(new e_vaccant_state(this))
{

}

explore_context::explore_context(interacting_sys* i_s, e_state * pstate)
	: context(i_s), cur_state(pstate)
{

}

void explore_context::change_to_select_state(std::size_t tmax)
{
	set_state(new e_select_state(this, tmax));
}

void explore_context::change_to_vaccant_state()
{
	set_state(new e_vaccant_state(this));
}

explore_context::~explore_context()
{
	delete cur_state;
}

void explore_context::set_state(e_state * pstate)
{
	delete cur_state;
	cur_state = pstate;
}

void explore_context::read_input()
{
	while (MouseHit())
	{
		auto hit = GetMouseMsg();
		if (hit.mkLButton)
		{
			if (hit.x > gra_size::deck_pic_x && hit.y > gra_size::deck_pic_y
				&& hit.x < gra_size::deck_pic_x + gra_size::deck_width && hit.y < gra_size::deck_pic_y + gra_size::deck_height)
			{
				get_data().view_cards = 1;
			}
			else if (hit.x > gra_size::r_deck_pic_x && hit.y > gra_size::r_deck_pic_y
				&& hit.x < gra_size::r_deck_pic_x + gra_size::deck_width && hit.y < gra_size::r_deck_pic_y + gra_size::deck_height
				&& get_data().is_battle)
			{
				get_data().view_cards = 2;
			}
			else if (hit.x > gra_size::grave_pic_x && hit.y > gra_size::grave_pic_y
				&& hit.x < gra_size::grave_pic_x + gra_size::deck_width && hit.y < gra_size::grave_pic_y + gra_size::deck_height
				&& get_data().is_battle)
			{
				get_data().view_cards = 3;
			}
			else if (hit.x > gra_size::remove_pic_x && hit.y > gra_size::remove_pic_y
				&& hit.x < gra_size::remove_pic_x + gra_size::deck_width && hit.y < gra_size::remove_pic_y + gra_size::deck_height
				&& get_data().is_battle)
			{
				get_data().view_cards = 4;
			}
			else if (hit.x > gra_size::view_artifact_x && hit.y > gra_size::view_artifact_y
				&& hit.x < gra_size::view_artifact_x + gra_size::deck_width && hit.y < gra_size::view_artifact_y + gra_size::deck_height)
			{
				get_data().view_cards = 5;
			}
			else if (get_data().is_vaccant)
			{
				//检测点击地图
				if (hit.x > gra_size::map_start_x && hit.x < gra_size::map_end_x
					&& hit.y > gra_size::map_start_y && hit.y < gra_size::map_end_y)
				{
					bool is_block = true;
					for (int i = 0; i < 11; ++i)
					{
						if (hit.x - gra_size::map_start_x > 60 + 85 * i && hit.x - gra_size::map_start_x < 85 + 85 * i)
						{
							is_block = false;
							break;
						}
					}
					for (int i = 0; i < 4; ++i)
					{
						if (hit.y - gra_size::map_start_y > 60 + 85 * i && hit.y - gra_size::map_start_y < 85 + 85 * i)
						{
							is_block = false;
							break;
						}
					}
					if (is_block)
					{
						size_t x = (hit.x - gra_size::map_start_x) / (gra_size::map_block_size + gra_size::map_closure);
						size_t y = (hit.y - gra_size::map_start_y) / (gra_size::map_block_size + gra_size::map_closure);
						cur_state->click_map_location(x, y);
					}
				}
				//检测点击食物
				else if (hit.x > gra_size::food_pic_x && hit.x < gra_size::food_pic_x + 90
					&& hit.y > gra_size::food_pic_y && hit.y < gra_size::food_pic_y + 90)
				{
					if (get_data().food > 0 && get_data().player_data.current_hp < get_data().player_data.max_hp)
					{
						get_data().food--;
						get_data().player_data.current_hp += 3;
						if (get_data().player_data.current_hp >= get_data().player_data.max_hp)
							get_data().player_data.current_hp = get_data().player_data.max_hp;
					}
				}
			}//点击card_deck等
			else
			{
				//检测点击选项
				if (hit.x > gra_size::card_x + gra_size::card_starting_pos && hit.x < gra_size::card_x + gra_size::card_starting_pos + gra_size::card_rx
					&& hit.y > gra_size::card_y && hit.y < gra_size::card_dy)
				{
					size_t pos = (hit.x - gra_size::card_closure - gra_size::card_starting_pos) / (gra_size::card_width + gra_size::card_closure);
					if (pos + get_data().current_select_page * MAX_CARDS_IN_HAND < get_data().choice_list.size())
					{
						cur_state->click_an_option(pos);
					}
				}
				//检测点击左箭头
				else if (hit.x > gra_size::left_arrow_x && hit.x < gra_size::left_arrow_x + 100
					&& hit.y > gra_size::left_arrow_y && hit.y < gra_size::left_arrow_y + 100)
				{
					cur_state->click_left_arrow();
				}
				//检测点击右箭头
				else if (hit.x > gra_size::right_arrow_x && hit.x < gra_size::right_arrow_x + 100
					&& hit.y > gra_size::right_arrow_y && hit.y < gra_size::right_arrow_y + 100)
				{
					cur_state->click_right_arrow();
				}
				else if (hit.x > gra_size::next_x && hit.x < gra_size::next_x + 200
					&& hit.y > gra_size::next_y && hit.y < gra_size::next_y + 100)
				{
					if (get_data().event_is_not_mandetory)
					{
						cur_state->click_next();
					}
				}
			}
			Sleep(100);
			FlushMouseMsgBuffer();
		}
	}
}

data_sys & explore_context::get_data()
{
	return i_s->data;
}

data_sys & battle_context::get_data()
{
	return i_s->data;
}

interacting_sys::interacting_sys(data_sys & d) :data(d),
present_battle_context(new battle_context(this)), present_explore_context(new explore_context(this))
{
}

void interacting_sys::move_player(int x, int y)
{
	set_map_location(data.player_location.first, data.player_location.second, map_mark_type::VISITED);
	data.map_marks[x][y] = map_mark_type::PLAYER;
	data.player_location = make_pair(x, y);
}

void interacting_sys::set_map_location(int x, int y, int mark_type)
{
	data.map_marks[x][y] = mark_type;
}

void interacting_sys::update()
{
	if (data.b_to_i_pipe)
	{
		if (data.b_to_i_pipe.type == interact_action_type::BATTLE_TO_VACCANT)
		{
			present_battle_context->change_to_vaccant_state();
		}
		else
		{
			present_battle_context->change_to_select_state(data.b_to_i_pipe);
		}
		data.b_to_i_pipe.clear();
	}
	else if (data.e_to_i_pipe)
	{
		if (data.e_to_i_pipe.type == interact_action_type::EXPLORE_TO_SELECT)
		{
			present_explore_context->change_to_select_state(data.e_to_i_pipe.value);
		}
		else
		{
			present_explore_context->change_to_vaccant_state();
		}
		data.e_to_i_pipe.clear();
	}
	if (data.is_battle)
	{
		present_battle_context->read_input();
	}
	else
	{
		present_explore_context->read_input();
	}
}

b_state::b_state(battle_context * b_c)
	:ctx(b_c)
{

}

data_sys & b_state::get_data()
{
	return ctx->i_s->data;
}

void b_state::send_to_battle_sys(info_to_battle_sys t)
{
	get_data().i_to_b_pipe = t;
}

b_vaccant_state::b_vaccant_state(battle_context * b_c)
	:b_state(b_c)
{

}

void b_vaccant_state::click_a_card(size_t card_pos)
{
	if (card_pos < get_data().cards_in_hand.size() && get_data().player_data.current_ap >= get_data().cards_in_hand[card_pos].cost)
	{
		get_data().render_pipe.push(r_action(render_functions::SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
		ctx->set_state(new b_confirm_state(ctx, card_pos, get_data().cards_in_hand[card_pos].cost));
	}
}

void b_vaccant_state::click_an_enemy(size_t enemy_No)
{
	//nothing happens
}

void b_vaccant_state::click_confirm()
{
	//nothing happens
}

void b_vaccant_state::click_cancel()
{
	//nothing happens
}

void b_vaccant_state::click_turn_end()
{
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::TURN_END)));
	ctx->set_state(new b_lock_state(ctx));
}

b_confirm_state::b_confirm_state(battle_context * b_c, size_t card_pos, std::size_t c)
	:b_state(b_c), selected_card(card_pos), cost(c), require_target(false)
{
	if (get_data().cards_in_hand[card_pos].require_target)
	{
		require_target = true;
	}
}

void b_confirm_state::click_a_card(size_t card_pos)
{
	if (card_pos == selected_card)
	{
		get_data().render_pipe.push(r_action(render_functions::DE_SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
		ctx->set_state(new b_vaccant_state(ctx));
	}
	else if (get_data().cards_in_hand.size() > card_pos &&
		get_data().player_data.current_ap >= get_data().cards_in_hand[card_pos].cost)
	{
		get_data().render_pipe.push(r_action(render_functions::SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
		get_data().render_pipe.push(r_action(render_functions::DE_SELECT_A_CARD, MEANINGLESS_VALUE, selected_card));
		ctx->set_state(new b_confirm_state(ctx, card_pos, get_data().cards_in_hand[card_pos].cost));
	}
	else
	{
		get_data().render_pipe.push(r_action(render_functions::DE_SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
		ctx->set_state(new b_vaccant_state(ctx));
	}
}

void b_confirm_state::click_an_enemy(size_t enemy_pos)
{
	if (require_target)
	{
		game_entity* target;
		get_data().render_pipe.push(r_action(render_functions::IMMEDIATE_DE_SELECT, MEANINGLESS_VALUE, selected_card));
		if (get_data().enemies_data[enemy_pos].is_alive())
		{
			target = &get_data().enemies_data[enemy_pos];
			info_to_battle_sys temp;
			card tcard = get_data().cards_in_hand[selected_card];
			get_data().b->send_message(action(battle_action_type::USE_A_CARD,
				get_data().cards_in_hand[selected_card].card_type, selected_card));
			temp.append(tcard.use_card(get_data()));
			for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
			{
				i->caller = &get_data().player_data;
				if (i->listener == &get_data().select_one_enemy)
				{
					i->listener = target;
				}
			}
			for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
			{
				if (i->listener == &get_data().all_enemies)
				{
					auto temp_action = *i;
					i = temp.action_set.erase(i);
					for (size_t j = 0; j < get_data().enemies_data.size(); ++j)
					{
						if (get_data().enemies_data[j].is_alive())
						{
							temp_action.listener = &get_data().enemies_data[j];
							i = temp.action_set.insert(i, temp_action);
							//++i;
						}
					}
				}
			}
			send_to_battle_sys(temp);
			get_data().player_data.current_ap -= cost;
			ctx->set_state(new b_vaccant_state(ctx));
		}
		else
		{
			get_data().render_pipe.push(r_action(render_functions::DE_SELECT_A_CARD, MEANINGLESS_VALUE, selected_card));
			ctx->set_state(new b_vaccant_state(ctx));
		}
	}
}

void b_confirm_state::click_confirm()
{
	if (!require_target)
	{
		info_to_battle_sys temp;
		card tcard = get_data().cards_in_hand[selected_card];
		get_data().b->send_message(action(battle_action_type::USE_A_CARD,
			get_data().cards_in_hand[selected_card].card_type, selected_card));

		temp.append(tcard.use_card(get_data()));
		for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
		{
			//可能要改成直接传all_enemies
			if (i->listener == &get_data().all_enemies)
			{
				auto temp_action = *i;
				i = temp.action_set.erase(i);
				for (size_t j = 0; j < get_data().enemies_data.size(); ++j)
				{
					if (get_data().enemies_data[j].is_alive())
					{
						temp_action.listener = &get_data().enemies_data[j];
						i = temp.action_set.insert(i, temp_action);
						//++i;
					}
				}
			}
		}
		send_to_battle_sys(temp);
		get_data().render_pipe.push(r_action(render_functions::IMMEDIATE_DE_SELECT, MEANINGLESS_VALUE, selected_card));
		get_data().player_data.current_ap -= cost;
		ctx->set_state(new b_vaccant_state(ctx));
	}
}

void b_confirm_state::click_cancel()
{
	for (int i = 0; i < MAX_CARDS_IN_HAND; ++i)
	{
		get_data().render_pipe.push(info_to_render_sys(r_action(render_functions::IMMEDIATE_DE_SELECT, MEANINGLESS_VALUE, i)));
	}
	ctx->set_state(new b_vaccant_state(ctx));
}

void b_confirm_state::click_turn_end()
{
	send_to_battle_sys(info_to_battle_sys(action(battle_action_type::TURN_END)));
	ctx->set_state(new b_lock_state(ctx));
}

b_lock_state::b_lock_state(battle_context * b_c)
	:b_state(b_c)
{
}

void b_lock_state::click_a_card(size_t card_pos)
{
	//nothing happens
}

void b_lock_state::click_an_enemy(size_t card_pos)
{
	//nothing happens
}

void b_lock_state::click_confirm()
{
	//nothing happens
}

void b_lock_state::click_cancel()
{
	//nothing happens
}

void b_lock_state::click_turn_end()
{
	//nothing happens
}

b_select_state::b_select_state(battle_context * b_c, size_t num, size_t ttype, bool mdy)
	:b_state(b_c), max(num), type(ttype), is_mandatory(mdy)
{
}


void b_select_state::click_a_card(std::size_t card_pos)
{
	bool is_selected = 0;
	for (auto i = selected_cards.begin(); i != selected_cards.end(); ++i)
	{
		if (*i == card_pos)
		{
			get_data().render_pipe.push(r_action(render_functions::DE_SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
			selected_cards.erase(i);
			return;
		}
	}
	if (selected_cards.size() == max)return;
	selected_cards.push_back(card_pos);
	get_data().render_pipe.push(r_action(render_functions::SELECT_A_CARD, MEANINGLESS_VALUE, card_pos));
}

void b_select_state::click_an_enemy(std::size_t)
{
	//nothing happens
}

void b_select_state::click_confirm()
{
	info_to_battle_sys t;
	for (auto& i : selected_cards)
	{
		t.append(action(type + TYPE_TO_P_TYPE, nullptr, &get_data().player_data, get_data().cards_in_hand[i].card_type, i));
	}
	send_to_battle_sys(t);
	ctx->set_state(new b_vaccant_state(ctx));
}

void b_select_state::click_cancel()
{
	//nothing happens
}

void b_select_state::click_turn_end()
{
	//nothing happened
}

data_sys & e_state::get_data()
{
	return ctx->i_s->data;
}

void e_state::send_to_explore_sys(info_to_explore_sys t)
{
	get_data().i_to_e_pipe = t;
}

e_vaccant_state::e_vaccant_state(explore_context * e_c)
	:e_state(e_c)
{
}

void e_vaccant_state::click_an_option(size_t option)
{
	//nothing happens
}

void e_vaccant_state::click_next()
{
	//nothing happens
}

void e_vaccant_state::click_left_arrow()
{
	//nothing happens
}

void e_vaccant_state::click_right_arrow()
{
	//nothing happens
}

void e_vaccant_state::click_map_location(std::size_t x, std::size_t y)
{
	int p_x = get_data().player_location.first;
	int p_y = get_data().player_location.second;
	if ((x == p_x + 1 && y == p_y) || (x == p_x - 1 && y == p_y) || (x == p_x && y == p_y + 1) || (x == p_x && y == p_y - 1))
	{
		int mark = get_data().map_marks[x][y];
		switch (mark)
		{
		case map_mark_type::EMPTY:
			break;
		case map_mark_type::VISITED:
			ctx->i_s->move_player(x, y);
			break;
		default://no matter the place is known or not
			ctx->i_s->move_player(x, y);
			get_data().i_to_e_pipe = info_to_explore_sys(e_action(explore_action_type::ENCOUNTER_EVENT
				, MEANINGLESS_VALUE, get_data().explore_map[x][y], -1));
			break;
		}
	}
}

e_state::e_state(explore_context *tcontext)
	:ctx(tcontext)
{
}

e_select_state::e_select_state(explore_context * e_c, std::size_t tmax)
	: e_state(e_c), max_selection(tmax), current(0)
{
}

void e_select_state::click_an_option(std::size_t pos)
{
	info_to_explore_sys temp(get_data().choice_list[pos + MAX_CARDS_IN_HAND * get_data().current_select_page]);
	get_data().choice_list.erase(get_data().choice_list.begin() + pos + MAX_CARDS_IN_HAND * get_data().current_select_page);
	if (get_data().choice_list.size() == MAX_CARDS_IN_HAND * get_data().current_select_page && get_data().current_select_page != 0)
	{
		get_data().current_select_page -= 1;
	}
	current++;
	if (current == max_selection && get_data().next_event_id != 0)
	{
		temp.action_set.push_back(e_action(explore_action_type::ENCOUNTER_EVENT, MEANINGLESS_VALUE,
			static_cast<size_t>(get_data().next_event_id), get_data().text_to_be_displayed, get_data().map_text));
	}
	get_data().i_to_e_pipe = temp;
}

void e_select_state::click_next()
{
	get_data().i_to_e_pipe = info_to_explore_sys(e_action(explore_action_type::ENCOUNTER_EVENT, MEANINGLESS_VALUE, get_data().next_event_id));
}

void e_select_state::click_left_arrow()
{
	if (get_data().current_select_page > 0)
	{
		get_data().current_select_page -= 1;
	}
}

void e_select_state::click_right_arrow()
{
	if (get_data().current_select_page < get_data().choice_list.size() / MAX_CARDS_IN_HAND)
	{
		get_data().current_select_page += 1;
	}
}

void e_select_state::click_map_location(std::size_t x, std::size_t y)
{
	//nothing happens
}

