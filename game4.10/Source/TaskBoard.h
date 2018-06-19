#pragma once
#include "TaskBlock.h"
enum TaskList
{
    nothing,
    FirstTask,
	eggComing,
    Boss
};
#define TaskSize 4
#define TaskBoardInterface_x 125
#define TaskBoardInterface_y 20
#define TaskBoard_x 330
#define TaskBoard_y 485
namespace game_framework
{
class TaskBoard
{
    public:
        TaskBoard();
        ~TaskBoard();
        void Initial();
        void LoadBitmap();
        void OnShow();
        void SetTaskShow(TaskList _task, bool flag);     //設定介面上的任務
        void SetNowTask(TaskList _task);
        void SetCompletionPercent(int percent);                                //設定任務完成度
        void ShowTaskName();
        bool OnRButtonDown(UINT nFlags, CPoint point);
        bool IsMouseOnTaskBoard(CPoint point);
        bool IsTaskOnClick(CPoint point);
        bool GetIsOnShow();
        int  GetShowTaskSize();
        int  GetTaskBoardX();
        TaskList GetNowTask();
    private:
        bool IsTaskShow[TaskSize];       //任務是否出現在介面板
        bool IsInterfaceOnShow;
        bool isMouseOn;
        string TaskTitle;
        TaskList nowTask;
        TaskBlock* myTaskBlock[3];
        CInteger*    completionPercent;     //完成度
        CMovingBitmap TaskBoardInterface, TaskBoardImg;
        CMovingBitmap TaskInformation;
};
}