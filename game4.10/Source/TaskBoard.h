#pragma once
#include "TaskBlock.h"
enum TaskList{
	nothing,
	FirstTask
};
#define TaskSize 2
#define TaskBoardInterface_x 125
#define TaskBoardInterface_y 10
#define TaskBoard_x 330
#define TaskBoard_y 485
namespace game_framework {
	class TaskBoard
	{
	public:
		TaskBoard();
		~TaskBoard();
		void Initial();
		void LoadBitmap();
		void OnShow();
		void SetTaskShow(TaskList _task, bool flag);     //�]�w�����W������
		bool IsMouseOnTaskBoard(CPoint point);
		bool IsTaskOnClick(CPoint point);
		int  GetShowTaskSize();
		int  GetTaskBoardX();
		TaskList GetNowTask();
	private:
		bool IsTaskShow[TaskSize];       //���ȬO�_�X�{�b�����O
		bool IsInterfaceOnShow;
		TaskList nowTask;
		TaskBlock *myTaskBlock[3];
		CMovingBitmap TaskBoardInterface,TaskBoardImg;

	};
}