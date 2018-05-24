#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "TaskBoard.h"

namespace game_framework {
	TaskBoard::TaskBoard()
	{
		for (int i = 0; i < 3; i++)myTaskBlock[i] = new TaskBlock();
	}
	TaskBoard::~TaskBoard()
	{
	}
	void TaskBoard::Initial()
	{
		TaskTitle = "無事";
		IsInterfaceOnShow = false;
		nowTask = nothing;
		isMouseOn = false;
		IsTaskShow[nothing] = true;
		IsTaskShow[1] = true;
		IsTaskShow[2] = false;
		TaskBoardImg.SetTopLeft(TaskBoard_x, TaskBoard_y);
		TaskBoardInterface.SetTopLeft(TaskBoardInterface_x, TaskBoardInterface_y);
		TaskInformation.SetTopLeft(50, 50);
		myTaskBlock[0]->SetPoint(TaskBoardInterface_x + 135, TaskBoardInterface_y + 150);
		myTaskBlock[1]->SetPoint(TaskBoardInterface_x + 135, TaskBoardInterface_y + 237);
		myTaskBlock[2]->SetPoint(TaskBoardInterface_x + 135, TaskBoardInterface_y + 324);
	}
	void TaskBoard::LoadBitmap()
	{
		TaskBoardImg.LoadBitmap("Bitmaps\\TaskBoard.bmp", RGB(255, 255, 255));
		TaskBoardInterface.LoadBitmap("Bitmaps\\TaskBoardInterface.bmp", RGB(255, 255, 255));
		TaskInformation.LoadBitmap("Bitmaps\\TaskInformation.bmp", RGB(255, 255, 255));
		for (int i = 0; i < 3; i++)myTaskBlock[i]->LoadBitmap();
	}
	void TaskBoard::OnShow()
	{
		if (isMouseOn) {
			TaskInformation.ShowBitmap();
			ShowTaskName();
		}
		if (IsInterfaceOnShow) {
			TaskBoardInterface.ShowBitmap();
			int count = 0;
			for (int i = 0; i < TaskSize; i++) {
				if (IsTaskShow[i]) {
					myTaskBlock[count]->Initial(i);
					myTaskBlock[count++]->OnShow();
					if (count >= 3)break;
				}
			}
		}
		else {
			TaskBoardImg.ShowBitmap();
		}
		
	}
	void TaskBoard::SetTaskShow(TaskList _task, bool flag)
	{
		IsTaskShow[_task] = flag;
	}
	void TaskBoard::SetNowTask(TaskList _task)
	{
		nowTask = _task;
	}
	void TaskBoard::ShowTaskName()
	{
			CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
			CFont f, *fp;
			f.CreatePointFont(140, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(223, 215, 204));
			pDC->SetTextColor(RGB(0, 0, 0));
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, TaskTitle.c_str());
			pDC->TextOut(170,115, str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	bool TaskBoard::OnRButtonDown(UINT nFlags, CPoint point)
	{
		IsInterfaceOnShow = false;
		CAudio::Instance()->Play(AUDIO_DECISION);
		return true;
	}
	bool TaskBoard::IsMouseOnTaskBoard(CPoint point)
	{
		for (int i = 0; i < GetShowTaskSize(); i++)myTaskBlock[i]->IsMouseOn(point);
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			isMouseOn = true;
			return true;
		}
		else {
			isMouseOn = false;
			return false;
		}
	}
	bool TaskBoard::IsTaskOnClick(CPoint point)
	{
		for (int i = 0; i < GetShowTaskSize(); i++) {
			if (myTaskBlock[i]->IsMouseClick(point)) {
				nowTask = (TaskList)i;   //未完成
				TaskTitle = myTaskBlock[i]->GetTaskName();
			}
		}
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			IsInterfaceOnShow = true;
			CAudio::Instance()->Play(AUDIO_DECISION);
			return true;
		}
		return false;
	}
	int TaskBoard::GetShowTaskSize()
	{
		int result = 0;
		for (int i = 0; i < TaskSize; i++) {
			if (IsTaskShow[i])result++;
		}
		return result;
	}
	int TaskBoard::GetTaskBoardX()
	{
		return TaskBoard_x;
	}
	TaskList TaskBoard::GetNowTask()
	{
		return nowTask;
	}
}