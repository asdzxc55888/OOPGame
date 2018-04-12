#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "MagicAttack.h"

namespace game_framework {
	MagicAttack::MagicAttack(int _x, int _y, int _damge,string type)
	{
		nowDirection = Left;
		x = _x;
		y = _y;
		tx1 = 0;
		tx2 = 0;
		damge = _damge;
		LoadBitmap(type);
	}
	MagicAttack::~MagicAttack()
	{
	}
	void MagicAttack::SetDirection(Direction _direction)
	{
		nowDirection = _direction;
	}
	void MagicAttack::SetTarget(int _tx1, int _tx2)
	{
		tx1 = _tx1;
		tx2 = _tx2;
	}
	void MagicAttack::LoadBitmap(string type)
	{
		type += ".bmp";
		string root = "Bitmaps\\bullet\\bulletLeft_" + type;
		char test[100];
		strcpy(test, root.c_str());
		bmp[0].LoadBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\bullet\\bulletRight_" + type;
		strcpy(test, root.c_str());
		bmp[1].LoadBitmap(test, RGB(255, 255, 255));
	}
	bool MagicAttack::HitTarget()
	{
		int x1 = x;
		int x2 = x + bmp[0].Width();
		return (tx2-10 >= x1 && tx1+10 <= x2);
	}
	int MagicAttack::GetX()
	{
		return x;
	}
	int MagicAttack::GetY()
	{
		return y;
	}
	int MagicAttack::GetDamge()
	{
		return damge;
	}
	void MagicAttack::OnMove()
	{
		switch (nowDirection)
		{
		case game_framework::Left:
			x -= 10;
			break;
		case game_framework::Right:
			x += 10;
			break;
		}
		bmp[nowDirection].SetTopLeft(x, y);
	}
	void MagicAttack::OnShow()
	{
		switch (nowDirection)
		{
		case game_framework::Left:
			bmp[0].ShowBitmap();
			break;
		case game_framework::Right:
			bmp[1].ShowBitmap();
			break;
		}
	}
}
