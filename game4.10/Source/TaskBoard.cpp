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
	}
	void TaskBoard::Initial()
	{
		nowTask = nothing;
		TaskBoardImg.SetTopLeft(TaskBoard_x, TaskBoard_y);
		TaskBoardInterface.SetTopLeft(TaskBoardInterface_x, TaskBoardInterface_y);
	}
	void TaskBoard::LoadBitmap()
	{
		TaskBoardImg.LoadBitmap("Bitmaps\\TaskBoard.bmp", RGB(255, 255, 255));
		TaskBoardInterface.LoadBitmap("Bitmaps\\TaskBoardInterface.bmp", RGB(255, 255, 255));
	}
	void TaskBoard::OnShow()
	{

	}
	bool TaskBoard::IsMouseOnTaskBoard(CPoint point)
	{
		if (point.x > TaskBoard_x && point.x <= TaskBoard_x + TaskBoardImg.Width() && point.y > TaskBoard_y && point.y <= TaskBoard_y + TaskBoardImg.Height()) {
			return true;
		}
		else return false;
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