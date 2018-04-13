/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
    for (int i = 0; i < 4; i++)
        menuBtn[i] = new CAnimation(3);
}

CGameStateInit::~CGameStateInit()
{
    for (int i = 0; i < 4; i++)delete menuBtn[i];
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0);	// 一開始的loading進度為0%
    //
    // 開始載入資料
    //
    Background.LoadBitmap("Bitmaps\\StartBackground.bmp");
    menuBtn[0]->AddBitmap("Bitmaps\\menu\\start.bmp", RGB(255, 255, 255));
    menuBtn[0]->AddBitmap("Bitmaps\\menu\\start1.bmp", RGB(255, 255, 255));
    menuBtn[1]->AddBitmap("Bitmaps\\menu\\load.bmp", RGB(255, 255, 255));
    menuBtn[1]->AddBitmap("Bitmaps\\menu\\load1.bmp", RGB(255, 255, 255));
    menuBtn[2]->AddBitmap("Bitmaps\\menu\\Options.bmp", RGB(255, 255, 255));
    menuBtn[2]->AddBitmap("Bitmaps\\menu\\Options1.bmp", RGB(255, 255, 255));
    menuBtn[3]->AddBitmap("Bitmaps\\menu\\Quit.bmp", RGB(255, 255, 255));
    menuBtn[3]->AddBitmap("Bitmaps\\menu\\Quit1.bmp", RGB(255, 255, 255));
    CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
    isLoadingBitmaps = true;
}

void CGameStateInit::OnBeginState()
{
    for (int i = 0; i < 4; i++)isMouseOn[i] = false;

    isLoadingBitmaps = false;
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (point.x > menuBtn[0]->Left() && point.x <  menuBtn[0]->Left() + menuBtn[0]->Width() && point.y >  menuBtn[0]->Top() && point.y < menuBtn[0]->Height() + menuBtn[0]->Top()) // 開始遊戲
        GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN

    if (point.x > menuBtn[3]->Left() && point.x <  menuBtn[3]->Left() + menuBtn[3]->Width() && point.y >  menuBtn[3]->Top() && point.y < menuBtn[3]->Height() + menuBtn[3]->Top()) // 開始遊戲
        exit(1);		// 離開遊戲
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    if (isLoadingBitmaps)
    {
        for (int i = 0; i < 4; i++)
        {
            if (point.x > menuBtn[i]->Left() && point.x <  menuBtn[i]->Left() + menuBtn[i]->Width() && point.y >  menuBtn[i]->Top() && point.y < menuBtn[i]->Height() + menuBtn[i]->Top())
            {
                if (!isPlayAudio)CAudio::Instance()->Play(AUDIO_DING);

                isMouseOn[i] = true;
                isPlayAudio = true;
            }
            else
            {
                isMouseOn[i] = false;
                isPlayAudio = false;
            }
        }
    }
}


void CGameStateInit::OnShow()
{
    //
    // 貼上logo
    //
    Background.ShowBitmap();

    for (int i = 0; i < 4; i++)
    {
        if (isMouseOn[i])
        {
            if (!menuBtn[i]->IsFinalBitmap())menuBtn[i]->OnMove();       //若不是最後一個圖形，就OnMove到最後一個圖形後停止。
        }
        else  menuBtn[i]->Reset();

        menuBtn[i]->SetTopLeft((SIZE_X - menuBtn[i]->Width()) / 2, SIZE_Y / 2 + 60 * (i + 1));
        menuBtn[i]->OnShow();
    }

    //
    // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
    //
    /*
    CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f,*fp;
    f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
    fp=pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0,0,0));
    pDC->SetTextColor(RGB(255,255,0));
    pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
    pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
    if (ENABLE_GAME_PAUSE)
    	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
    pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

    */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
        GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
    //
    // 開始載入資料
    //
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
    comingMonster = NULL;
	Clock = NULL;
    int room_x = 650, room_y = 510;

    for (int i = 0; i < 4; i++)gameRoom[i] = new Room(room_x + i * 115, room_y);
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    TaskBoard.SetTopLeft(330, 485);   //設定任務版座標
	Warning.SetTopLeft(-1280, 100);
    roomSize = 4;
	Clock = int(time(&nowtime))+60000;
    isOnBattle = false;
    isIntoBattle = false;

    for (int i = 0; i < 10; i++)warrior[i] = NULL;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    OnEvent();
	if (Warning.Left() > -1280) {                                  //警告圖片向左移動
		Warning.SetTopLeft(Warning.Left() - 20, Warning.Top());
	}
    if (comingMonster != NULL)
    {
        comingMonster->OnMove();
    }
	for (int i = 0; i < 10; i++) {
		if (warrior[i] != NULL) {
			warrior[i]->OnMove();
		}
	}
    for (int i = 0; i < 4; i++)
    {
        gameRoom[i]->OnMove();
    }
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
    //
    // 開始載入資料
    //
    Background.LoadBitmap("Bitmaps\\gameBackground1.bmp");
    TaskBoard.LoadBitmap("Bitmaps\\TaskBoard.bmp", RGB(255, 255, 255));
	Warning.LoadBitmap("Bitmaps\\Warning.bmp", RGB(255, 255, 255));
    CAudio::Instance()->Load(AUDIO_DOOROPEN, "Sounds\\RoomOpen.mp3");
    CAudio::Instance()->Load(AUDIO_DOORCLOSE, "Sounds\\RoomClose.mp3");

    for (int i = 0; i < 4; i++)gameRoom[i]->LoadBitmap();

    //
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭

    if (nChar == KEY_LEFT)
    {
    }
    else if (nChar == KEY_RIGHT)
    {
    }
    else if (nChar == KEY_UP)
    {
        BattleTest1(warrior, isIntoBattle, gameRoom);
    }
    else if (nChar == KEY_DOWN)
    {
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭

    if (nChar == KEY_LEFT)
    {
    }
    else if (nChar == KEY_RIGHT)
    {
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    if (comingMonster != NULL && comingMonster->IsMouseOn(point)) //若點選到拜訪的怪物
    {
        MonsterBeingClick(&comingMonster, 4, gameRoom);
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    /*for (int i = 0; i > 4; i++) {
    	gameRoom[i]->IsMouseOn(point);
    }*/
    // 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (isOnBattle) {
		for (int i = 0; i < roomSize; i++) {
			if (gameRoom[i]->IsMouseOn(point) && gameRoom[i]->GetIsMonsterIn()) {
				gameRoom[i]->SetMonsterFight(true);
			}
			Monster* _monster = gameRoom[i]->GetLiveMonster();
			if (_monster->GetIsOnBattle() && _monster->IsMouseOn(point)) {
				MonsterGohome_event(gameRoom[i]);
				_monster->SetIsOnBattle(false);
			}
		}
	}
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    //
    //  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
    //        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
    //        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
    //
    Background.ShowBitmap();
    TaskBoard.ShowBitmap();

    for (int i = 0; i < 4; i++)gameRoom[i]->OnShow(true);

    for (int i = 0; i < 4; i++)gameRoom[i]->OnShow(false);
	for (int i = 0; i < 10; i++) {
		if (warrior[i] != NULL) {
			warrior[i]->OnShow();
		}
	}
    if (comingMonster != NULL)
    {
        comingMonster->OnShow();
    }
	Warning.ShowBitmap();
}
void CGameStateRun::OnEvent()
{
	if (isIntoBattle)  //進入戰鬥時的事件
	{
		Warning.SetTopLeft(1280, 100); //警告圖片
		if (comingMonster != NULL)comingMonster->SetMonsterState(leave); //拜訪怪物離開

		for (int i = 0; i < roomSize; i++)
		{
			if (gameRoom[i]->GetIsMonsterLiving() && !gameRoom[i]->GetIsMonsterIn()) {
				MonsterGohome_event(gameRoom[i]);
			}
		}
		Clock = int(time(&nowtime));
		isIntoBattle = false;
		isOnBattle = true;
	}
	/////////////////////////////////////////////////////////////////////////////勇者攻擊事件
	if (isOnBattle && difftime(time(&nowtime), Clock) > 5) {
		if (warrior[0] != NULL)
		{
			Monster* target = findMonsterTarget(warrior[0], gameRoom, roomSize);

			if (target != NULL)
			{
				WarriorAttack_event(warrior[0], &target);
			}
			else {
				Moving(&(warrior[0]), 700, 1);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////怪物攻擊事件
	if (isOnBattle) {
		for (int i = 0; i < roomSize; i++) {
			if (gameRoom[i]->GetLiveMonster()->GetIsOnBattle()) {
				Monster* _monster = gameRoom[i]->GetLiveMonster();
				Warrior* target = findWarriorTarget(_monster, warrior);
				if (target!=NULL) {
					MonsterAttack_event(_monster, &warrior[0]);
				}
				else {                                         //結束戰鬥
					BattleEnd(gameRoom,roomSize);
					isOnBattle = false;
					break;
				}
			}
		}
	}

    /////////////////////////////////////////////////////////////////////////////拜訪怪物事件
    if (comingMonster != NULL)
    {
        Monster_state comingMonsterState = comingMonster->GetMonsterState();
        int randvalue = rand() % 1000;

        switch (comingMonsterState)
        {
            case game_framework::leave:
                MonsterLeave(&comingMonster);
                break;

            case game_framework::nothing:
                MonsterFindHouse(&comingMonster, TaskBoard.Left(), TaskBoard.Width());
                break;

            case game_framework::findHouse:
                if (randvalue < 5)
                {
                    comingMonster->SetMonsterState(leave);
                }

                break;

            default:
                break;
        }
    }
    else
    {
        if (!isOnBattle)CreateMonster_event(&comingMonster);
    }

    ///////////////////////////////////////////////////////////////////////////
}
}