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
		IsInterfaceOnShow = false;
		nowTask = nothing;
		IsTaskShow[nothing] = true;
		IsTaskShow[1] = false;
		IsTaskShow[2] = false;
		TaskBoardImg.SetTopLeft(TaskBoard_x, TaskBoard_y);
		TaskBoardInterface.SetTopLeft(TaskBoardInterface_x, TaskBoardInterface_y);
		myTaskBlock[0]->SetPoint(TaskBoardInterface_x + 20, TaskBoardInterface_y + 20);
		myTaskBlock[1]->SetPoint(TaskBoardInterface_x + 20, TaskBoardInterface_y + 107);
		myTaskBlock[2]->SetPoint(TaskBoardInterface_x + 20, TaskBoardInterface_y + 194);
	}
	void TaskBoard::LoadBitmap()
	{
		TaskBoardImg.LoadBitmap("Bitmaps\\TaskBoard.bmp", RGB(255, 255, 255));
		TaskBoardInterface.LoadBitmap("Bitmaps\\TaskBoardInterface.bmp", RGB(255, 255, 255));
		for (int i = 0; i < 3; i++)myTaskBlock[i]->LoadBitmap();
	}
	void TaskBoard::OnShow()
	{
		if (IsInterfaceOnShow) {
			TaskBoardInterface.ShowBitmap();

			for (int i = 0; i < TaskSize; i++) {
				int count = 0;
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
	bool TaskBoard::IsMouseOnTaskBoard(CPoint point)
	{
		for (int i = 0; i < GetShowTaskSize(); i++)myTaskBlock[i]->IsMouseOn(point);
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			return true;
		}
		else return false;
	}
	bool TaskBoard::IsTaskOnClick(CPoint point)
	{
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			IsInterfaceOnShow = true;
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