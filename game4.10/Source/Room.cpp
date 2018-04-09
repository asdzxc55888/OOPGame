#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Room.h"
namespace game_framework
{
	Room::Room(int x, int y) : _x(x), _y(y) //未完成
	{
		counter = 0;
		isDoorOpen = false;
		isMonsterIn = false;
		isMonsterGoHome = false;
		isMonsterLiving = false;
		isMonsterFight = false;
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
	void Room::OnShow(bool flag)  //true 為讓門顯示 false試讓怪物顯示
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
		if (isMonsterGoHome)isMonsterGoHome = MonsterGoHome();// 怪物回家移動
		if (liveMonster.GetIsExist())liveMonster.OnMove();
		if (isDoorOpen) {                           //開關門動畫
			if (!animation.IsFinalBitmap()) {
				animation.OnMove();        //若不是最後一個圖形，就OnMove到最後一個圖形後停止。
				animation.SetDelayCount(50);
				CAudio::Instance()->Play(AUDIO_DOOROPEN);
			}
			else {
				animation.OnMove();
				animation.SetDelayCount(10);
				CAudio::Instance()->Play(AUDIO_DOORCLOSE);
				if (animation.GetCurrentBitmapNumber() == 0)isDoorOpen = false;
			}
		}
	}
	Monster* Room::GetLiveMonster()
	{
		return &liveMonster;
	}
	bool Room::GetIsMonsterLiving()
	{
		return isMonsterLiving;
	}
	bool Room::GetIsMonsterIn()
	{
		return isMonsterIn;
	}
	bool Room::GetIsMonsterFight()
	{
		return isMonsterFight;
	}
	void Room::LetMonsterGohome()
	{
		isMonsterGoHome = true;
		isMonsterLiving = true;
	}
	bool Room::IsMouseOn(CPoint point)
	{
		if (point.x > _x && point.x <= _x + animation.Width() && point.y > _y && point.y <= _y + animation.Height()) {
			return true;
		}
		return false;
	}
	void Room::SetMonsterFight(bool flag)
	{
		isMonsterFight = flag;
	}
	void Room::SetMonsterIntohome() //怪物到達門後的動作
	{
		liveMonster.SetIntoHouse(true);
		isMonsterIn = true;
		isDoorOpen = true;
	}
	bool Room::MonsterGoHome()  //讓怪物移動回家
	{
		if (liveMonster.GetX() >= _x&&liveMonster.GetX() < _x + animation.Width())
		{
			liveMonster.SetMovingLeft(false);
			liveMonster.SetMovingRight(false);
			SetMonsterIntohome();
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
	void Room::SetMonsterlivingRoom(Monster** _monster)
	{
		liveMonster = **_monster;
		delete *_monster;
		*_monster = NULL;
	}
}