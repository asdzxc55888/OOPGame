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
		presentRent = new CInteger(2);

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
		rentPercent = 0;
		maxPercent = 15;
		presentRent->SetIsBmpLoaded();
		presentRent->SetInteger(15);
		presentRent->SetTopLeft(RentInt_x, RemtInt_y);
		for (int i = 0; i < 3; i++) {
			monster[i] = NULL;
		}
	}
	void RoomInterface::OnShow()
	{
		if (isOnShow) 
		{
			bg.ShowBitmap();
			ShowRentBar();
			presentRent->ShowBitmap();
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
	void RoomInterface::ShowRentBar()
	{
		if (!SHOW_LOAD_PROGRESS)
			return;
		const int bar_width = 120;
		const int bar_height = 19;
		const int x1 = RentPercent_x + 70;
		const int x2 = x1 + bar_width;
		const int y1 = RentPercent_y + 125;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + rentPercent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);
		if (rentPercent >= 50) {
			CBrush b2(RGB(0, 162, 232));					// 畫黃色 progrss進度
			pDC->SelectObject(&b2);
			pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
		}

		pDC->SelectObject(pp);						// 釋放 pen
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void RoomInterface::SetInterfaceShow(bool flag)
	{
		if (flag) {
			for (int i = 0; i < 3; i++) if (monster[i] != NULL) {
				delete monster[i];   //重新LOAD圖
				monster[i] = NULL;
			}

			for (int i = 0; i < gameRoom[RoomSelector]->GetLiveMonsterSize(); i++)              //Load怪物圖
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
			presentRent->SetInteger(gameRoom[RoomSelector]->GetRent());                       //設定租金
			rentPercent = gameRoom[RoomSelector]->GetRent() * 100 /maxPercent;               //房租比例
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