#pragma once
#define TaskContent_x 600
#define TaskContent_y 160
#define TaskName_x 200
#define TaskName_y 200
#define Content_x 200
#define Content_y 200
#define reward_str_x 200
#define reward_str_y 200
namespace game_framework {
	class TaskBlock
	{
	public:
		TaskBlock();
		~TaskBlock();
		void Initial(int Index);
		void LoadBitmap();
		void OnShow();
		void SetPoint(int x,int y);
		void ShowTitle();
		void ShowTaskName();
		void ShowContent();
		void ShowReward_str();
		void IsMouseOn(CPoint point);
	private:
		int x, y;
		bool isMouseOn;
		string TaskName;
		string Content;
		string reward_str;
		CMovingBitmap TaskBlockBackGround;
		CMovingBitmap TaskContentBackGround;            //»¡©ú­I´º
	};
}