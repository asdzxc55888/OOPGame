#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "npcObject.h"
game_framework::npcObject::npcObject()
{
    for (int i = 0; i < 7; i++)
        animation[i] = new CAnimation;

    _x = 0;
    _y = 530;
	floor = 0;
    isMovingDown = false;			// �O�_���b���U����
    isMovingLeft = false;			// �O�_���b��������
    isMovingRight = false;			// �O�_���b���k����
    isMovingUp = false;			// �O�_���b���W����
	isIntoHouse = false;
	isAlive = true;
	nowMovingType = Forward;    // �w�]�ʹ�
}

game_framework::npcObject::~npcObject()
{
    for (int i = 0; i < 7; i++)delete animation[i];
}

void game_framework::npcObject::operator=(npcObject obj)
{
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
	if (isAlive) {
		for (int i = 0; i < 7; i++)animation[i]->SetTopLeft(_x, _y);

		animation[nowMovingType]->OnShow();
	}
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

void game_framework::npcObject::SetIsAlive(bool flag)
{
	isAlive = flag;
}

void game_framework::npcObject::BeingAttack(int damge, Attack_Type type)
{
	int HpDamge = 0;
	switch (type)
	{
	case game_framework::Ad:
		HpDamge = damge - AdDefense;
		break;
	case game_framework::Ap:
		HpDamge = damge - ApDefense;
		break;
	default:
		break;
	}
	if (HpDamge <= 0) {
		HpDamge = 1;
	}
	Hp -= HpDamge;
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

game_framework::Attack_Type game_framework::npcObject::GetAttackType()
{
    return AttackType;
}

bool game_framework::npcObject::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	int x1 = _x ;				// �y�����W��x�y��
	int y1 = _y ;				// �y�����W��y�y��
	int x2 = x1 + animation[0]->Width();	// �y���k�U��x�y��
	int y2 = y1 + animation[0]->Height();	// �y���k�U��y�y��
								//
								// �˴��y���x�λP�ѼƯx�άO�_���涰
								//
	return (tx2 >= x1 && tx1 <= x2);
}


