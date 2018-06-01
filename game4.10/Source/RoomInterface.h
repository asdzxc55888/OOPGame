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
#define monsterBmp_x 280
#define monsterBmp_y 160
#define RentPercent_x 232
#define RentPercent_y 135
#define RentInt_x 460
#define RemtInt_y 260
	class RoomInterface
	{
	public:
		RoomInterface(Room **gameRoom);
		~RoomInterface();
		void Initial();
		void OnShow();
		void OnMove();
		void ShowRentBar();
		void SetInterfaceShow(bool flag);
		void SetRoomSelector(int index);
		void SetMonsterSelector(int index);
		int  GetRoomSelector();
		bool GetIsShow();
		bool IsMouseOn(CPoint point);
		bool IsMouseClick(CPoint point, int monsterIndex);
		bool IsMouseClick(CPoint point);
	private:
		void ResetRent();
		int  RoomSelector;
		int  monsterSelector;
		int  rentPercent;
		int  maxPercent;
		bool isOnShow;
		bool isMouseOn;
		bool isMouseOnBtn[4];
		CInteger *presentRent;
		CMovingBitmap bg;                            //�I����
		CMovingBitmap Increase_btn,Decrease_btn;     //�Я��վ����
		CMovingBitmap Right_btn, Left_btn;           //�ж���ܶs
		CMovingBitmap *monster[3];                   //�Ǫ���
		MonsterDataBoard *MonsterBoard;              //�Ǫ������
		Room **gameRoom;
	};

}