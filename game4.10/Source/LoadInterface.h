#pragma once
namespace game_framework
{
#define LoadInterface_bg_x 150
#define LoadInterface_bg_y 30
#define Save_size 5               //存檔個數
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
        int OnClick(CPoint point);   //回傳遞幾個存檔
    private:
        CMovingBitmap bg;   //背景圖
        string save_str[Save_size];
        bool isSaveMouseOn[Save_size];
        bool isSaveExist[Save_size];
        bool isMusicOn;
};

}