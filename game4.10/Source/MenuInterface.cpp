#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "MenuInterface.h"
namespace game_framework
{
	MenuInterface::MenuInterface()
	{
		Initial();
	}

	MenuInterface::~MenuInterface()
	{
	}

	void MenuInterface::Initial()
	{
		confirm_str[0] = "�T�w";
		confirm_str[1] = "����";
		option_str[0] = "�s��";
		option_str[1] = "Ū��";
		option_str[2] = "���}";
		for (int i = 0; i < Option_size; i++)isOptionMouseOn[i] = false; 
		for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;
		isOnShow = false;
		isConfirmOnShow = false;
	}

	void MenuInterface::OnShow()
	{
		if (isOnShow) 
		{
			bg.ShowBitmap();
			ShowOptions();
			if (isConfirmOnShow)
			{
				confirm_bg.ShowBitmap();
				ShowConfirmBtn();
			}
		}
	}

	void MenuInterface::LoadBitmap()
	{
		bg.LoadBitmap("Bitmaps\\gameRun\\Menu.bmp",RGB(255,255,255));
		confirm_bg.LoadBitmap("Bitmaps\\gameRun\\Confirm_bg.bmp", RGB(255, 255, 255));
		bg.SetTopLeft(MenuInterface_bg_x, MenuInterface_bg_y);
		confirm_bg.SetTopLeft(MenuConfirm_bg_x, MenuConfirm_bg_y);
	}

	void MenuInterface::ShowOptions()
	{
		for (int i = 0; i < Option_size; i++)
		{
			CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
			CFont f, *fp;
			f.CreatePointFont(200, "Yu Gothic UI Semibold");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(RGB(90, 57, 8));

			if (isOptionMouseOn[i])
			{
				pDC->SetTextColor(RGB(238, 216, 17));
			}
			else
			{
				pDC->SetTextColor(RGB(254, 254, 250));
			}

			char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
			sprintf(str, option_str[i].c_str());
			pDC->TextOut(MenuInterface_bg_x + 80, MenuInterface_bg_y + 275 + (i * 80), str);
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}
	}

	void MenuInterface::ShowConfirmBtn()
	{
		for (int i = 0; i < 2; i++)
		{
			CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
			CFont f, *fp;
			f.CreatePointFont(180, "Yu Gothic UI Semibold");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(RGB(171, 208, 107));

			if (isConfirmBtnMouseOn[i])
			{
				pDC->SetTextColor(RGB(238, 216, 17));
			}
			else
			{
				pDC->SetTextColor(RGB(254, 254, 250));
			}

			char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
			sprintf(str, confirm_str[i].c_str());
			pDC->TextOut(MenuConfirm_bg_x + 150 + (i * 222), MenuConfirm_bg_y + 120, str);
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(140, "Yu Gothic UI Semibold");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(171, 208, 107));
		pDC->SetTextColor(RGB(254, 254, 200));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, confirm_information.c_str());
		pDC->TextOut(MenuConfirm_bg_x + 80 , MenuConfirm_bg_y + 60, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	bool MenuInterface::SetIsOnShow(bool flag)
	{
		if (!flag && isConfirmOnShow) {
			isConfirmOnShow = false;
		}
		else 
		{
			isOnShow = flag;
			return true;
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
			for (int i = 0; i < Option_size; i++)
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

		return false;
	}

	bool MenuInterface::IsMouseClick()
	{
		if (isOptionMouseOn[0]) 
		{

		}
		else if (isOptionMouseOn[1])
		{

		}
		else if (isOptionMouseOn[2])     //���}���s
		{
			isConfirmOnShow = true;
			confirm_information = "���O�s���C����Ƴ��N�����A�O�_�n���}";
			for (int i = 0; i < 2; i++)isConfirmBtnMouseOn[i] = false;      //�M�����s���A
		}

		if (isConfirmOnShow)
		{
			if (isConfirmBtnMouseOn[0]) {
				exit(1);
			}
			else if (isConfirmBtnMouseOn[1])
			{
				isConfirmOnShow = false;
			}
		}
		return false;
	}

	bool MenuInterface::GetIsOnShow()
	{
		return isOnShow;
	}

}