#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<iostream>
#include<fstream>
#include "audio.h"
#include "gamelib.h"
#include "stdafx.h"
#include "TaskBlock.h"

namespace game_framework {
	TaskBlock::TaskBlock()
	{
	}
	TaskBlock::~TaskBlock()
	{
	}
	void TaskBlock::Initial(int Index)
	{
		isMouseOn = false;

		char line[50] = "";
		int count = 0;
		vector<string> Data;       //名稱 內容 獎勵
		fstream nameFile;
		nameFile.open("Source\\TaskContent.txt", ios::in);
		while (nameFile.getline(line, sizeof(line), '\n')) {
			if (atoi(line) == Index) {
				for (int i = 0; i < 3;i++) {
					nameFile.getline(line, sizeof(line), '!');
					Data.push_back(line);
				}
				break;
			}
		}
		TaskName = Data[0];
		Content = Data[1];
		reward_str = Data[2];
		TaskContentBackGround.SetTopLeft(TaskContent_x, TaskContent_y);
	}
	void TaskBlock::LoadBitmap()
	{
		TaskBlockBackGround.LoadBitmap("Bitmaps\\TaskBlock.bmp", RGB(255, 255, 255));
		TaskContentBackGround.LoadBitmap("Bitmaps\\Instruction.bmp", RGB(255, 255, 255));
	}
	void TaskBlock::OnShow()
	{
		TaskBlockBackGround.ShowBitmap();
		ShowTitle();
		if (isMouseOn) {
			TaskContentBackGround.ShowBitmap();
			ShowTaskName();
			ShowContent();
			ShowReward_str();
		}
	}
	void TaskBlock::SetPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
		TaskBlockBackGround.SetTopLeft(x, y);
	}
	void TaskBlock::ShowTitle()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(120, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(254, 233, 189));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, TaskName.c_str());
		pDC->TextOut(x+20, y+10, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void TaskBlock::ShowTaskName()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(120, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(254, 233, 189));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, TaskName.c_str());
		pDC->TextOut(TaskName_x, TaskName_y, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void TaskBlock::ShowContent()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(120, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(254, 233, 189));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, Content.c_str());
		pDC->TextOut(Content_x, Content_y, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void TaskBlock::ShowReward_str()
	{
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(120, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(254, 233, 189));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, reward_str.c_str());
		pDC->TextOut(reward_str_x, reward_str_y, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	void TaskBlock::IsMouseOn(CPoint point)
	{
		if (point.x > x && point.x <= x + TaskBlockBackGround.Width() && point.y > y && point.y <= y + TaskBlockBackGround.Height()) {
			isMouseOn = true;
		}
		else isMouseOn = false;
	}
}