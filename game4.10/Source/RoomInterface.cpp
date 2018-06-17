#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RoomInterface.h"
#include "MonsterDataBoard.h"
namespace game_framework
{
RoomInterface::RoomInterface(Room** _gameRoom)
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
    roomNumber = new CInteger(3);

    for (int i = 0; i < 4; i++)isMouseOnBtn[i] = false;

    bg.LoadBitmap("Bitmaps\\gameRun\\Room_interface.bmp", RGB(255, 255, 255));
    Increase_btn.LoadBitmap("Bitmaps\\gameRun\\increase_button.bmp", RGB(255, 255, 255));
    Decrease_btn.LoadBitmap("Bitmaps\\gameRun\\decrease_button.bmp", RGB(255, 255, 255));
    Right_btn.LoadBitmap("Bitmaps\\gameRun\\right_button.bmp", RGB(255, 255, 255));
    Left_btn.LoadBitmap("Bitmaps\\gameRun\\left_button.bmp", RGB(255, 255, 255));
    cancle_btn.LoadBitmap("Bitmaps\\gameRun\\RoomInterface_deleteBtn.bmp", RGB(255, 255, 255));
    bg.SetTopLeft(RoomInterface_bg_x, RoomInterface_bg_y);
    Increase_btn.SetTopLeft(RoomInterface_Increase_x, RoomInterface_Increase_y);
    Decrease_btn.SetTopLeft(RoomInterface_Decrease_x, RoomInterface_Decrease_y);
    Right_btn.SetTopLeft(RoomInterface_Right_x, RoomInterface_Right_y);
    Left_btn.SetTopLeft(RoomInterface_Left_x, RoomInterface_Left_y);
    isMouseOn = false;
    isOnShow = false;
    isCancleShow = false;
    monsterSelector = 0;
    RoomSelector = 0;
    rentPercent = 0;
    maxPercent = 30;
    presentRent->SetIsBmpLoaded();
    presentRent->SetInteger(15);
    presentRent->SetTopLeft(RentInt_x, RemtInt_y);
    roomNumber->SetIsBmpLoaded();
    roomNumber->SetTopLeft(RoomInterface_RoomNumber_x, RoomInterface_RoomNumber_y);
    confirm_str[0] = "確認";                                         //確認框初始化
    confirm_str[1] = "取消";
    confirm_bg.LoadBitmap("Bitmaps\\gameRun\\Confirm_bg.bmp", RGB(255, 255, 255));
    confirm_bg.SetTopLeft(300, 250);
    isConfirmOnShow = false;

    for (int i = 0; i < 3; i++)
    {
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
        roomNumber->ShowBitmap();

        if (isMouseOnBtn[0])
        {
            Increase_btn.ShowBitmap(1.14);
        }
        else
        {
            Increase_btn.ShowBitmap();
        }

        if (isMouseOnBtn[1])
        {
            Decrease_btn.ShowBitmap(1.14);
        }
        else
        {
            Decrease_btn.ShowBitmap();
        }

        if (isMouseOnBtn[2])
        {
            Right_btn.ShowBitmap(1.14);
        }
        else
        {
            Right_btn.ShowBitmap();
        }

        if (isMouseOnBtn[3])
        {
            Left_btn.ShowBitmap(1.14);
        }
        else
        {
            Left_btn.ShowBitmap();
        }

        if (gameRoom[RoomSelector]->GetLiveMonsterSize() > 0 && isMouseOn)MonsterBoard->OnShow();

        if (isConfirmOnShow)
        {
			confirm_bg.ShowBitmap();
            ShowConfirm();
        }

        for (int i = 0; i < monster_count; i++)
        {
            if (monster[i] != NULL )
            {
                monster[i]->ShowBitmap();
            }
        }

        if (isCancleShow)cancle_btn.ShowBitmap();
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
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CPen* pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
    pp = pDC->SelectObject(&p);
    CBrush b2(RGB(0, 162, 232));					// 畫黃色 progrss進度
    pDC->SelectObject(&b2);
    pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
    pDC->SelectObject(pp);						// 釋放 pen
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void RoomInterface::ShowConfirm()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, t, *fp;
    t.CreatePointFont(160, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&t);					// 選用 font f
    pDC->SetBkColor(RGB(171, 208, 107));
    pDC->SetTextColor(RGB(254, 254, 200));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "是否驅逐居住的怪物");
    pDC->TextOut(300 + 80, 250 + 60, str);
    f.CreatePointFont(180, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    pDC->SetBkColor(RGB(171, 208, 107));

    for (int i = 0; i < 2; i++)
    {
        if (isConfirmBtnMouseOn[i])
        {
            pDC->SetTextColor(RGB(238, 216, 17));
        }
        else
        {
            pDC->SetTextColor(RGB(254, 254, 250));
        }

        char str[80];								// Demo 數字對字串的轉換
        sprintf(str, confirm_str[i].c_str());
        pDC->TextOut(300 + 150 + (i * 222), 250 + 120, str);
    }

    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void RoomInterface::SetInterfaceShow(bool flag)
{
    monster_count = 0;

    if (flag)
    {
        for (int i = 0; i < 3; i++) if (monster[i] != NULL)
            {
                delete monster[i];   //重新LOAD圖
                monster[i] = NULL;
            }

        for (int i = 0; i < gameRoom[RoomSelector]->GetLiveMonsterSize(); i++)              //Load怪物圖
        {
            monster[i] = new CMovingBitmap();
            Monster* _thisM = gameRoom[RoomSelector]->GetLiveMonster(i);

            if (_thisM->GetMonsterState() != leave)             //若怪物狀態為離開則不顯示
            {
                string _monsterType = _thisM->GetMonsterType();
                _monsterType += ".bmp";

                if (_thisM->GetMonsterGender() == male)
                {
                    _monsterType = "m_" + _monsterType;
                }
                else
                {
                    _monsterType = "w_" + _monsterType;
                }

                if (_thisM->GetIsKid()) _monsterType = "child_" + _monsterType;

                _monsterType = "Bitmaps\\monster\\monster_" + _monsterType;
                char root[200];
                strcpy(root, _monsterType.c_str());
                monster[monster_count]->LoadBitmap(root, RGB(255, 255, 255));

                if (_thisM->GetIsKid())
                {
                    monster[monster_count]->SetTopLeft(monsterBmp_x + monster_count * 65, monsterBmp_y + 20);
                }
                else
                {
                    monster[monster_count]->SetTopLeft(monsterBmp_x + monster_count * 60, monsterBmp_y);
                }

                monster_count++;
            }
        }

        if (gameRoom[RoomSelector]->GetLiveMonster(monsterSelector) != NULL)       //設定怪物之料
        {
            MonsterBoard = gameRoom[RoomSelector]->GetLiveMonster(monsterSelector)->GetMonsterDataBoard();
            MonsterBoard->SetPoint(600, 250);
        }

        ResetRent();
		isOnShow = true;
    }
    else
    {
		if (isConfirmOnShow) {
			isConfirmOnShow = false;
		}else if (gameRoom[RoomSelector]->GetLiveMonsterSize() > 0)
		{	
			MonsterBoard->SetPoint(50, 50);
			isOnShow = false;
		}
    }
}
void RoomInterface::SetRoomSelector(int index)
{
    RoomSelector = index;
    roomNumber->SetInteger(gameRoom[RoomSelector]->GetRoomNumber());
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
bool RoomInterface::GetIsConfirmOnShow()
{
	return isConfirmOnShow;
}
bool RoomInterface::IsMouseOn(CPoint point)
{
    isMouseOn = false;

    if (point.x > Increase_btn.Left() && point.x <= Increase_btn.Left() + Increase_btn.Width() && point.y > Increase_btn.Top() && point.y <= Increase_btn.Top() + Increase_btn.Height())
    {
        isMouseOnBtn[0] = true;
        return true;
    }
    else if (point.x > Decrease_btn.Left() && point.x <= Decrease_btn.Left() + Decrease_btn.Width() && point.y > Decrease_btn.Top() && point.y <= Decrease_btn.Top() + Decrease_btn.Height())
    {
        isMouseOnBtn[1] = true;
        return true;
    }
    else if (point.x > Right_btn.Left() && point.x <= Right_btn.Left() + Right_btn.Width() && point.y > Right_btn.Top() && point.y <= Right_btn.Top() + Right_btn.Height())
    {
        isMouseOnBtn[2] = true;
        return true;
    }
    else if (point.x > Left_btn.Left() && point.x <= Left_btn.Left() + Left_btn.Width() && point.y > Left_btn.Top() && point.y <= Left_btn.Top() + Left_btn.Height())
    {
        isMouseOnBtn[3] = true;
        return true;
    }

    for (int i = 0; i < 4; i++)isMouseOnBtn[i] = false;

    for (int i = 0; i < monster_count; i++)
    {
        int y1 = monster[i]->Top();
        int y2 = y1 + monster[i]->Height();
        int x1 = monster[i]->Left();
        int x2 = x1 + monster[i]->Width();

        if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
        {
            MonsterBoard->SetPoint(50, 50);
            monsterSelector = i;
            MonsterBoard = gameRoom[RoomSelector]->GetLiveMonster(monsterSelector)->GetMonsterDataBoard();
            MonsterBoard->SetPoint(600, 250);
            cancle_btn.SetTopLeft(cancle_x + i * 60, cancle_y);
            isCancleShow = true;
            isMouseOn = true;
            return true;
        }
    }

	if (isConfirmOnShow)
	{
		for (int i = 0; i < 2; i++)
		{
			int x1 = 300 + 150 + (i * 222);
			int x2 = x1 + 40;
			int y1 = 250 + 120;
			int y2 = y1 + 40;

			if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
			{
				isConfirmBtnMouseOn[i] = true;
				return true;
			}
			else
			{
				isConfirmBtnMouseOn[i] = false;
			}
		}
	}

    isCancleShow = false;
    return false;
}
bool RoomInterface::IsMouseClick(CPoint point, int monsterIndex)
{
    if (monster[monsterIndex] == NULL || monsterIndex >= monster_count)return false;

    int y1 = monster[monsterIndex]->Top();
    int y2 = y1 + monster[monsterIndex]->Height();
    int x1 = monster[monsterIndex]->Left();
    int x2 = x1 + monster[monsterIndex]->Width();

    if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
    {
		isConfirmOnShow = true;
		leaveMonsterIndex = monsterIndex;
		isConfirmBtnMouseOn[0] = false;      //確認按鈕初始化
		isConfirmBtnMouseOn[1] = false;
        return true;
    }

    return false;
}
bool RoomInterface::IsMouseClick(CPoint point)
{
    if (isMouseOnBtn[0])
    {
        if (gameRoom[RoomSelector]->GetRent() < maxPercent)
        {
            gameRoom[RoomSelector]->SetRent(gameRoom[RoomSelector]->GetRent() + maxPercent / 10);
            ResetRent();
        }
    }
    else if (isMouseOnBtn[1])
    {
        if (gameRoom[RoomSelector]->GetRent() > 0)
        {
            gameRoom[RoomSelector]->SetRent(gameRoom[RoomSelector]->GetRent() - maxPercent / 10);
            ResetRent();
        }
    }
    else if (isMouseOnBtn[2] && RoomSelector < 3)
    {
        SetRoomSelector(RoomSelector + 1);
        SetInterfaceShow(true);
    }
    else if (isMouseOnBtn[3] && RoomSelector > 0)
    {
        SetRoomSelector(RoomSelector - 1);
        SetInterfaceShow(true);
    }

    return false;
}
int RoomInterface::IsConfirmOnClick()
{
	if (isConfirmOnShow)
	{
		if (isConfirmBtnMouseOn[0])			//確認
		{
			isConfirmOnShow = false;
			return leaveMonsterIndex;
		}
		else if (isConfirmBtnMouseOn[1])     //取消
		{
			isConfirmOnShow = false;
			return -1;
		}
	}

	return -1;
}
void RoomInterface::ResetRent()
{
    presentRent->SetInteger(gameRoom[RoomSelector]->GetRent());                       //設定租金
    rentPercent = gameRoom[RoomSelector]->GetRent() * 100 / maxPercent;               //房租比例
}
}