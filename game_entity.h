#pragma once
#include "managers.h"
#include "message.h"
#include "cards.h"
#include "artifacts.h"
#include "buff.h"
#include "data_sys.h"

//the definition of base class game_entity

class game_entity : public message_dispatcher
{
public:
	virtual void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list) = 0;
	virtual info_to_battle_sys calling_action(action);
	virtual info_to_battle_sys performing_action(action);
	virtual info_to_battle_sys kill() = 0;
	bool is_alive();
	virtual info_to_battle_sys on_turn_begin() = 0;
	virtual info_to_battle_sys on_turn_end() = 0;

	data_sys& data;
	bool living_state; //ʵ��Ĵ��״̬��ʵ�����۴��״̬��ζ���ռ��ԭ�ȵ�λ��
	int max_hp;//�������ֵ
	int current_hp;//��ǰ����ֵ
	int max_ap; // ����ж���
	int current_ap;//��ǰ�ж���
	std::vector<card> cards_deck;//ս��ʱ�ƿ�
	std::vector<card> cards_grave;//���ƶ�
	std::vector<card> cards_in_hand;//����
	std::vector<card> cards_removed;//������
	std::vector<card> cards_equiped;//װ����
	std::vector<buff> buff_pool;//buff��
	virtual info_to_battle_sys create_message_to_battle_sys() = 0;
};


//definition of the player class


class player : public game_entity
{
public:
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list);
	info_to_battle_sys kill();
	info_to_battle_sys on_turn_begin();
	info_to_battle_sys on_turn_end();
	std::size_t gold;
	std::size_t food;

	info_to_battle_sys create_message_to_battle_sys();
};


//definition of the enemy class


class enemy : public game_entity
{
public:
	void initiate(std::vector<card>&card_pool, std::vector<artifact>&artifact_list);
	virtual info_to_battle_sys kill();
	info_to_battle_sys on_turn_begin();
	info_to_battle_sys on_turn_end();

	info_to_battle_sys create_message_to_battle_sys();
};