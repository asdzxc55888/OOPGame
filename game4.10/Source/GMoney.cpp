#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<iostream>
#include<fstream>
#include<vector>
#include "audio.h"
#include "gamelib.h"
#include "GMoney.h"
namespace game_framework {
	GMoney::GMoney()
	{
		value = 0;
		Initial();
	}
	GMoney::~GMoney()
	{
		delete money;
	}
	void GMoney::Initial()
	{
		x = 250;
		y = 700;
		money = new CInteger(GetDigit(value));
		money->SetIsBmpLoaded();
		money->SetInteger(value);
	}
	void GMoney::OnShow()
	{
		money->ShowBitmap();
	}
	void GMoney::OnMove()
	{
		int digit = GetDigit(value);
		money->SetTopLeft(Money_x-digit*11, Money_y);
	}
	void GMoney::SetValue(int _value)
	{
		delete money;
		value = _value;
		money = new CInteger(GetDigit(value));
		money->SetIsBmpLoaded();
		money->SetInteger(value);
	}
	int GMoney::GetValue()
	{
		return value;
	}
	int GMoney::GetDigit(int x)
	{
		int result = 0;
		while (x > 0) {
			x /= 10;
			result++;
		}
		return result;
	}
}