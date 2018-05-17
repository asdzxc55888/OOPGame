#pragma once
enum TaskList{
	nothing,
	FirstTask
};
#define TaskSize 2
#define TaskBoardInterface_x 20
#define TaskBoardInterface_y 20
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
		void SetTaskShow(TaskList _task, bool flag);     //設定介面上的任務
		bool IsMouseOnTaskBoard(CPoint point);
		bool IsTaskOnClick(CPoint point);
		int  GetShowTaskSize();
		int  GetTaskBoardX();
		TaskList GetNowTask();
	private:
		int  TaskShowIndex[3];
		bool IsTaskShow[TaskSize];       //任務是否出現在介面板
		bool IsInterfaceOnShow;
		TaskList nowTask;
		TaskBlock *myTaskBlock[3];
		CMovingBitmap TaskBoardInterface,TaskBoardImg;

	};
}