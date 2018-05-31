#pragma once
#include "Room.h"
namespace game_framework {
#define RoomInterface_bg_x 20
#define RoomInterface_bg_y 20
#define RoomInterface_Increase_x 20
#define RoomInterface_Increase_y 20
#define RoomInterface_Decrease_x 20
#define RoomInterface_Decrease_y 20
#define RoomInterface_Right_x 20
#define RoomInterface_Right_y 20
#define RoomInterface_Left_x 20
#define RoomInterface_Left_y 20
	class RoomIterface
	{
	public:
		RoomIterface(Room **gameRoom);
		~RoomIterface();
		void Initial();
		void OnShow();
		void SetInterfaceShow(bool flag);
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