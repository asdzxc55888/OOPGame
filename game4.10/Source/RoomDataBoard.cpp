#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RoomDataBoard.h"

namespace game_framework
{
RoomDataBoard::RoomDataBoard(int liveMonsterSize, string monsterType[3], int monsterGender[3], string monsterName[3], bool monsterIsKid[3], int number)
{
    Initialize(liveMonsterSize, monsterType, monsterGender, monsterName, monsterIsKid, number);
}
RoomDataBoard::~RoomDataBoard()
{
}
void RoomDataBoard::Initialize(int liveMonsterSize, string monsterType[3], int monsterGender[3], string _monsterName[3], bool monsterIsKid[3], int number)
{
    MonsterImgSize = liveMonsterSize;
    RoomNumber = number;
    x = 50;
    y = 50;
    bmp.LoadBitmap("Bitmaps\\gameRun\\RoomBoard.bmp", RGB(255, 255, 255));
    bmp.SetTopLeft(x, y);

    for (int i = 0; i < liveMonsterSize; i++)
    {
        string _monsterType = monsterType[i];
        char path[100] = "Bitmaps\\monster\\monster_";

        if (monsterIsKid[i])strcat(path, "child_");

        if (monsterGender[i] == 0)strcat(path, "m_");
        else strcat(path, "w_");

        strcat(path, _monsterType.c_str());
        strcat(path, ".bmp");
        MonsterImg[i].LoadBitmap(path, RGB(255, 255, 255));

        if (monsterIsKid[i])
        {
            MonsterImg[i].SetTopLeft(x + 30, y + 40 + (i * 65));
        }
        else
        {
            MonsterImg[i].SetTopLeft(x + 25, y + 40 + (i * 65));
        }

        monsterName[i] = _monsterName[i];
    }
}
void RoomDataBoard::OnShow()
{
    bmp.ShowBitmap();

    for (int i = 0; i < MonsterImgSize; i++)
    {
        MonsterImg[i].ShowBitmap();
    }

    ShowName();
    ShowRoomNumber();
}
void RoomDataBoard::ShowName()
{
    for (int i = 0; i < MonsterImgSize; i++)
    {
        CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
        CFont f, *fp;
        f.CreatePointFont(100, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkColor(RGB(234, 245, 236));
        pDC->SetTextColor(RGB(0, 0, 0));
        char str[80];								// Demo 數字對字串的轉換
        sprintf(str, monsterName[i].c_str());
        pDC->TextOut(x + 90, y + 55 + (i * 60), str);
        pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
        CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    }
}
void RoomDataBoard::ShowRoomNumber()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(120, "Arial");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(234, 245, 236));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Room %d", RoomNumber);
    pDC->TextOut(x + 28, y + 18, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
}
