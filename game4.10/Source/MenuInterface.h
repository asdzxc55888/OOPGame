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
		void ShowOptions();                   // ��ܿﶵ
		void ShowConfirmBtn();                // ��ܽT�{�ﶵ
		void ShowSave();                      // ��ܦs��
		bool ShowConfirm();                   // ��ܴ��ܵ�
		bool SetIsOnShow(bool flag);          // �Y���������^��ture
		bool IsMouseOn(CPoint point);
		bool IsMouseClick();                  // �Y�I���s�ɩ�Ū�ɦ^��true�A�_�h�^��false
		bool GetIsOnShow();
		bool GetIsSaveDataOnShow();
		int  SaveDataOnClick();               // �s�ɬO�_�Q�I���A�^�ǳQ�I�����s�ɪ�index
		Menu_state GetState();
	private:
		CMovingBitmap bg;                     // �I����
		CMovingBitmap confirm_bg;             // �T�{�I����
		Menu_state state;
		string confirm_information;           // �T�{��T��r
		string confirm_str[2];                // �T�{�ﶵ��r YES NO
		string option_str[Option_size];       // �ﶵ��r
		string save_str[save_size];           // �s�ɤ�r
		string title;                         // �����D
		bool isSaveMouseOn[save_size];
		bool isSaveExist[save_size];
		bool isConfirmOnShow;                 // �T�{�ɭ��O�_���
		bool isOnShow;                        // �ɭ��O�_���
		bool isSaveDataOnShow;                // �x�s��ƨϧ_���
		bool isOptionMouseOn[Option_size];    // �ƹ��O�_�b�ﶵ�W
		bool isConfirmBtnMouseOn[2];          // �ƹ��O�_�b���s�W
		int  SaveIndexTemp;
	};
}