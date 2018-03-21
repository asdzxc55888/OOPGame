#include "stdafx.h"
#include "npcObject.h"

game_framework::npcObject::npcObject()
{
}

game_framework::npcObject::~npcObject()
{
}

void game_framework::npcObject::LoadBitmap()
{

}

void game_framework::npcObject::OnMove()
{
	animation.OnMove();

}

void game_framework::npcObject::OnShow()
{
}

void game_framework::npcObject::SetPoint(int _x, int _y)
{
}

void game_framework::npcObject::SetMovingRight(bool flag)
{
	x += 5;
}

void game_framework::npcObject::SetMovingLeft(bool flag)
{
	x -= 5;
}

void game_framework::npcObject::SetMovingUp(bool flag)
{
	y -= 5;
}

void game_framework::npcObject::SetMovingDown(bool flag)
{
	y += 5;
}

int game_framework::npcObject::GetX()
{
	return x;
}

int game_framework::npcObject::GetY()
{
	return y;
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
