#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "MonsterDataBoard.h"
namespace game_framework {
	MonsterDataBoard::MonsterDataBoard(int MaxHp, int ApD, int AdD, int dps, string MonsterType,bool flag)
	{
		isLoadBitmaps = false;
		Initialize(MaxHp, ApD, AdD, dps, MonsterType,flag);
	}
	MonsterDataBoard::MonsterDataBoard()
	{
		isLoadBitmaps = false;
		Initialize(10, 10, 10, 10, "tentacle",true);
	}
	MonsterDataBoard::~MonsterDataBoard()
	{
		delete Hp,MaxHp,AttackPower,AdDefense,ApDefense;
	}
	void MonsterDataBoard::Initialize(int maxHp, int ApD, int AdD, int dps, string MonsterType,bool flag)
	{
		Hp= new CInteger(GetDigit(maxHp));
		MaxHp = new CInteger(GetDigit(maxHp));
		AttackPower = new CInteger(GetDigit(dps));
		AdDefense = new CInteger(GetDigit(AdD));
		ApDefense = new CInteger(GetDigit(ApD));
		if (!isLoadBitmaps) {
			Board.LoadBitmap("Bitmaps\\gameRun\\MonsterBoard.bmp", RGB(255, 255, 255));
			if (flag) {                                                                    //flag=true為怪物 FALSE為勇士
				char temp[100] = "Bitmaps\\monster\\monster_";
				strcat(temp, MonsterType.c_str());
				strcat(temp, ".bmp");
				Picture.LoadBitmap(temp, RGB(255, 255, 255));
			}
			else {
				char temp[100] = "Bitmaps\\warrior\\warrior_";
				strcat(temp, MonsterType.c_str());
				strcat(temp, ".bmp");
				Picture.LoadBitmap(temp, RGB(255, 255, 255));
			}
			Hp->SetIsBmpLoaded();
			MaxHp->SetIsBmpLoaded();
			AttackPower->SetIsBmpLoaded();
			AdDefense->SetIsBmpLoaded();
			ApDefense->SetIsBmpLoaded();
			isLoadBitmaps = true;
		}
		
		SetData(maxHp, maxHp, ApD, AdD, dps);
		//////////////////////////////////////////////////////////////////////
		x = 50;
		y = 50;

		Board.SetTopLeft(x, y);
		MaxHp->SetTopLeft(x + 310, y + 130);
		Hp->SetTopLeft(x + 260, y + 130);
		AttackPower->SetTopLeft(x + 70, y + 170);
		AdDefense->SetTopLeft(x + 190, y + 170);
		ApDefense->SetTopLeft(x + 300, y + 170);
		Picture.SetTopLeft(x + 35, y + 20);

	}
	void MonsterDataBoard::ShowHpBar(int percent)
	{
		if (!SHOW_LOAD_PROGRESS)
			return;
		const int bar_width = 170;
		const int bar_height = 25;
		const int x1 = x+70;
		const int x2 = x1 + bar_width;
		const int y1 = y+125 ;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);
		if (percent >= 50) {
			CBrush b2(RGB(0, 255, 0));					// 畫黃色 progrss進度
			pDC->SelectObject(&b2);
			pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
		}
		else {
			int Green = 255 - (50 - percent) * 8;
			if (Green <= 0)Green = 0;
			CBrush b3(RGB(255, Green, 0));					// 畫黃色 progrss進度
			pDC->SelectObject(&b3);
			pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
		}

		pDC->SelectObject(pp);						// 釋放 pen
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void MonsterDataBoard::SetData(int hp, int maxHp, int ApD, int AdD, int dps)
	{
		Hp->SetInteger(hp);
		MaxHp->SetInteger(maxHp);
		AttackPower->SetInteger(dps);
		AdDefense->SetInteger(AdD);
		ApDefense->SetInteger(ApD);
	}
	void MonsterDataBoard::OnShow()
	{
		Board.ShowBitmap();
		MaxHp->ShowBitmap();
		Hp->ShowBitmap();
		AttackPower->ShowBitmap();
		AdDefense->ShowBitmap();
		ApDefense->ShowBitmap();
		Picture.ShowBitmap(1.2);

		ShowHpBar(Hp->GetInteger()*100/MaxHp->GetInteger());
	}

	int MonsterDataBoard::GetDigit(int x)
	{
		int result = 0;
		while (x >= 1) {
			x /= 10;
			result++;
		}
		return result;
	}
	
}