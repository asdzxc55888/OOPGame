#pragma once
#define TaskContent_x 600
#define TaskContent_y 160
#define TaskName_x 740
#define TaskName_y 205
#define Content_x 740
#define Content_y 255
#define reward_str_x 740
#define reward_str_y 480
namespace game_framework
{
enum TaskList
{
	nothing_task,
    FirstTask,
    eggComing,
    Boss
};
enum TaskState
{
    normal,
    doing,
    finish
};
class TaskBlock
{
    public:
        TaskBlock();
        ~TaskBlock();
        void Initial(int Index);
        void LoadBitmap();
        void OnShow();
        void SetPoint(int x, int y);
        void SetTaskState(TaskState _state);
        void ShowTitle();
        void ShowTaskName();
        void ShowContent();
        void ShowReward_str();
        void IsMouseOn(CPoint point);
        bool IsMouseClick(CPoint point);
        string GetTaskName();
		TaskList GetTask();
    private:
        int x, y;
        bool isMouseOn;
        bool isMusicEffectOn;
        TaskState state;
		TaskList thisTask;                              // 當前方塊任務
        string TaskName;
        string Content;
        string reward_str;
        CMovingBitmap TaskBlockBackGround[3];
        CMovingBitmap TaskContentBackGround;            //說明背景
};
}