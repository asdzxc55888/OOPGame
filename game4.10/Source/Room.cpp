#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Room.h"
namespace game_framework
{
Room::Room(int x, int y): _x(x), _y(y)
{
	counter = 0;
    isDoorOpen = false;
    isMonsterIn = false;
	isMonsterGoHome = false;
	animation.SetDelayCount(10);
}
Room::~Room()
{
}
void Room::LoadBitmap()
{
    animation.AddBitmap("Bitmaps\\gameRun\\room.bmp", RGB(255, 255, 255));
    animation.AddBitmap("Bitmaps\\gameRun\\room1.bmp", RGB(255, 255, 255));
}
void Room::OnShow(bool flag)
{
	if (flag) {
		animation.SetTopLeft(_x, _y);
		animation.OnShow();
	}
	else {
		if (liveMonster.GetIsExist())liveMonster.OnShow();  //怪物存在地圖上與否
	}
    
	
}
void Room::OnMove()
{
	if (isMonsterGoHome)isMonsterGoHome = MonsterGoHome();
	if (liveMonster.GetIsExist())liveMonster.OnMove();
	if (isDoorOpen) {
		if (!animation.IsFinalBitmap()) {
			animation.OnMove();        //若不是最後一個圖形，就OnMove到最後一個圖形後停止。
			animation.SetDelayCount(50);
		}
		else {
			animation.OnMove();
			animation.SetDelayCount(10);
			if (animation.GetCurrentBitmapNumber() == 0)isDoorOpen = false;
		}
	}
}
Monster Room::GetLiveMonster()
{
    return liveMonster;
}
void Room::LetMonsterGohome()
{
	isMonsterGoHome = true;
}
void Room::SetMonsterIntohome(bool flag)
{
	if (flag) {
		liveMonster.SetIntoHouse(true);
	}
	isDoorOpen = flag;
}
bool Room::MonsterGoHome()  //未完成 
{
	if (liveMonster.GetX() >= _x&&liveMonster.GetX() < _x + animation.Width())
	{
		liveMonster.SetMovingLeft(false);
		liveMonster.SetMovingRight(false);
		SetMonsterIntohome(true);
		return false;
	}
	else if (liveMonster.GetX() > _x)
	{
		liveMonster.SetMovingLeft(true);
	}
	else if (liveMonster.GetX() <= _x)
	{
		liveMonster.SetMovingRight(true);
	}
	return true;
}
void Room::SetMonsterIntoRoom(Monster* _monster)
{
    liveMonster = *_monster;
}
}