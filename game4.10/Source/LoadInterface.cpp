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
namespace game_framework {
	LoadInterface::LoadInterface()
	{

	}
	LoadInterface::~LoadInterface()
	{
	}
	void LoadInterface::Initial()
	{
		bg.SetTopLeft(LoadInterface_bg_x, LoadInterface_bg_y);
	}
	void LoadInterface::OnShow()
	{
		bg.ShowBitmap();
		ShowSave();
	}
	void LoadInterface::OnClick(int saveIndex)
	{

	}
	void LoadInterface::ShowSave()
	{
		for (int i = 0; i < 5; i++) {
			CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
			CFont f, *fp;
			f.CreatePointFont(100, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(234, 245, 236));
			pDC->SetTextColor(RGB(0, 0, 0));
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, save_str[i].c_str());
			pDC->TextOut(LoadInterface_bg_x + 90, LoadInterface_bg_y + 55 + (i * 60), str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}
	}
	void LoadInterface::LoadSaveData()
	{
		string fileName[5] = { "save1","save2","save3","save4","save5" };
		char buf[10240];
		char temp[10240];
		for (int i = 0; i < 5; i++) {
			fstream saveFile;
			strcpy(temp, buf);
			saveFile.open(fileName[i], ios::in);
			if (saveFile) {
				saveFile.read(buf, sizeof(buf));
				save_str[i] = strtok(temp, "\n");
				saveFile.close();
			}
			else {
				save_str[i] = "---------------------";
			}
		}
	}
}