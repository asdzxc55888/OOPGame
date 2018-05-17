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
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(120, "Yu Gothic UI Semibold");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(254, 233, 189));
		pDC->SetTextColor(RGB(0, 0, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, TaskName.c_str());
		pDC->TextOut(x + 130, y + 85, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
}