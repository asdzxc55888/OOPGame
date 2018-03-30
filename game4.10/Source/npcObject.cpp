#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "npcObject.h"
game_framework::npcObject::npcObject()
{
    for (int i = 0; i < 5; i++)
        animation[i] = new CAnimation;

    _x = 0;
    _y = 530;
    isMovingDown = false;			// 是否正在往下移動
    isMovingLeft = false;			// 是否正在往左移動
    isMovingRight = false;			// 是否正在往右移動
    isMovingUp = false;			// 是否正在往上移動
	isIntoHouse = false;
	nowMovingType = Forward;    // 預設動圖
}

game_framework::npcObject::~npcObject()
{
    for (int i = 0; i < 5; i++)delete animation[i];
}

void game_framework::npcObject::operator=(npcObject obj)
{
	_x = obj._x;
	_y = obj._y;
	Hp=obj.Hp;					//血量
	ApDefense=obj.ApDefense;
	AdDefense = obj.AdDefense;
	AttackPower=obj.AttackPower;        //攻擊力
	isMovingDown=obj.isMovingDown;			// 是否正在往下移動
	isMovingLeft=obj.isMovingLeft;			// 是否正在往左移動
	isMovingRight=obj.isMovingRight;			// 是否正在往右移動
	isMovingUp=obj.isMovingRight;			// 是否正在往上移動
	AttackType=obj.AttackType; //攻擊模式
	nowMovingType=obj.nowMovingType;
	for(int i = 0; i <5; i++)animation[i]=obj.animation[i];
}

void game_framework::npcObject::LoadBitmap(string monsterName)
{
    monsterName += ".bmp";
    string root = "Bitmaps\\monster\\monster_";
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
    animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
    root = "Bitmaps\\monster\\monsterLeft2_" + monsterName;
    strcpy(test, root.c_str());
    animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
    root = "Bitmaps\\monster\\monsterRight1_" + monsterName;
    strcpy(test, root.c_str());
    animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
    root = "Bitmaps\\monster\\monsterRight2_" + monsterName;
    strcpy(test, root.c_str());
    animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
	animation[Hide]->AddBitmap("Bitmaps\\monster\\monsterHide.bmp", RGB(255, 255, 255));
}

void game_framework::npcObject::OnMove()
{
	if (isIntoHouse) {      //怪物進房
		nowMovingType = Back;
		if (!animation[nowMovingType]->IsFinalBitmap()) {
			animation[nowMovingType]->OnMove();        //若不是最後一個圖形，就OnMove到最後一個圖形後停止。
		}
		else {
			nowMovingType = Back;
			animation[nowMovingType]->OnMove();
			if (animation[nowMovingType]->GetCurrentBitmapNumber() == 0) {
				isIntoHouse = false;
				nowMovingType = Hide;
				animation[nowMovingType]->OnMove();
			}
		}
	}
	else {
		if (isMovingDown)
		{

		}
		else if (isMovingUp) {

		}
		else if (isMovingLeft) {
			nowMovingType = Moving_Left;
			_x -= 5;
		}
		else if (isMovingRight) {
			nowMovingType = Moving_Right;
			_x += 5;
		}
		animation[nowMovingType]->OnMove();
	}
}

void game_framework::npcObject::OnShow()
{
    for (int i = 0; i < 4; i++)animation[i]->SetTopLeft(_x, _y);

    animation[nowMovingType]->OnShow();
}

void game_framework::npcObject::SetPoint(int x, int y)
{
    _x = x;
    _y = y;
}

void game_framework::npcObject::SetMovingType(MovingAnimation_Type _MovingType)
{
	nowMovingType = _MovingType;
}

void game_framework::npcObject::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}

void game_framework::npcObject::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}

void game_framework::npcObject::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}

void game_framework::npcObject::SetIntoHouse(bool flag)
{
	isIntoHouse = flag;
}

void game_framework::npcObject::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

int game_framework::npcObject::GetX()
{
    return _x;
}

int game_framework::npcObject::GetY()
{
    return _y;
}

int game_framework::npcObject::GetWidth()
{
	return animation[0]->Width;
}

int game_framework::npcObject::GetHeight()
{
	return animation[0]->Height();
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


