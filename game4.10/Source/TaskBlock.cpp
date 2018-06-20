#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<iostream>
#include<fstream>
#include "audio.h"
#include "gamelib.h"
#include "stdafx.h"
#include "TaskBlock.h"

namespace game_framework
{
TaskBlock::TaskBlock()
{
    isMouseOn = false;
    isMusicEffectOn = false;
    state = normal;
}
TaskBlock::~TaskBlock()
{
}
void TaskBlock::Initial(int Index)
{
    char line[50] = "";
    int count = 0;
    vector<string> Data;       //名稱 內容 獎勵
    fstream nameFile;
    nameFile.open("Source\\TaskContent.txt", ios::in);

    while (nameFile.getline(line, sizeof(line), '\n'))
    {
        if (atoi(line) == Index)
        {
            for (int i = 0; i < 3; i++)
            {
                nameFile.getline(line, sizeof(line), '!');
                Data.push_back(line);
            }

            break;
        }
    }
	
	thisTask = (TaskList)Index;
    TaskName = Data[0];
    Content = Data[1];
    reward_str = Data[2];
    TaskContentBackGround.SetTopLeft(TaskContent_x, TaskContent_y);
}
void TaskBlock::LoadBitmap()
{
    TaskBlockBackGround[0].LoadBitmap("Bitmaps\\TaskBlock.bmp", RGB(255, 255, 255));
    TaskBlockBackGround[1].LoadBitmap("Bitmaps\\Tasking.bmp", RGB(255, 255, 255));
    TaskContentBackGround.LoadBitmap("Bitmaps\\Instruction.bmp", RGB(255, 255, 255));
}
void TaskBlock::OnShow()
{
    TaskBlockBackGround[state].SetTopLeft(x, y);
    TaskBlockBackGround[state].ShowBitmap();

    if (isMouseOn)
    {
        TaskBlockBackGround[state].SetTopLeft(x - 7, y );
        TaskBlockBackGround[state].ShowBitmap(1.05);
        TaskContentBackGround.ShowBitmap();
        ShowTaskName();
        ShowContent();
        ShowReward_str();

        if (!isMusicEffectOn)
        {
            CAudio::Instance()->Play(AUDIO_DING);
            isMusicEffectOn = true;
        }
    }
    else
    {
        isMusicEffectOn = false;
    }

    ShowTitle();
}
void TaskBlock::SetPoint(int _x, int _y)
{
    x = _x;
    y = _y;
    TaskBlockBackGround[0].SetTopLeft(x, y);
}
void TaskBlock::SetTaskState(TaskState _state)
{
    state = _state;
}
void TaskBlock::ShowTitle()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;

    if (isMouseOn)
    {
        f.CreatePointFont(180, "Yu Gothic UI Semibold");
    }
    else f.CreatePointFont(160, "Yu Gothic UI Semibold");

    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(156, 123, 66));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, TaskName.c_str());
    pDC->TextOut(x + 20, y + 10, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void TaskBlock::ShowTaskName()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(140, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(224, 223, 210));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, TaskName.c_str());
    pDC->TextOut(TaskName_x, TaskName_y, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void TaskBlock::ShowContent()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(140, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(224, 223, 210));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, Content.c_str());
    pDC->TextOut(Content_x, Content_y, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void TaskBlock::ShowReward_str()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(140, "Yu Gothic UI Semibold");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(224, 223, 210));
    pDC->SetTextColor(RGB(0, 0, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, reward_str.c_str());
    pDC->TextOut(reward_str_x, reward_str_y, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}
void TaskBlock::IsMouseOn(CPoint point)
{
    if (point.x > x && point.x <= x + TaskBlockBackGround[0].Width() && point.y > y && point.y <= y + TaskBlockBackGround[0].Height())
    {
        isMouseOn = true;
    }
    else
    {
        isMouseOn = false;
    }
}
bool TaskBlock::IsMouseClick(CPoint point)
{
    if (point.x > x && point.x <= x + TaskBlockBackGround[0].Width() && point.y > y && point.y <= y + TaskBlockBackGround[0].Height())
    {
        CAudio::Instance()->Play(AUDIO_DECISION);
        TaskBlockBackGround[0].SetTopLeft(x + 5, y + 5);
        isMouseOn = true;
        return true;
    }
    else
    {
        isMouseOn = false;
        return false;
    }
}
string TaskBlock::GetTaskName()
{
    return TaskName;
}
TaskList TaskBlock::GetTask()
{
	return thisTask;
}
}