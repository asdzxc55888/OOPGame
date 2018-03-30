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
	void MonsterlivingHouse_event(Room *_room,Monster *_monster) {
		_room->SetMonsterlivingRoom(_monster);
		MonsterGohome_event(_room);
	}
	void MonsterGohome_event(Room *_room)
	{
		_room->LetMonsterGohome();
	}
	Monster* CreateMonster_event(Monster *_monster,int *monsterNumber) {
		if (*monsterNumber == 0) {
			int result = 0;
			result = rand() % 1000;
			if (result < 10) {
				_monster = new Monster("tentacle");
				_monster->LoadBitmap(_monster->GetMonsterType());
				_monster->SetMonsterIsExist(true);
				*monsterNumber = 1;
			}
		}
		return _monster;
	}
}