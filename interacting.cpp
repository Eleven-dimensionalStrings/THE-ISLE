#include <random>
#include <ctime>
#include <graphics.h>
#include "interacting.h"
using namespace std;
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
			if (hit.x > gra_size::card_x && hit.x < gra_size::card_x + gra_size::card_rx
				&& hit.y>gra_size::card_y && hit.y < gra_size::card_dy)
			{
				size_t pos = (hit.x - gra_size::card_closure) / (gra_size::card_width + gra_size::card_closure);
				if (pos <= get_data().cards_in_hand.size())
				{
					cur_state->click_a_card(pos);
					//cur_state->click_confirm();
				}
			}
			//检查点击敌人
			else if (hit.x > gra_size::enemy_x && hit.x<gra_size::enemy_x + gra_size::enemy_width*gra_size::max_enemies
				&& hit.y>gra_size::enemy_y && hit.y < gra_size::enemy_y + 200)//需要改为敌人高度
			{
				size_t pos = (hit.x - gra_size::enemy_x) / gra_size::enemy_width;
				if (pos <= get_data().enemies_data.size())
				{
					cur_state->click_an_enemy(pos);
				}
			}
			//confirm, to revice the value
			else if (hit.x > gra_size::confirm_button_x && hit.y > gra_size::confirm_button_y
				&& hit.x < gra_size::confirm_button_x + 100 && hit.y < gra_size::confirm_button_y + 50)
			{
				cur_state->click_confirm();
			}

		}
		//FlushMouseMsgBuffer();
	}
	//test_read();
}

void battle_context::change_to_select_state(info_battle_to_interacting t)
{
	set_state(new b_select_state(this, t.num, t.type, t.is_m));
}

explore_context::explore_context(interacting_sys* i_s)
	: context(i_s), cur_state(new e_vaccant_state(this))
{

}

explore_context::explore_context(interacting_sys* i_s, e_state * pstate)
	: context(i_s), cur_state(pstate)
{

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
	//switch
	//cur_state->xxxfunction
}

data_sys & battle_context::get_data()
{
	return i_s->data;
}

void battle_context::test_read()
{
	size_t card_pos, target_pos;
	cin >> card_pos;
	set_state(new b_confirm_state(this, card_pos));
	if (get_data().cards_in_hand[card_pos].require_target)
	{
		cin >> target_pos;
		cur_state->click_an_enemy(target_pos);
		return;
	}
	cur_state->click_confirm();
}

interacting_sys::interacting_sys(data_sys & d) :data(d),
present_battle_context(new battle_context(this)), present_explore_context(new explore_context(this))
{
}


info_to_battle_sys interacting_sys::play_a_card(size_t card_pos, game_entity* target)
{
	info_to_battle_sys result(action(battle_action_type::USE_A_CARD, &data.player_data, target,
		data.cards_in_hand[card_pos].card_type, card_pos));
	auto ef = data.card_effect(data.cards_in_hand[card_pos].card_id);
	result.append(ef);
	for (auto& i : result.action_set)
		i.caller = &data.player_data;
	return result;
}

void interacting_sys::move_player(int x, int y)
{
	data.map_marks[data.player_location.first][data.player_location.second] = map_mark_type::VISITED;
	data.map_marks[x][y] = map_mark_type::PLAYER;
	data.player_location = make_pair(x, y);
}

void interacting_sys::set_map_location(int x, int y, int mark_type)
{
	data.map_marks[x][y] = mark_type;
	//tell the renderer to reveal the map
}

void interacting_sys::reveal_map_location(int x, int y)
{
	//call the renderer to reveal the map
}

void interacting_sys::encounter_event(std::size_t event_card_no)
{
	event_card temp = data.event_effect.find(event_card_no)->second;
	present_explore_context->set_state(&e_select_state(present_explore_context, temp.root));
}

void interacting_sys::update()
{
	if (data.b_to_i_pipe)
	{
		present_battle_context->change_to_select_state(data.b_to_i_pipe);
		data.b_to_i_pipe.clear();
		return;
	}
	else if (data.e_to_i_pipe)
	{
		//TODO
		data.e_to_i_pipe.clear();
		return;
	}
	present_battle_context->read_input();
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
	get_data().draw_select_card[card_pos] = 1;
	ctx->set_state(new b_confirm_state(ctx, card_pos));
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

b_confirm_state::b_confirm_state(battle_context * b_c, size_t card_pos)
	:b_state(b_c), selected_card(card_pos), require_target(false)
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
		get_data().draw_select_card[selected_card] = 0;
		ctx->set_state(new b_vaccant_state(ctx));
	}
	else
	{
		get_data().draw_select_card[card_pos] = 1;
		get_data().draw_select_card[selected_card] = 0;
		ctx->set_state(new b_confirm_state(ctx, card_pos));
	}
}

void b_confirm_state::click_an_enemy(size_t enemy_pos)
{
	if (require_target)
	{
		game_entity* target;
		if (get_data().enemies_data[enemy_pos].is_alive())
		{
			target = &get_data().enemies_data[enemy_pos];
			info_to_battle_sys temp(action(battle_action_type::USE_A_CARD, get_data().cards_in_hand[selected_card].card_type, selected_card));
			temp.append(get_data().cards_in_hand[selected_card].use_card(get_data()));
			for (auto i = temp.action_set.begin(); i != temp.action_set.end(); ++i)
			{
				i->caller = &get_data().player_data;
				if (i->listener == &get_data().select_one_enemy)
				{
					i->listener = target;
				}
			}
			send_to_battle_sys(temp);
			ctx->set_state(new b_vaccant_state(ctx));
		}
		else
		{
			ctx->set_state(new b_vaccant_state(ctx));
		}
		get_data().draw_select_card[selected_card] = 0;
	}
}

void b_confirm_state::click_confirm()
{
	if (!require_target)
	{
		info_to_battle_sys temp(action(battle_action_type::USE_A_CARD, get_data().cards_in_hand[selected_card].card_type, selected_card));
		temp.append(get_data().cards_in_hand[selected_card].use_card(get_data()));
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
		get_data().draw_select_card[selected_card] = 0;
	}
}

void b_confirm_state::click_cancel()
{
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
			get_data().draw_select_card[card_pos] = 0;
			selected_cards.erase(i);
			return;
		}
	}
	if (selected_cards.size() == max)return;
	selected_cards.push_back(card_pos);
	get_data().draw_select_card[card_pos] = 1;
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
		t.append(action(type + TYPE_TO_P_TYPE, 0, i));
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

void e_vaccant_state::click_up_arrow()
{
	if (get_data().player_location.second == 5)
	{
		return;
	}
	int mark = get_data().map_marks[get_data().player_location.first][get_data().player_location.second + 1];
	switch (mark)
	{
	case map_mark_type::EMPTY:
		break;
	case map_mark_type::VISITED:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second + 1);
		break;
	case map_mark_type::KNOWN:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second + 1);
		ctx->i_s->set_map_location(get_data().player_location.first, get_data().player_location.second + 1, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
		break;
	case map_mark_type::UNKNOWN:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second + 1);
		ctx->i_s->set_map_location(get_data().player_location.first, get_data().player_location.second + 1, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
	default:
		break;
	}
}

void e_vaccant_state::click_down_arrow()
{
	if (get_data().player_location.second == 0)
	{
		return;
	}
	int mark = get_data().map_marks[get_data().player_location.first][get_data().player_location.second - 1];
	switch (mark)
	{
	case map_mark_type::EMPTY:
		break;
	case map_mark_type::VISITED:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second - 1);
		break;
	case map_mark_type::KNOWN:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second - 1);
		ctx->i_s->set_map_location(get_data().player_location.first, get_data().player_location.second - 1, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
		break;
	case map_mark_type::UNKNOWN:
		ctx->i_s->move_player(get_data().player_location.first, get_data().player_location.second - 1);
		ctx->i_s->set_map_location(get_data().player_location.first, get_data().player_location.second - 1, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
	default:
		break;
	}
}

void e_vaccant_state::click_left_arrow()
{
	if (get_data().player_location.first == 0)
	{
		return;
	}
	int mark = get_data().map_marks[get_data().player_location.first - 1][get_data().player_location.second];
	switch (mark)
	{
	case map_mark_type::EMPTY:
		break;
	case map_mark_type::VISITED:
		ctx->i_s->move_player(get_data().player_location.first - 1, get_data().player_location.second);
		break;
	case map_mark_type::KNOWN:
		ctx->i_s->move_player(get_data().player_location.first - 1, get_data().player_location.second);
		ctx->i_s->set_map_location(get_data().player_location.first - 1, get_data().player_location.second, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
		break;
	case map_mark_type::UNKNOWN:
		ctx->i_s->move_player(get_data().player_location.first - 1, get_data().player_location.second);
		ctx->i_s->set_map_location(get_data().player_location.first - 1, get_data().player_location.second, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
	default:
		break;
	}
}

void e_vaccant_state::click_right_arrow()
{
	if (get_data().player_location.first == 5)
	{
		return;
	}
	int mark = get_data().map_marks[get_data().player_location.first + 1][get_data().player_location.second];
	switch (mark)
	{
	case map_mark_type::EMPTY:
		break;
	case map_mark_type::VISITED:
		ctx->i_s->move_player(get_data().player_location.first + 1, get_data().player_location.second);
		break;
	case map_mark_type::KNOWN:
		ctx->i_s->move_player(get_data().player_location.first + 1, get_data().player_location.second);
		ctx->i_s->set_map_location(get_data().player_location.first + 1, get_data().player_location.second, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
		break;
	case map_mark_type::UNKNOWN:
		ctx->i_s->move_player(get_data().player_location.first + 1, get_data().player_location.second);
		ctx->i_s->set_map_location(get_data().player_location.first + 1, get_data().player_location.second, map_mark_type::VISITED);
		//ctx->i_s->encounter_event(get_data().explore_map[get_data().player_location.first][get_data().player_location.second]);
	default:
		break;
	}
}

e_state::e_state(explore_context *tcontext)
	:ctx(tcontext)
{
}

e_select_state::e_select_state(explore_context * e_c, event_e e_e)
	: e_state(e_c), current_phase(e_e)
{
	switch (current_phase.type)
	{
	case event_type::SELECT:
		get_data().choice_list.clear();
		get_data().choice_list = e_e.selection;
		break;
	case event_type::SELECT_NEXT_EVENT:
		get_data().choice_list.clear();
		get_data().choice_list = e_e.selection;
		break;
	case event_type::BATTLE:
		get_data().i_to_e_pipe = info_to_explore_sys(e_action(explore_action_type::START_BATTLE, e_e.enemy_type));
		break;
	case event_type::REMOVE_CARDS:
		get_data().choice_list.clear();
		for (int i = 0; i < get_data().cards_pool.size(); i++)
		{
			get_data().choice_list.push_back(explore_selection(explore_action_type::REMOVE_CARD, i, get_data().cards_pool[i]));
		}
		break;
	case event_type::UPGRADE_CARDS:
		get_data().choice_list.clear();
		for (int i = 0; i < get_data().cards_pool.size(); i++)
		{
			if (get_data().cards_pool[i].upgrade_version_id != 0)
			{
				get_data().choice_list.push_back(explore_selection(explore_action_type::UPGRADE_CARD, i, get_data().cards_pool[i]));
			}
		}
		break;
	case event_type::CHANGE_CARDS:
		get_data().choice_list.clear();
		for (int i = 0; i < get_data().cards_pool.size(); i++)
		{
			get_data().choice_list.push_back(explore_selection(explore_action_type::CHANGE_CARD, i, get_data().cards_pool[i]));
		}
		break;
	case event_type::REMOVE_ARTIFACTS:
		get_data().choice_list.clear();
		for (int i = 0; i < get_data().artifacts.size(); i++)
		{
			get_data().choice_list.push_back(explore_selection(explore_action_type::REMOVE_ARTIFACT, i, get_data().artifacts[i]));
		}
		break;
	}
}

void e_select_state::click_an_option(std::size_t pos)
{
	explore_selection temp = get_data().choice_list[pos + 3 * get_data().current_select_page];
	get_data().i_to_e_pipe = info_to_explore_sys(e_action(temp));
	get_data().choice_list.erase(get_data().choice_list.begin() + pos + 3 * get_data().current_select_page, get_data().choice_list.begin() + pos + get_data().current_select_page + 1);
	if (get_data().choice_list.empty())
	{
		ctx->set_state(&e_select_state(ctx, current_phase.following_event[0]));
	}
	else if (get_data().choice_list.size() == 3 * get_data().current_select_page)
	{
		get_data().current_select_page -= 1;
	}
}

void e_select_state::click_next()
{
	if (!is_mandatory)
	{
		ctx->set_state(&e_select_state(ctx, current_phase.following_event[0]));
	}
}

void e_select_state::click_up_arrow()
{
	if (get_data().current_select_page > 0)
	{
		get_data().current_select_page -= 1;
	}
}

void e_select_state::click_down_arrow()
{
	if (get_data().current_select_page < get_data().choice_list.size() / 3)
	{
		get_data().current_select_page += 1;
	}
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
	if (get_data().current_select_page < get_data().choice_list.size() / 3)
	{
		get_data().current_select_page += 1;
	}
}

