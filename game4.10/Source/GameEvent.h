#pragma once
#include "Room.h"

namespace game_framework {
	enum GameEvent_number {
		MonsterGohome_eventNumber
	};
	void ChoseEvent(GameEvent_number event);
	void MonsterFindHouse(Monster **_monster, int TaskBoard_x, int TaskBoard_y); //�Ǫ��ݫΨƥ� 
	void MonsterGohome_event(Room *_room);                                     //�Ǫ��i�Шƥ�A���P�Ǫ���Ψƥ�
	void MonsterBeingClick(Monster **_monster, int room_size, Room **gameroom); //�Ǫ��Q�I���ƥ�
	bool MonsterLeave(Monster **_monster);                                      //�Ǫ����}�A�����������������}
	bool Moving(Monster **_monster, int x, int floor);                          //�Ǫ�����
	void CreateMonster_event(Monster **_monster);
	void DeleteMonster_event(Monster **_monster);
}