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
		Initial();
	}
	TaskBoard::~TaskBoard()
	{
	}
	void TaskBoard::Initial()
	{
		IsInterfaceOnShow = false;
		nowTask = nothing;
		IsTaskShow[nothing] = true;
		TaskBoardImg.SetTopLeft(TaskBoard_x, TaskBoard_y);
		TaskBoardInterface.SetTopLeft(TaskBoardInterface_x, TaskBoardInterface_y);
		TaskBlock[0].SetTopLeft(TaskBoardInterface_x + 20, TaskBoardInterface_y+20);
		TaskBlock[1].SetTopLeft(TaskBoardInterface_x + 20, TaskBoardInterface_y + 107);
		TaskBlock[2].SetTopLeft(TaskBoardInterface_x + 20, TaskBoardInterface_y + 194);
	}
	void TaskBoard::LoadBitmap()
	{
		TaskBoardImg.LoadBitmap("Bitmaps\\TaskBoard.bmp", RGB(255, 255, 255));
		TaskBoardInterface.LoadBitmap("Bitmaps\\TaskBoardInterface.bmp", RGB(255, 255, 255));
	}
	void TaskBoard::OnShow()
	{
		if (IsInterfaceOnShow) {
			TaskBoardInterface.ShowBitmap();

			for (int i = 0; i < GetShowTaskSize(); i++) {
				TaskBlock[i].ShowBitmap();
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
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			return true;
		}
		else return false;
	}
	bool TaskBoard::IsTaskOnClick(CPoint point)
	{
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			return true;
		}
		else return false;
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
		return TaskBoardInterface_x;
	}
	TaskList TaskBoard::GetNowTask()
	{
		return nowTask;
	}
}