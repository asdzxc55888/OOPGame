#pragma once
#include "Room.h"
namespace game_framework {
	enum GameEvent_number {
		MonsterGohome_eventNumber
	};
	void ChoseEvent(GameEvent_number event);
	void MonsterGohome_event(Room *_room);
	Monster* CreateMonster_event(Monster *_monster, int *monsterNumber);
}