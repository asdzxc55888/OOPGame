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
	}
	void LoadInterface::ShowSave()
	{/*
		for (int i = 0; i < MonsterImgSize; i++) {
			CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
			CFont f, *fp;
			f.CreatePointFont(100, "Yu Gothic UI Semibold");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(RGB(234, 245, 236));
			pDC->SetTextColor(RGB(0, 0, 0));
			char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
			sprintf(str, monsterName[i].c_str());
			pDC->TextOut(x + 90, y + 55 + (i * 60), str);
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}*/
	}
	void LoadInterface::LoadSaveData()
	{
		string fileName[5] = { "save1","save2","save3","save4","save5" };
		char buf[10240];
		for (int i = 0; i < 5; i++) {
			fstream saveFile;
			saveFile.open(fileName[i], ios::in);
			saveFile.read(buf, sizeof(buf));
			
			saveFile.close();
		}
	}
}