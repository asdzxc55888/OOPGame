#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
namespace game_framework {
	void ChoseEvent(GameEvent_number event)
	{
		switch (event)
		{
		case game_framework::MonsterGohome_eventNumber:
			//MonsterGohome_event(Room *_room);
			break;
		default:
			break;
		}
	}
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_Width) //怪物找房
	{
		if (Moving(_monster,TaskBoard_x+20,0)) {
			(*_monster)->SetMovingType(Back);
			(*_monster)->SetMonsterState(findHouse);
		}
		
	}
	void MonsterlivingHouse_event(Room *_room,Monster **_monster) {
		_room->SetMonsterlivingRoom(_monster);
		MonsterGohome_event(_room);
	}
	void MonsterGohome_event(Room *_room)
	{
		_room->LetMonsterGohome();
	}
	void MonsterBeingClick(Monster **_monster,int room_size,Room **gameroom)
	{
		Monster_state nowState=(*_monster)->GetMonsterState();
		switch (nowState)
		{
		case game_framework::wolking:

			break;
		case game_framework::findHouse:                   //同意怪物住進防屋
			for (int i = 0; i < room_size; i++) {
				if (!(gameroom)[i]->GetIsMonsterLiving()) {  //沒怪物住的話就分配到那間房
					MonsterlivingHouse_event((gameroom)[i], _monster);
					
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	bool MonsterLeave(Monster ** _monster) //已經離開回傳true
	{
		if (Moving(_monster, -100, 0)) {
			DeleteMonster_event(_monster);
			return true;
		}
		return false;
	}
	bool Moving(Monster **_monster, int x, int floor)
	{
		if ((*_monster)->GetFloor() == floor) {
			if ((*_monster)->GetX() > x+10) {
				(*_monster)->SetMovingLeft(true);
			}
			else if ((*_monster)->GetX() <= x-10) {
				(*_monster)->SetMovingRight(true);
			}
			else {
				(*_monster)->SetMovingLeft(false);
				(*_monster)->SetMovingRight(false);
				return true;
			}
		}
		return false;
	}
	void CreateMonster_event(Monster **_monster) {
			int result = 0;
			result = rand() % 1000;
			if (result < 20) {
				(*_monster) = new Monster();
				(*_monster)->LoadBitmap((*_monster)->GetMonsterType());
				(*_monster)->SetMonsterIsExist(true);
				(*_monster)->SetMonsterState(nothing);
			}
		
	}
	void DeleteMonster_event(Monster ** _monster)
	{
		if ((*_monster) != NULL) {
			delete *_monster;
			(*_monster) = NULL;
		}
	}
}