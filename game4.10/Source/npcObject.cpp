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
	for (int i = 0; i < 3; i++) {
		magicAttack[i] = NULL;
	}
	
	movingSpeed = 5;
    _x = 0;
    _y = 530;
	floor = 0;
    isMovingDown = false;			// �O�_���b���U����
    isMovingLeft = false;			// �O�_���b��������
    isMovingRight = false;			// �O�_���b���k����
    isMovingUp = false;			// �O�_���b���W����
	isIntoHouse = false;
	isGoOutside = false;
	isAlive = true;
	isFirstShot = true;
	isOnBattle = false;
	nowMovingType = Forward;    // �w�]�ʹ�
}

game_framework::npcObject::~npcObject()
{
    for (int i = 0; i < 7; i++)delete animation[i];
	for (int i = 0; i < 3; i++)delete magicAttack[i];
}

void game_framework::npcObject::operator=(npcObject obj)
{
}

void game_framework::npcObject::OnMove()
{
	if (isIntoHouse) {      //�Ǫ��i��
		if (isOnBattle) {
			BattleTemp = true;        //�԰��w��
			isOnBattle = false;
		}
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
				if (isMovingDown) {                      //�U�Ӱʵe
					_y += 100;
					isMovingDown = false;
					nowMovingType = Forward;
					animation[nowMovingType]->OnMove();
					isGoOutside = true;
				}
				else if (isMovingUp) {                  //�W�Ӱʵe
					_y -= 100;
					isMovingUp = false;
					nowMovingType = Forward;
					animation[nowMovingType]->OnMove();
					isGoOutside = true;
				}
				
			}
		}
	}
	else if (isGoOutside) {                         //�X���ʵe
		if (abs(time(&nowTime) - setTime)>=2) {
			nowMovingType = Forward;
			isGoOutside = false;
			if(BattleTemp=true)isOnBattle = true;
			animation[nowMovingType]->OnMove();
		}
		else if (abs(time(&nowTime) - setTime) >= 1) {
			nowMovingType = Forward;
			animation[nowMovingType]->OnMove();
		}
		else {
			nowMovingType = Hide;
			animation[nowMovingType]->OnMove();
		}
	}
	else {
		if (isMovingDown)
		{
			isIntoHouse = true;
			floor -= 1;
		}
		else if (isMovingUp) {
			isIntoHouse = true;
			floor += 1;
		}
		else if (isMovingLeft) {
			nowMovingType = Moving_Left;
			_x -= movingSpeed;
		}
		else if (isMovingRight) {
			nowMovingType = Moving_Right;
			_x += movingSpeed;
		}
		animation[nowMovingType]->OnMove();
	}
	for (int i = 0; i < 3; i++) {
		if (magicAttack[i] != NULL) {
			magicAttack[i]->OnMove();
		}
	}
}

void game_framework::npcObject::OnShow()
{
	if (isAlive) {
		for (int i = 0; i < 7; i++)animation[i]->SetTopLeft(_x, _y);

		animation[nowMovingType]->OnShow();
	}
	for (int i = 0; i < 3; i++) {
		if (magicAttack[i] != NULL) {
			magicAttack[i]->OnShow();
		}
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

void game_framework::npcObject::SetIsGoOutside(bool flag)
{
	time(&setTime);//�]�m�X�ήɶ�
	isGoOutside = flag;
}

void game_framework::npcObject::SetIsAlive(bool flag)
{
	isAlive = flag;
}

void game_framework::npcObject::SetIsOnBattle(bool flag)
{
	isOnBattle = flag;
}

void game_framework::npcObject::SetBattleTemp(bool flag)
{
	BattleTemp = flag;
}

bool game_framework::npcObject::MagicAttack_event(int target_x1, int target_x2,string type)
{
	/////////////////////////////////////////////////////////////////////�гy�]�k����
	int i = 0;
	while (magicAttack[i] != NULL)
	{
		i++;
		if (i > 3) return false;
	}

	if (isFirstShot || time(&nowTime) - setTime > 1) {
		magicAttack[i] = new MagicAttack(_x, _y+10, AttackPower, type);
		magicAttack[i]->SetTarget(target_x1, target_x2);
		if (target_x1 < _x) {
			magicAttack[i]->SetDirection(Left);
		}
		else {
			magicAttack[i]->SetDirection(Right);
		}
		time(&setTime);
		isFirstShot = false;
	}
	//////////////////////////////////////////////////////////////////////////�P�_�O�_����
	for (int k = 0; k < 3; k++) {         
		if (magicAttack[k] != NULL) {
			if (magicAttack[k]->HitTarget()) {
				delete magicAttack[k];
				magicAttack[k]=NULL;
				return true;
			}
			else {
			//	magicAttack[i]->SetTarget(target_x1, target_x2);
			}
		}
	}
	return false;
}

bool game_framework::npcObject::PhysicalAttack_event(int tar_x1,int tar_x2)
{
	if (isFirstShot || time(&nowTime) - setTime > 1) {
		if (tar_x1 > _x)
		{
			SetMovingType(Attack_Right);
		}
		else
		{
			SetMovingType(Attack_Left);
		}
		isFirstShot = false;
		time(&setTime);
		return HitRectangle(tar_x1, 0, tar_x2, 0);
	}
	return false;
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
	if (Hp <= 0) {
		isAlive = false;
	}
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

bool game_framework::npcObject::GetIsOnBattle()
{
	return isOnBattle;
}

bool game_framework::npcObject::GetIsAlive()
{
	return isAlive;
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


