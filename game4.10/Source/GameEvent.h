#pragma once
#include "Room.h"
#include "Warrior.h"
#include "obstacle.h"
namespace game_framework {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetObstacle(Room** gameRoom,Warrior** _warriors,Obstacle *obs, int roomSize);
	////////////////////////////////////////////////////////////////////////////�Ǫ��ƥ�////////////////////////////////////////////////////////
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_y); //�Ǫ��ݫΨƥ� 
	void MonsterGohome_event(Room *_room,int monsterIndex);                                     //�Ǫ��i�Шƥ�A���P�Ǫ���Ψƥ�
	void MonsterBeingClick(Monster **_monster, int room_size, Room **gameroom); //�Ǫ��Q�I���ƥ�
	bool MonsterLeave(Monster **_monster);                                      //�Ǫ����}�A�����������������}
	bool Moving(Monster **_monster, int x, int floor,Obstacle obs);                          //�Ǫ�����
	bool MovingLR(Monster **_monster, int x);
	void AttackWarrior(Monster *monster,Warrior **_warrior);
	bool HitWarrior(Monster *_monster,Warrior *_warrior);          //�P�_���L�I��i��
	void CreateMonster_event(Monster **_monster);
	////////////////////////////////////////////////////////////////////////////�i�̨ƥ�//////////////////////////////////////////////////////////
	bool Moving(Warrior **_warrior, int x, int floor, Obstacle obs);
	void CreateWarrior_event(Warrior **_warrior, warrior_type type);
	void DeleteWarrior_event(Warrior **_warrior);
	bool HitMonster(Warrior *_warrior,Monster *_monster);
	/////////////////////////////////////////////////////////////////////////////////�԰��ƥ�/////////////////////////////////////////////////////
	void WarriorAttack_event(Warrior *_warrior, Monster **target, Obstacle obs);
	void MonsterAttack_event(Monster *_monster, Warrior ** target, Obstacle obs);
	void MonsterPositionFix(Room **gameRoom, Obstacle obs, int roomSize);        //�Ǫ���m�ץ�
	Monster* findMonsterTarget(Warrior *_warrior, Room **gameroom,int room_size);
	Warrior* findWarriorTarget(Monster *_monster, Warrior **_warrior);
	void BattleEnd(Room **gameRoom, int roomsize);
	void BattleTest1(Warrior **_warrior, bool &isIntoBattle, Room **gameRoom);
	///////////////////////////////////////////////////////////////////�ɶ�����//////////////////////////////////////////////////////////////////
	void timeControl(int *timelevel, bool  isSpeedControlOn[3]);
	//////////////////////////////////////////////////////////////////////�ʷR�ƥ�///////////////////////////////////////////////////
	void ComingMonsterFallInLoveEvent(Monster **_monster,Room **gameRoom ,int roomSize);             //���X�Ǫ��ʷR�ƥ�
	void MonsterMatingEvent(Room **gameRoom, int roomSize);    //�Ǫ���t�ƥ�
	void MonsterBorn(Room **gameRoom, int roomSize);  //�Ǫ��X��

}