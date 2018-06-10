#pragma once
namespace game_framework
{
#define MenuInterface_bg_x 100
#define MenuInterface_bg_y 0
#define MenuConfirm_bg_x 300
#define MenuConfirm_bg_y 250
#define Option_size 3
	class MenuInterface
	{
	public:
		MenuInterface();
		~MenuInterface();
		void Initial();
		void OnShow();
		void LoadBitmap();
		void ShowOptions();                   // 顯示選項
		void ShowConfirmBtn();                // 顯示確認選項
		bool SetIsOnShow(bool flag);          // 若介面關閉回傳ture
		bool IsMouseOn(CPoint point);
		bool IsMouseClick();
		bool GetIsOnShow();
	private:
		CMovingBitmap bg;                     // 背景圖
		CMovingBitmap confirm_bg;             // 確認背景圖
		string confirm_information;           // 確認資訊文字
		string confirm_str[2];                // 確認選項文字 YES NO
		string option_str[Option_size];       // 選項文字
		bool isConfirmOnShow;                 // 確認界面是否顯示
		bool isOnShow;                        // 界面是否顯示
		bool isOptionMouseOn[Option_size];    // 滑鼠是否在選項上
		bool isConfirmBtnMouseOn[2];          // 滑鼠是否在按鈕上
	};
}