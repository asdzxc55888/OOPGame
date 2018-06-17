#pragma once
#include "Room.h"
namespace game_framework
{
#define RoomInterface_bg_x 100
#define RoomInterface_bg_y 0
#define RoomInterface_Increase_x 425
#define RoomInterface_Increase_y 252
#define RoomInterface_Decrease_x 272
#define RoomInterface_Decrease_y 252
#define RoomInterface_Right_x 335
#define RoomInterface_Right_y 70
#define RoomInterface_Left_x 117
#define RoomInterface_Left_y 70
#define RoomInterface_RoomNumber_x 220
#define RoomInterface_RoomNumber_y 85
#define monsterBmp_x 280
#define monsterBmp_y 160
#define RentPercent_x 232
#define RentPercent_y 135
#define RentInt_x 460
#define RemtInt_y 260
#define cancle_x 320
#define cancle_y 160
class RoomInterface
{
    public:
        RoomInterface(Room** gameRoom);
        ~RoomInterface();
        void Initial();
        void OnShow();
        void OnMove();
        void ShowRentBar();
		void ShowConfirm();
        void SetInterfaceShow(bool flag);
        void SetRoomSelector(int index);
        void SetMonsterSelector(int index);
        int  GetRoomSelector();
        bool GetIsShow();
		bool GetIsConfirmOnShow();
        bool IsMouseOn(CPoint point);
        bool IsMouseClick(CPoint point, int monsterIndex);
        bool IsMouseClick(CPoint point);
		int  IsConfirmOnClick();
    private:
        void ResetRent();
        int  RoomSelector;			 // 當前所選擇的房屋
        int  monsterSelector;		 // 當前所選的怪物
        int  rentPercent;			 // 房租百分比
        int  maxPercent;             // 最大房租
		int  monster_count;          // 顯示怪物的計數
		int  leaveMonsterIndex;
		bool isCancleShow;
        bool isOnShow;
        bool isMouseOn;
		bool isConfirmBtnMouseOn[2];
        bool isMouseOnBtn[4];
		bool isConfirmOnShow;
		string confirm_str[2];                // 確認選項文字 YES NO
        CInteger* presentRent;
		CInteger* roomNumber;
		CMovingBitmap confirm_bg;                    // 確認背景圖
        CMovingBitmap bg;                            // 背景圖
        CMovingBitmap Increase_btn, Decrease_btn;    // 房租調整按鍵
        CMovingBitmap Right_btn, Left_btn;           // 房間選擇鈕
        CMovingBitmap* monster[3];                   // 怪物圖
		CMovingBitmap cancle_btn;                    // 驅逐怪物提示圖
        MonsterDataBoard* MonsterBoard;              // 怪物資料欄
        Room** gameRoom;
};

}