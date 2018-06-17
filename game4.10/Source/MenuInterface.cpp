#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<fstream>
#include "audio.h"
#include "gamelib.h"
#include "MenuInterface.h"
namespace game_framework
{
MenuInterface::MenuInterface()
{
    Initial();
    isOnShow = false;
}

MenuInterface::~MenuInterface()
{
}

void MenuInterface::Initial()
{
    confirm_str[0] = "確定";
    confirm_str[1] = "取消";
    option_str[0] = "存檔";
    option_str[1] = "讀檔";
    option_str[2] = "離開";

    for (int i = 0; i < Option_size; i++)isOptionMouseOn[i] = false;

    for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;

    for (int i = 0; i < save_size; i++)isSaveMouseOn[i] = false;

    for (int i = 0; i < save_size; i++)isSaveExist[i] = false;

    state = nostate;
    SaveIndexTemp = 0;
    isConfirmOnShow = false;
    isSaveDataOnShow = false;
}

void MenuInterface::OnShow()
{
    if (isOnShow)
    {
        bg.ShowBitmap();
        ShowOptions();

        if (isSaveDataOnShow)
        {
            ShowSave();
        }

        if (isConfirmOnShow)
        {
            confirm_bg.ShowBitmap();
            ShowConfirmBtn();
        }
    }
}

void MenuInterface::LoadBitmap()
{
    bg.LoadBitmap("Bitmaps\\gameRun\\Menu.bmp", RGB(255, 255, 255));
    confirm_bg.LoadBitmap("Bitmaps\\gameRun\\Confirm_bg.bmp", RGB(255, 255, 255));
    bg.SetTopLeft(MenuInterface_bg_x, MenuInterface_bg_y);
    confirm_bg.SetTopLeft(MenuConfirm_bg_x, MenuConfirm_bg_y);
}

void MenuInterface::LoadSaveData()
{
    string fileName[save_size] = { "save1", "save2", "save3", "save4", "save5" };
    char buf[10240];
    char temp[10240];

    for (int i = 0; i < save_size; i++)
    {
        fstream saveFile;
        saveFile.open("Save\\" + fileName[i] + ".txt", ios::in);

        if (saveFile)
        {
            saveFile.read(buf, sizeof(buf));
            strcpy(temp, buf);
            save_str[i] = strtok(temp, "\n");
            isSaveExist[i] = true;
            saveFile.close();
        }
        else
        {
            save_str[i] = "---------------------";
        }
    }
}

void MenuInterface::ShowOptions()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(200, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(90, 57, 8));

    for (int i = 0; i < Option_size; i++)
    {
        if (isOptionMouseOn[i])
        {
            pDC->SetTextColor(RGB(238, 216, 17));
        }
        else
        {
            pDC->SetTextColor(RGB(254, 254, 250));
        }

        char str[80];								// Demo 數字對字串的轉換
        sprintf(str, option_str[i].c_str());
        pDC->TextOut(MenuInterface_bg_x + 80, MenuInterface_bg_y + 275 + (i * 80), str);
    }

    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void MenuInterface::ShowConfirmBtn()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, t, *fp;
    t.CreatePointFont(160, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&t);					// 選用 font f
    pDC->SetBkColor(RGB(171, 208, 107));
    pDC->SetTextColor(RGB(254, 254, 200));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, confirm_information.c_str());
    pDC->TextOut(MenuConfirm_bg_x + 80, MenuConfirm_bg_y + 60, str);
    f.CreatePointFont(180, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    pDC->SetBkColor(RGB(171, 208, 107));

    for (int i = 0; i < 2; i++)
    {
        if (isConfirmBtnMouseOn[i])
        {
            pDC->SetTextColor(RGB(238, 216, 17));
        }
        else
        {
            pDC->SetTextColor(RGB(254, 254, 250));
        }

        char str[80];								// Demo 數字對字串的轉換
        sprintf(str, confirm_str[i].c_str());
        pDC->TextOut(MenuConfirm_bg_x + 150 + (i * 222), MenuConfirm_bg_y + 120, str);
    }

    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void MenuInterface::ShowSave()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f,t, *fp;

	t.CreatePointFont(220, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&t);					// 選用 font f
	pDC->SetBkColor(RGB(233, 246, 253));
	pDC->SetTextColor(RGB(33, 33, 33));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, title.c_str());
	pDC->TextOut(MenuInterface_bg_x + 60, MenuInterface_bg_y + 70, str);

    f.CreatePointFont(160, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(247, 173, 84));

    for (int i = 0; i < save_size; i++)
    {
        if (isSaveMouseOn[i])
        {
            pDC->SetTextColor(RGB(238, 216, 17));
        }
        else
        {
            pDC->SetTextColor(RGB(254, 254, 200));
        }
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, save_str[i].c_str());
		pDC->TextOut(MenuInterface_bg_x + 480, MenuInterface_bg_y + 150 + (i * 90), str);
    }
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

bool MenuInterface::ShowConfirm()
{
    if (isConfirmOnShow)             // 離開提醒視窗
    {
        switch (state)
        {
            case game_framework::nostate:
                break;

            case game_framework::Save:
                if (isConfirmBtnMouseOn[0])
                {
                    return true;
                }
                else if (isConfirmBtnMouseOn[1])
                {
                    isConfirmOnShow = false;
                }

                break;

            case game_framework::Load:
                if (isConfirmBtnMouseOn[0])
                {
                    return true;
                }
                else if (isConfirmBtnMouseOn[1])
                {
                    isConfirmOnShow = false;
                }

                break;

            case game_framework::Exit:
                if (isConfirmBtnMouseOn[0])
                {
                    exit(1);
                }
                else if (isConfirmBtnMouseOn[1])
                {
                    isConfirmOnShow = false;
                }

                break;

            default:
                break;
        }
    }

    return false;
}
bool MenuInterface::SetIsOnShow(bool flag)
{
    if (flag)
    {
        LoadSaveData();
        isOnShow = true;
        Initial();
        return true;
    }
    else
    {
        if (isConfirmOnShow)
        {
            isConfirmOnShow = false;
        }
        else if (isSaveDataOnShow)
        {
            isOnShow = flag;
            isSaveDataOnShow = false;
            return true;
        }
        else
        {
            isOnShow = false;
            return true;
        }
    }

    return false;
}
bool MenuInterface::IsMouseOn(CPoint point)
{
    for (int i = 0; i < Option_size; i++)
    {
        int x1 = MenuInterface_bg_x + 90;
        int x2 = x1 + 80;
        int y1 = MenuInterface_bg_y + 275 + (i * 80);
        int y2 = y1 + 50;

        if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
        {
            isOptionMouseOn[i] = true;
            return true;
        }
        else
        {
            isOptionMouseOn[i] = false;
        }
    }

    if (isConfirmOnShow)
    {
        for (int i = 0; i < 2; i++)
        {
            int x1 = MenuConfirm_bg_x + 150 + (i * 222);
            int x2 = x1 + 40;
            int y1 = MenuConfirm_bg_y + 120;
            int y2 = y1 + 40;

            if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
            {
                isConfirmBtnMouseOn[i] = true;
                return true;
            }
            else
            {
                isConfirmBtnMouseOn[i] = false;
            }
        }
    }

    if (isSaveDataOnShow && !isConfirmOnShow)
    {
        for (int i = 0; i < save_size; i++)
        {
            int x1 = MenuInterface_bg_x + 480;
            int x2 = x1 + 400;
            int y1 = MenuInterface_bg_y + 150 + (i * 90);
            int y2 = y1 + 80;

            if (point.x > x1 && point.x <= x2 && point.y > y1 && point.y <= y2)
            {
                isSaveMouseOn[i] = true;
                return true;
            }
            else
            {
                isSaveMouseOn[i] = false;
            }
        }
    }

    return false;
}
bool MenuInterface::IsMouseClick()
{
    if (isOptionMouseOn[0])          // 存檔
    {
        LoadSaveData();
        isSaveDataOnShow = true;
        state = Save;
        title = "存檔中";
        return true;
    }
    else if (isOptionMouseOn[1])     // 讀檔
    {
        LoadSaveData();
        isSaveDataOnShow = true;
        state = Load;
        title = "讀檔中";
        return true;
    }
    else if (isOptionMouseOn[2])     //離開按鈕
    {
        state = Exit;
        isConfirmOnShow = true;
        isSaveDataOnShow = false;
        confirm_information = "未保存的遊戲資料都將消除，是否要離開";

        for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;      //清除按鈕狀態
    }

    ShowConfirm();
    return false;
}
bool MenuInterface::GetIsOnShow()
{
    return isOnShow;
}
bool MenuInterface::GetIsSaveDataOnShow()
{
    return isSaveDataOnShow;
}
int MenuInterface::SaveDataOnClick()
{
    switch (state)
    {
        case game_framework::Save:
            for (int i = 0; i < save_size; i++)
            {
                if (isSaveMouseOn[i])
                {
                    SaveIndexTemp = i;
                    isConfirmOnShow = true;

                    if (isSaveExist[i])
                    {
                        confirm_information = "已有存檔資料，是否要覆蓋?";
                    }
                    else
                    {
                        confirm_information = "儲存目前遊戲檔案?";
                    }
                }
            }

            break;

        case game_framework::Load:
            for (int i = 0; i < save_size; i++)
            {
                if (isSaveMouseOn[i])
                {
                    if (isSaveExist[i])
                    {
                        SaveIndexTemp = i;
                        isConfirmOnShow = true;
                        confirm_information = "未保存的資料都會遺失，確定讀取?";
                    }
                }
            }

            break;

        default:
            break;
    }

    if (ShowConfirm())                        //顯示提示視窗
    {
        isOnShow = false;
        isConfirmOnShow = false;

        for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;

        return SaveIndexTemp + 1;
    }

    for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;

    return 0;
}
Menu_state MenuInterface::GetState()
{
    return state;
}
}