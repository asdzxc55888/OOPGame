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
		bool IsMouseOnTaskBoard(CPoint point);
		int  GetTaskBoardX();
		TaskList GetNowTask();
	private:
		bool IsTaskShow[TaskSize];       //任務是否出現在介面板
		TaskList nowTask;
		CMovingBitmap TaskBoardInterface,TaskBoardImg;
	};
}