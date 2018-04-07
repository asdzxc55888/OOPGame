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
	floor = 0;
    isMovingDown = false;			// �O�_���b���U����
    isMovingLeft = false;			// �O�_���b��������
    isMovingRight = false;			// �O�_���b���k����
    isMovingUp = false;			// �O�_���b���W����
	isIntoHouse = false;
	nowMovingType = Forward;    // �w�]�ʹ�
}

game_framework::npcObject::~npcObject()
{
    for (int i = 0; i < 5; i++)delete animation[i];
}

void game_framework::npcObject::operator=(npcObject obj)
{
	_x = obj._x;
	_y = obj._y;
	Hp=obj.Hp;					//��q
	ApDefense=obj.ApDefense;
	AdDefense = obj.AdDefense;
	AttackPower=obj.AttackPower;        //�����O
	isMovingDown=obj.isMovingDown;			// �O�_���b���U����
	isMovingLeft=obj.isMovingLeft;			// �O�_���b��������
	isMovingRight=obj.isMovingRight;			// �O�_���b���k����
	isMovingUp=obj.isMovingRight;			// �O�_���b���W����
	AttackType=obj.AttackType; //�����Ҧ�
	nowMovingType=obj.nowMovingType;
	for(int i = 0; i <5; i++)animation[i]=obj.animation[i];
}



void game_framework::npcObject::OnMove()
{
	if (isIntoHouse) {      //�Ǫ��i��
		nowMovingType = Back;
		if (!animation[nowMovingType]->IsFinalBitmap()) {
			animation[nowMovingType]->OnMove();        //�Y���O�̫�@�ӹϧΡA�NOnMove��̫�@�ӹϧΫᰱ��C
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

int game_framework::npcObject::GetFloor()
{
	return floor;
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
	return animation[0]->Width();
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


