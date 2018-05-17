#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "stdafx.h"
#include "TaskBlock.h"

namespace game_framework {
	TaskBlock::TaskBlock()
	{
	}
	void TaskBlock::LoadBitmap()
	{
		BackGround.LoadBitmap("Bitmaps\\TaskBlock.bmp", RGB(255, 255, 255));
	}
	void TaskBlock::OnShow()
	{
	}
	void TaskBlock::SetPoint(int x, int y)
	{
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
		pDC->TextOut(x + 130, y + 85, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}