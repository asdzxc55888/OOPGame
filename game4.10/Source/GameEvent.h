#pragma once
#include "Room.h"
#include "Warrior.h"
#include "obstacle.h"
namespace game_framework {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetObstacle(Room** gameRoom,Warrior** _warriors,Obstacle *obs, int roomSize);
	////////////////////////////////////////////////////////////////////////////怪物事件////////////////////////////////////////////////////////
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_y); //怪物看屋事件 
	void MonsterGohome_event(Room *_room);                                     //怪物進房事件，等同怪物住屋事件
	void MonsterBeingClick(Monster **_monster, int room_size, Room **gameroom); //怪物被點擊事件
	bool MonsterLeave(Monster **_monster);                                      //怪物離開，直接消失的那種離開
	bool Moving(Monster **_monster, int x, int floor,Obstacle obs);                          //怪物移動
	bool MovingLR(Monster **_monster, int x);
	void AttackWarrior(Monster *monster,Warrior **_warrior);
	bool HitWarrior(Monster *_monster,Warrior *_warrior);          //判斷有無碰到勇者
	void CreateMonster_event(Monster **_monster);
	////////////////////////////////////////////////////////////////////////////勇者事件//////////////////////////////////////////////////////////
	bool Moving(Warrior **_warrior, int x, int floor, Obstacle obs);
	void CreateWarrior_event(Warrior **_warrior, warrior_type type);
	void DeleteWarrior_event(Warrior **_warrior);
	bool HitMonster(Warrior *_warrior,Monster *_monster);
	/////////////////////////////////////////////////////////////////////////////////戰鬥事件/////////////////////////////////////////////////////
	void WarriorAttack_event(Warrior *_warrior, Monster **target, Obstacle obs);
	void MonsterAttack_event(Monster *_monster, Warrior ** target, Obstacle obs);
	Monster* findMonsterTarget(Warrior *_warrior, Room **gameroom,int room_size);
	Warrior* findWarriorTarget(Monster *_monster, Warrior **_warrior);
	void BattleEnd(Room **gameRoom, int roomsize);
	void BattleTest1(Warrior **_warrior, bool &isIntoBattle, Room **gameRoom);
	///////////////////////////////////////////////////////////////////時間控制//////////////////////////////////////////////////////////////////
	void timeControl(int *timelevel, bool  isSpeedControlOn[3]);

}