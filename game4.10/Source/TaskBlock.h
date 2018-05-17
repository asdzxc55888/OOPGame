#pragma once

namespace game_framework {
	class TaskBlock
	{
	public:
		TaskBlock();
		~TaskBlock();
		void LoadBitmap();
		void OnShow();
		void SetPoint(int x,int y);
		void ShowTaskName();
	private:
		int x, y;
		string TaskName;
		string Content;
		string reward_str;
		CMovingBitmap BackGround;
	};
}