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
		for (int i = 0; i < 3; i++) {
			monster[i] = NULL;
		}
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
			if(gameRoom[RoomSelector]->GetLiveMonsterSize()>0 && isMouseOn)MonsterBoard->OnShow();
			for (int i = 0; i < 3; i++) {
				if (monster[i] != NULL)
				{
					monster[i]->ShowBitmap();
				}
			}
		}
	}
	void RoomInterface::OnMove()
	{

	}
	void RoomInterface::SetInterfaceShow(bool flag)
	{
		if (flag) {
			for (int i = 0; i < 3; i++) if (monster[i] != NULL) {
				delete monster[i];   //­«·sLOAD¹Ï
				monster[i] = NULL;
			}
			for (int i = 0; i < gameRoom[RoomSelector]->GetLiveMonsterSize(); i++)
			{
				monster[i] = new CMovingBitmap();
				Monster *_thisM=gameRoom[RoomSelector]->GetLiveMonster(i);
				string _monsterType = _thisM->GetMonsterType();
				_monsterType += ".bmp";
				if (_thisM->GetMonsterGender() == male) {
					_monsterType = "m_" + _monsterType;
				}
				else {
					_monsterType = "w_" + _monsterType;
				}
				if(_thisM->GetIsKid()) _monsterType = "child_" + _monsterType;
				_monsterType = "Bitmaps\\monster\\monster_" + _monsterType;
				char root[200] ;
				strcpy(root, _monsterType.c_str());
				monster[i]->LoadBitmap(root, RGB(255, 255, 255));
				monster[i]->SetTopLeft(monsterBmp_x + i * 60, monsterBmp_y);
			}

			if (gameRoom[RoomSelector]->GetLiveMonster(monsterSelector) != NULL) {
				MonsterBoard = gameRoom[RoomSelector]->GetLiveMonster(monsterSelector)->GetMonsterDataBoard();
				MonsterBoard->SetPoint(600, 250);
			}
		}
		else {
			if(gameRoom[RoomSelector]->GetLiveMonsterSize()>0)MonsterBoard->SetPoint(50, 50);
		}
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
	int RoomInterface::GetRoomSelector()
	{
		return RoomSelector;
	}
	bool RoomInterface::GetIsShow()
	{
		return isOnShow;
	}
	bool RoomInterface::IsMouseOn(CPoint point)
	{
		isMouseOn = false;
		for (int i = 0; i < gameRoom[RoomSelector]->GetLiveMonsterSize(); i++) {
			int y1 = monster[i]->Top();
			int y2 = y1 + monster[i]->Height();
			int x1 = monster[i]->Left();
			int x2 = x1 + monster[i]->Width();
			if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2) {
				MonsterBoard->SetPoint(50, 50);
				monsterSelector = i;
				MonsterBoard = gameRoom[RoomSelector]->GetLiveMonster(monsterSelector)->GetMonsterDataBoard();
				MonsterBoard->SetPoint(600, 250);
				isMouseOn = true;
			}
		}
		return false;
	}
	bool RoomInterface::IsMouseClick(CPoint point,int monsterIndex)
	{
		if (monster[monsterIndex] == NULL)return false;
		int y1 = monster[monsterIndex]->Top();
		int y2 = y1 + monster[monsterIndex]->Height();
		int x1 = monster[monsterIndex]->Left();
		int x2 = x1 + monster[monsterIndex]->Width();
		if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2) {
			return true;
		}
		return false;
	}
}