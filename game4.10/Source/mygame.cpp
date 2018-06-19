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
    for (int i = 0; i < 3; i++)
        menuBtn[i] = new CAnimation(3);

    isLoadingBitmaps = false;
}

CGameStateInit::~CGameStateInit()
{
    for (int i = 0; i < 3; i++)delete menuBtn[i];
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
    Load.LoadBitmap();
    temp.LoadBitmap();
    Background.LoadBitmap("Bitmaps\\StartBackground.bmp");
    menuBtn[0]->AddBitmap("Bitmaps\\menu\\start.bmp", RGB(255, 255, 255));
    menuBtn[0]->AddBitmap("Bitmaps\\menu\\start1.bmp", RGB(255, 255, 255));
    menuBtn[1]->AddBitmap("Bitmaps\\menu\\load.bmp", RGB(255, 255, 255));
    menuBtn[1]->AddBitmap("Bitmaps\\menu\\load1.bmp", RGB(255, 255, 255));
    menuBtn[2]->AddBitmap("Bitmaps\\menu\\Quit.bmp", RGB(255, 255, 255));
    menuBtn[2]->AddBitmap("Bitmaps\\menu\\Quit1.bmp", RGB(255, 255, 255));
	CAudio::Instance()->Load(AUDIO_Fail, "Sounds\\fail.mp3");
    CAudio::Instance()->Load(AUDIO_DING, "Sounds\\Ding.mp3");
    CAudio::Instance()->Load(AUDIO_DECISION, "Sounds\\decision.mp3");
    CAudio::Instance()->Load(AUDIO_MENUBGM, "Sounds\\menuBGM.mp3");
    CAudio::Instance()->Load(AUDIO_GAMEBGM, "Sounds\\GameBGM.mp3");
    //Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
    isLoadingBitmaps = true;
    isLoadInterfaceOnShow = false;
}

void CGameStateInit::OnBeginState()
{
    for (int i = 0; i < 3; i++)isMouseOn[i] = false;

    BGM = false;
	isPlayAudio = false;
	isLoadInterfaceOnShow = false;

	CAudio::Instance()->Pause();
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
    if (!isLoadInterfaceOnShow)
    {
        if (point.x > menuBtn[0]->Left() && point.x <  menuBtn[0]->Left() + menuBtn[0]->Width() && point.y >  menuBtn[0]->Top() && point.y < menuBtn[0]->Height() + menuBtn[0]->Top()) // 開始遊戲
        {
            CAudio::Instance()->Play(AUDIO_DECISION);
            GotoGameState(GAME_STATE_RUN);	  // 切換至GAME_STATE_RUN
            CAudio::Instance()->Play(AUDIO_GAMEBGM);
            CAudio::Instance()->Stop(AUDIO_MENUBGM);
        }

        if (point.x > menuBtn[1]->Left() && point.x <  menuBtn[1]->Left() + menuBtn[1]->Width() && point.y >  menuBtn[1]->Top() && point.y < menuBtn[1]->Height() + menuBtn[1]->Top()) // 讀取遊戲
        {
            CAudio::Instance()->Play(AUDIO_DECISION);
            isLoadInterfaceOnShow = true;
        }

        if (point.x > menuBtn[2]->Left() && point.x <  menuBtn[2]->Left() + menuBtn[2]->Width() && point.y >  menuBtn[2]->Top() && point.y < menuBtn[2]->Height() + menuBtn[2]->Top()) // 離開遊戲
            exit(1);	
    }
    else
    {
        SaveIndex = Load.OnClick(point);

        if (SaveIndex != 0)
        {
            CAudio::Instance()->Play(AUDIO_GAMEBGM);
            CAudio::Instance()->Stop(AUDIO_MENUBGM);
            GotoGameState(GAME_STATE_RUN);	  // 切換至GAME_STATE_RUN
        }
    }
}
void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
{
    if (isLoadInterfaceOnShow)      //讀取介面取消動作
    {
        CAudio::Instance()->Play(AUDIO_DING);
        isLoadInterfaceOnShow = false;
    }
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    if (isLoadingBitmaps && !isLoadInterfaceOnShow)
    {
        for (int i = 0; i < 3; i++)
        {
            if (point.x > menuBtn[i]->Left() && point.x <  menuBtn[i]->Left() + menuBtn[i]->Width() && point.y >  menuBtn[i]->Top() && point.y < menuBtn[i]->Height() + menuBtn[i]->Top())
            {
                if (!isPlayAudio && !isMouseOn[i])CAudio::Instance()->Play(AUDIO_DING);

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
    else if (isLoadInterfaceOnShow)
    {
        if (Load.MouseOn(point))
        {
            if (!isPlayAudio)
            {
                CAudio::Instance()->Play(AUDIO_DING);
            }

            isPlayAudio = true;
        }
        else
        {
            isPlayAudio = false;
        }
    }
}


void CGameStateInit::OnShow()
{
    //
    // 貼上logo
    //
    if (!BGM)
    {
        CAudio::Instance()->Play(AUDIO_MENUBGM);
        BGM = true;
    }

    Background.ShowBitmap();

    for (int i = 0; i < 3; i++)
    {
        if (isMouseOn[i])
        {
            if (!menuBtn[i]->IsFinalBitmap())menuBtn[i]->OnMove();       //若不是最後一個圖形，就OnMove到最後一個圖形後停止。
        }
        else  menuBtn[i]->Reset();

        menuBtn[i]->SetTopLeft((SIZE_X - menuBtn[i]->Width()) / 2, SIZE_Y / 2 + 70 * (i + 1));
        menuBtn[i]->OnShow();
    }

    if (isLoadInterfaceOnShow)
    {
        Load.OnShow();
    }

    CSpecialEffect::DelayFromSetCurrentTime(GAME_CYCLE_TIME);
    CSpecialEffect::SetCurrentTime();	// 設定離開OnIdle()的時間
  
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

	bg.SetTopLeft(bg.Left(), bg.Top() - 3);

    if (counter < 0)
        GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 27; // 5 seconds
	CAudio::Instance()->Stop(AUDIO_Fail);
	CAudio::Instance()->Play(AUDIO_GAMEOVER);
	bg.SetTopLeft(0, 600);
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
	CAudio::Instance()->Load(AUDIO_GAMEOVER, "Sounds\\GameOverBGM.mp3");
	bg.LoadBitmapA("Bitmaps\\Final.bmp");
    //
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	bg.ShowBitmap();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
	myGame = new GameEvent();
}

CGameStateRun::~CGameStateRun()
{
    delete myGame;
}

void CGameStateRun::OnBeginState()
{
    myGame->OnBeginState();
    LoadGame();
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    myGame->OnMove();

	if (myGame->GameOver())
	{
		SaveIndex = 0;
		GotoGameState(GAME_STATE_OVER);
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
    myGame->OnInit();
    //
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    myGame->OnKeyDown(nChar, nRepCnt, nFlags);
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
    myGame->OnLButtonDown(nFlags, point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    myGame->OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    myGame->OnRButtonDown(nFlags, point);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::LoadGame()
{
    if (SaveIndex != 0)
    {
        string saveName_str = "save";
        char NumTemp = '0' + SaveIndex;
        saveName_str += NumTemp;
        myGame->LoadGame(saveName_str);
    }
}

void CGameStateRun::OnShow()
{
	myGame->OnShow();
}

}