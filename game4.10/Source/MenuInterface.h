#pragma once
namespace game_framework
{
#define MenuInterface_bg_x 100
#define MenuInterface_bg_y 0
#define MenuConfirm_bg_x 300
#define MenuConfirm_bg_y 250
#define Option_size 3
#define save_size 5
	enum Menu_state{nostate,Save,Load,Exit};
	class MenuInterface
	{
	public:
		MenuInterface();
		~MenuInterface();
		void Initial();
		void OnShow();
		void LoadBitmap();
		void LoadSaveData();
		void ShowOptions();                   // 顯示選項
		void ShowConfirmBtn();                // 顯示確認選項
		void ShowSave();                      // 顯示存檔
		bool ShowConfirm();                   // 顯示提示窗
		bool SetIsOnShow(bool flag);          // 若介面關閉回傳ture
		bool IsMouseOn(CPoint point);
		bool IsMouseClick();                  // 若點擊存檔或讀檔回傳true，否則回傳false
		bool GetIsOnShow();
		bool GetIsSaveDataOnShow();
		int  SaveDataOnClick();               // 存檔是否被點擊，回傳被點擊的存檔的index
		Menu_state GetState();
	private:
		CMovingBitmap bg;                     // 背景圖
		CMovingBitmap confirm_bg;             // 確認背景圖
		Menu_state state;
		string confirm_information;           // 確認資訊文字
		string confirm_str[2];                // 確認選項文字 YES NO
		string option_str[Option_size];       // 選項文字
		string save_str[save_size];           // 存檔文字
		string title;                         // 選單標題
		bool isSaveMouseOn[save_size];
		bool isSaveExist[save_size];
		bool isConfirmOnShow;                 // 確認界面是否顯示
		bool isOnShow;                        // 界面是否顯示
		bool isSaveDataOnShow;                // 儲存資料使否顯示
		bool isOptionMouseOn[Option_size];    // 滑鼠是否在選項上
		bool isConfirmBtnMouseOn[2];          // 滑鼠是否在按鈕上
		int  SaveIndexTemp;
	};
}