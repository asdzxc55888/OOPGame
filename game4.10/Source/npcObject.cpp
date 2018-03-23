#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "npcObject.h"
game_framework::npcObject::npcObject()
{
	for (int i = 0; i < 4; i++)
		animation[i] = new CAnimation;
	_x = 0;
	_y = 0;
	isMovingDown =false;			// 是否正在往下移動
	isMovingLeft = false;			// 是否正在往左移動
	isMovingRight = false;			// 是否正在往右移動
	isMovingUp = false;			// 是否正在往上移動
}

game_framework::npcObject::~npcObject()
{
	for (int i = 0; i < 4;i++)delete animation[i];
}

void game_framework::npcObject::LoadBitmap(string monsterName)
{  
	monsterName += ".bmp";
	string root= "Bitmaps\\monster\\monster_";
	root += monsterName;
	char test[100];
	strcpy(test, root.c_str());
	animation[Forward]->AddBitmap(test, RGB(255, 255, 255));
	root = "Bitmaps\\monster\\monsterBack1_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255,  255));
	root = "Bitmaps\\monster\\monsterBack2_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255, 255));
	root = "Bitmaps\\monster\\monsterLeft1_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255, 255));
	root = "Bitmaps\\monster\\monsterLeft2_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255, 255));
	root = "Bitmaps\\monster\\monsterRight1_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255, 255));
	root = "Bitmaps\\monster\\monsterRight2_" + monsterName;
	strcpy(test, root.c_str());
	animation[Back]->AddBitmap(test, RGB(255, 255, 255));
}

void game_framework::npcObject::OnMove()
{
	
	
}

void game_framework::npcObject::OnShow()
{
	for (int i = 0; i < 4; i++)animation[i]->SetTopLeft(_x, _y);
	animation[0]->OnShow();
}

void game_framework::npcObject::SetPoint(int x, int y)
{
	_x = x;
	_y = y;
}

void game_framework::npcObject::SetMovingRight(bool flag)
{
	_x += 5;
}

void game_framework::npcObject::SetMovingLeft(bool flag)
{
	_x -= 5;
}

void game_framework::npcObject::SetMovingUp(bool flag)
{
	_y -= 5;
}

void game_framework::npcObject::SetMovingDown(bool flag)
{
	_y += 5;
}

int game_framework::npcObject::GetX()
{
	return _x;
}

int game_framework::npcObject::GetY()
{
	return _y;
}

int game_framework::npcObject::GetHp()
{
	return Hp;
}

int game_framework::npcObject::GetApDefense()
{
	return ApDefense;
}

int game_framework::npcObject::GetAdDefense()
{
	return AdDefense;
}

int game_framework::npcObject::GetAttackPower()
{
	return AttackPower;
}

int game_framework::npcObject::GetAttackType()
{
	return AttackType;
}
