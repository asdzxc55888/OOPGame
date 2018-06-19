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
// �o��class���C�����C���}�Y�e������
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
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    //
    // �}�l���J���
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
    //Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
        GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo �����C������k
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (!isLoadInterfaceOnShow)
    {
        if (point.x > menuBtn[0]->Left() && point.x <  menuBtn[0]->Left() + menuBtn[0]->Width() && point.y >  menuBtn[0]->Top() && point.y < menuBtn[0]->Height() + menuBtn[0]->Top()) // �}�l�C��
        {
            CAudio::Instance()->Play(AUDIO_DECISION);
            GotoGameState(GAME_STATE_RUN);	  // ������GAME_STATE_RUN
            CAudio::Instance()->Play(AUDIO_GAMEBGM);
            CAudio::Instance()->Stop(AUDIO_MENUBGM);
        }

        if (point.x > menuBtn[1]->Left() && point.x <  menuBtn[1]->Left() + menuBtn[1]->Width() && point.y >  menuBtn[1]->Top() && point.y < menuBtn[1]->Height() + menuBtn[1]->Top()) // Ū���C��
        {
            CAudio::Instance()->Play(AUDIO_DECISION);
            isLoadInterfaceOnShow = true;
        }

        if (point.x > menuBtn[2]->Left() && point.x <  menuBtn[2]->Left() + menuBtn[2]->Width() && point.y >  menuBtn[2]->Top() && point.y < menuBtn[2]->Height() + menuBtn[2]->Top()) // ���}�C��
            exit(1);	
    }
    else
    {
        SaveIndex = Load.OnClick(point);

        if (SaveIndex != 0)
        {
            CAudio::Instance()->Play(AUDIO_GAMEBGM);
            CAudio::Instance()->Stop(AUDIO_MENUBGM);
            GotoGameState(GAME_STATE_RUN);	  // ������GAME_STATE_RUN
        }
    }
}
void CGameStateInit::OnRButtonDown(UINT nFlags, CPoint point)
{
    if (isLoadInterfaceOnShow)      //Ū�����������ʧ@
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
    // �K�Wlogo
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
            if (!menuBtn[i]->IsFinalBitmap())menuBtn[i]->OnMove();       //�Y���O�̫�@�ӹϧΡA�NOnMove��̫�@�ӹϧΫᰱ��C
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
    CSpecialEffect::SetCurrentTime();	// �]�w���}OnIdle()���ɶ�
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
    //
    // �}�l���J���
	CAudio::Instance()->Load(AUDIO_GAMEOVER, "Sounds\\GameOverBGM.mp3");
	bg.LoadBitmapA("Bitmaps\\Final.bmp");
    //
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �̲׶i�׬�100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	bg.ShowBitmap();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
    myGame->OnMove();

	if (myGame->GameOver())
	{
		SaveIndex = 0;
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
    //
    // �}�l���J���
    //
    myGame->OnInit();
    //
    // ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    myGame->OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y

    if (nChar == KEY_LEFT)
    {
    }
    else if (nChar == KEY_RIGHT)
    {
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    myGame->OnLButtonDown(nFlags, point);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    myGame->OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    myGame->OnRButtonDown(nFlags, point);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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