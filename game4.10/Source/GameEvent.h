#pragma once
#include "Room.h"
#include "Warrior.h"
namespace game_framework {
	enum GameEvent_number {
		MonsterGohome_eventNumber
	};
	////////////////////////////////////////////////////////////////////////////�Ǫ��ƥ�////////////////////////////////////////////////////////
	void ChoseEvent(GameEvent_number event);
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_y); //�Ǫ��ݫΨƥ� 
	void MonsterGohome_event(Room *_room);                                     //�Ǫ��i�Шƥ�A���P�Ǫ���Ψƥ�
	void MonsterBeingClick(Monster **_monster, int room_size, Room **gameroom); //�Ǫ��Q�I���ƥ�
	bool MonsterLeave(Monster **_monster);                                      //�Ǫ����}�A�����������������}
	bool Moving(Monster **_monster, int x, int floor);                          //�Ǫ�����
	void AttackWarrior(Monster *monster,Warrior *_warrior);
	bool HitWarrior(Monster *_monster,Warrior *_warrior);          //�P�_���L�I��i��
	void CreateMonster_event(Monster **_monster);
	void DeleteMonster_event(Monster **_monster);
	//bool HitMonster(Monster _monster);
	//bool HitWarrior(Warrior _warrior);
	////////////////////////////////////////////////////////////////////////////�i�̨ƥ�//////////////////////////////////////////////////////////
	bool Moving(Warrior **_warrior, int x, int floor);
	void CreateWarrior_event(Warrior **_warrior, warrior_type type);
	void AttackMonster(Warrior *_warrior,Monster *_monster);
	bool HitMonster(Warrior *_warrior,Monster *_monster);
	/////////////////////////////////////////////////////////////////////////////////�԰��ƥ�/////////////////////////////////////////////////////
	Monster* findMonsterTarget(Warrior *_warrior, Room **gameroom,int room_size);
	Warrior* findWarriorTarget(Monster *_monster, Warrior **_warrior);
	void WarriorAdAttack(Warrior *_warrior, Monster *_monster);
	void BattleTest1(Warrior **_warrior, bool &isIntoBattle, Room **gameRoom);

}