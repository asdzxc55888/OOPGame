#pragma once
namespace game_framework
{
#define LoadInterface_bg_x 150
#define LoadInterface_bg_y 30
#define Save_size 5               //�s�ɭӼ�
class LoadInterface
{
    public:
        LoadInterface();
        ~LoadInterface();
        void Initial();
        void LoadBitmap();
        void OnShow();
        bool MouseOn(CPoint point);
        void ShowSave();
        void LoadSaveData();
        int OnClick(CPoint point);   //�^�ǻ��X�Ӧs��
    private:
        CMovingBitmap bg;   //�I����
        string save_str[Save_size];
        bool isSaveMouseOn[Save_size];
        bool isSaveExist[Save_size];
        bool isMusicOn;
};

}