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
        int  RoomSelector;			 // ��e�ҿ�ܪ��Ы�
        int  monsterSelector;		 // ��e�ҿ諸�Ǫ�
        int  rentPercent;			 // �Я��ʤ���
        int  maxPercent;             // �̤j�Я�
		int  monster_count;          // ��ܩǪ����p��
		int  leaveMonsterIndex;
		bool isCancleShow;
        bool isOnShow;
        bool isMouseOn;
		bool isConfirmBtnMouseOn[2];
        bool isMouseOnBtn[4];
		bool isConfirmOnShow;
		string confirm_str[2];                // �T�{�ﶵ��r YES NO
        CInteger* presentRent;
		CInteger* roomNumber;
		CMovingBitmap confirm_bg;                    // �T�{�I����
        CMovingBitmap bg;                            // �I����
        CMovingBitmap Increase_btn, Decrease_btn;    // �Я��վ����
        CMovingBitmap Right_btn, Left_btn;           // �ж���ܶs
        CMovingBitmap* monster[3];                   // �Ǫ���
		CMovingBitmap cancle_btn;                    // �X�v�Ǫ����ܹ�
        MonsterDataBoard* MonsterBoard;              // �Ǫ������
        Room** gameRoom;
};

}