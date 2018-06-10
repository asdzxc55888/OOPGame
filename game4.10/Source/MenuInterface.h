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
		void ShowOptions();                   // ��ܿﶵ
		void ShowConfirmBtn();                // ��ܽT�{�ﶵ
		bool SetIsOnShow(bool flag);          // �Y���������^��ture
		bool IsMouseOn(CPoint point);
		bool IsMouseClick();
		bool GetIsOnShow();
	private:
		CMovingBitmap bg;                     // �I����
		CMovingBitmap confirm_bg;             // �T�{�I����
		string confirm_information;           // �T�{��T��r
		string confirm_str[2];                // �T�{�ﶵ��r YES NO
		string option_str[Option_size];       // �ﶵ��r
		bool isConfirmOnShow;                 // �T�{�ɭ��O�_���
		bool isOnShow;                        // �ɭ��O�_���
		bool isOptionMouseOn[Option_size];    // �ƹ��O�_�b�ﶵ�W
		bool isConfirmBtnMouseOn[2];          // �ƹ��O�_�b���s�W
	};
}