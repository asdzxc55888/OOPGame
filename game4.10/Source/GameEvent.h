#pragma once
#include "Room.h"
#include "Warrior.h"
namespace game_framework {
	enum GameEvent_number {
		MonsterGohome_eventNumber
	};
	////////////////////////////////////////////////////////////////////////////怪物事件////////////////////////////////////////////////////////
	void ChoseEvent(GameEvent_number event);
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_y); //怪物看屋事件 
	void MonsterGohome_event(Room *_room);                                     //怪物進房事件，等同怪物住屋事件
	void MonsterBeingClick(Monster **_monster, int room_size, Room **gameroom); //怪物被點擊事件
	bool MonsterLeave(Monster **_monster);                                      //怪物離開，直接消失的那種離開
	bool Moving(Monster **_monster, int x, int floor);                          //怪物移動
	void CreateMonster_event(Monster **_monster);
	void DeleteMonster_event(Monster **_monster);
	////////////////////////////////////////////////////////////////////////////勇者事件//////////////////////////////////////////////////////////
	bool Moving(Warrior **_warrior, int x, int floor);
	void CreateWarrior_event(Warrior **_warrior, warrior_type type);
	/////////////////////////////////////////////////////////////////////////////////戰鬥事件/////////////////////////////////////////////////////
	void BattleTest1(Warrior **_warrior);
}