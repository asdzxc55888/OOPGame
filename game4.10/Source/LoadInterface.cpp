#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<iostream>
#include<fstream>
#include<vector>
#include "audio.h"
#include "gamelib.h"
#include "LoadInterface.h"
namespace game_framework
{
LoadInterface::LoadInterface()
{
    Initial();
}
LoadInterface::~LoadInterface()
{
}
void LoadInterface::Initial()
{
    for (int i = 0; i < Save_size; i++)isSaveExist[i] = false;

    LoadSaveData();
    isMusicOn = false;
}
void LoadInterface::LoadBitmap()
{
    bg.LoadBitmap("Bitmaps\\menu\\LoadInterface.bmp", RGB(255, 255, 255));
    bg.SetTopLeft(LoadInterface_bg_x, LoadInterface_bg_y);
}
void LoadInterface::OnShow()
{
    bg.ShowBitmap();
    ShowSave();
}
bool LoadInterface::MouseOn(CPoint point)
{
    for (int i = 0; i < Save_size; i++)
    {
        int x1 = LoadInterface_bg_x + 90;
        int x2 = x1 + 500;
        int y1 = LoadInterface_bg_y + 75 + (i * 80);
        int y2 = y1 + 50;

        if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
        {
            isSaveMouseOn[i] = true;
            return true;
        }
        else
        {
            isSaveMouseOn[i] = false;
        }
    }

    return false;
}
void LoadInterface::ShowSave()
{
    for (int i = 0; i < Save_size; i++)
    {
        CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
        CFont f, *fp;
        f.CreatePointFont(240, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkColor(RGB(224, 223, 209));

        if (isSaveMouseOn[i])
        {
            pDC->SetTextColor(RGB(238, 216, 17));
        }
        else
        {
            pDC->SetTextColor(RGB(0, 0, 0));
        }

        char str[80];								// Demo 數字對字串的轉換
        sprintf(str, save_str[i].c_str());
        pDC->TextOut(LoadInterface_bg_x + 90, LoadInterface_bg_y + 75 + (i * 80), str);
        pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
        CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
    }
}
void LoadInterface::LoadSaveData()
{
    string fileName[Save_size] = { "save1", "save2", "save3", "save4", "save5" };
    char buf[10240];
    char temp[10240];

    for (int i = 0; i < Save_size; i++)
    {
        fstream saveFile;
        saveFile.open("Save\\" + fileName[i] + ".txt", ios::in);

        if (saveFile)
        {
            saveFile.read(buf, sizeof(buf));
            strcpy(temp, buf);
            save_str[i] = strtok(temp, "\n");
            isSaveExist[i] = true;
            saveFile.close();
        }
        else
        {
            save_str[i] = "---------------------";
        }
    }
}
int LoadInterface::OnClick(CPoint point)
{
    for (int i = 0; i < Save_size; i++)
    {
		if (isSaveMouseOn[i] && isSaveExist[i]) {
			return i + 1;
		}
    }

    return 0;
}
}