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
        void SetTaskShow(TaskList _task, bool flag);     //�]�w�����W������
        void SetNowTask(TaskList _task);
        void SetCompletionPercent(int percent);                                //�]�w���ȧ�����
        void ShowTaskName();
        bool OnRButtonDown(UINT nFlags, CPoint point);
        bool IsMouseOnTaskBoard(CPoint point);
        bool IsTaskOnClick(CPoint point);
        bool GetIsOnShow();
        int  GetShowTaskSize();
        int  GetTaskBoardX();
        TaskList GetNowTask();
    private:
        bool IsTaskShow[TaskSize];       //���ȬO�_�X�{�b�����O
        bool IsInterfaceOnShow;
        bool isMouseOn;
        string TaskTitle;
        TaskList nowTask;
        TaskBlock* myTaskBlock[3];
        CInteger*    completionPercent;     //������
        CMovingBitmap TaskBoardInterface, TaskBoardImg;
        CMovingBitmap TaskInformation;
};
}