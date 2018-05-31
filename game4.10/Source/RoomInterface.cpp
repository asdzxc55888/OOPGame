#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RoomInterface.h"
#include "MonsterDataBoard.h"
namespace game_framework {
	RoomInterface::RoomInterface(Room **_gameRoom)
	{
		gameRoom = _gameRoom;
		Initial();
	}
	RoomInterface::~RoomInterface()
	{
	}
	void RoomInterface::Initial()
	{
		bg.LoadBitmap("Bitmaps\\gameRun\\Room_interface.bmp", RGB(255, 255, 255));
		Increase_btn.LoadBitmap("Bitmaps\\gameRun\\increase_button.bmp", RGB(255, 255, 255));
		Decrease_btn.LoadBitmap("Bitmaps\\gameRun\\decrease_button.bmp", RGB(255, 255, 255));
		Right_btn.LoadBitmap("Bitmaps\\gameRun\\right_button.bmp", RGB(255, 255, 255));
		Left_btn.LoadBitmap("Bitmaps\\gameRun\\left_button.bmp", RGB(255, 255, 255));
		bg.SetTopLeft(RoomInterface_bg_x, RoomInterface_bg_y);
		Increase_btn.SetTopLeft(RoomInterface_Increase_x,RoomInterface_Increase_y);
		Decrease_btn.SetTopLeft(RoomInterface_Decrease_x, RoomInterface_Decrease_y);
		Right_btn.SetTopLeft(RoomInterface_Right_x,RoomInterface_Right_y);
		Left_btn.SetTopLeft(RoomInterface_Left_x, RoomInterface_Left_y);
		isMouseOn = false;
		isOnShow = false;
		monsterSelector = 0;
		RoomSelector = 0;
	}
	void RoomInterface::OnShow()
	{
		if (isOnShow) 
		{
			bg.ShowBitmap();
			Increase_btn.ShowBitmap();
			Decrease_btn.ShowBitmap();
			Right_btn.ShowBitmap();
			Left_btn.ShowBitmap();
		}
	}
	void RoomInterface::OnMove()
	{
		if (gameRoom[RoomSelector]->GetLiveMonster(monsterSelector) != NULL) {
			MonsterBoard = gameRoom[RoomSelector]->GetLiveMonster(monsterSelector)->GetMonsterDataBoard();
		}
		MonsterBoard.SetPoint(500, 250);
	}
	void RoomInterface::SetInterfaceShow(bool flag)
	{
		isOnShow = flag;
	}
	void RoomInterface::SetRoomSelector(int index)
	{
		RoomSelector = index;
	}
	void RoomInterface::SetMonsterSelector(int index)
	{
		monsterSelector = index;
	}
	bool RoomInterface::IsMouseOn(CPoint point)
	{
		return false;
	}
}