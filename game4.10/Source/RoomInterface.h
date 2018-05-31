#pragma once
#include "Room.h"
namespace game_framework {
#define RoomInterface_bg_x 100
#define RoomInterface_bg_y 0
#define RoomInterface_Increase_x 425
#define RoomInterface_Increase_y 252
#define RoomInterface_Decrease_x 272
#define RoomInterface_Decrease_y 252
#define RoomInterface_Right_x 335
#define RoomInterface_Right_y 70
#define RoomInterface_Left_x 117
#define RoomInterface_Left_y 70
	class RoomInterface
	{
	public:
		RoomInterface(Room **gameRoom);
		~RoomInterface();
		void Initial();
		void OnShow();
		void OnMove();
		void SetInterfaceShow(bool flag);
		void SetRoomSelector(int index);
		void SetMonsterSelector(int index);
		bool IsMouseOn(CPoint point);
	private:
		int RoomSelector;
		int monsterSelector;
		bool isOnShow;
		bool isMouseOn;
		CMovingBitmap bg;     //�I����
		CMovingBitmap Increase_btn,Decrease_btn;     //�Я��վ����
		CMovingBitmap Right_btn, Left_btn;           //�ж���ܶs
		MonsterDataBoard MonsterBoard;               //�Ǫ������
		Room **gameRoom;
	};

}