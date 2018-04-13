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
		floor = 0;
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
	bool Room::MovingLR(int x)
	{
		if (liveMonster.GetX() > x -30)
		{
			liveMonster.SetMovingLeft(true);
			liveMonster.SetMovingRight(false);
		}
		else if (liveMonster.GetX() <= x -40)
		{
			liveMonster.SetMovingRight(true);
			liveMonster.SetMovingLeft(false);
		}
		else
		{
			liveMonster.SetMovingLeft(false);
			liveMonster.SetMovingRight(false);
			return true;
		}
		return false;
	}
	void Room::SetMonsterFight(bool flag)
	{
		isMonsterFight = flag;
		isMonsterIn = false;
		isDoorOpen = true;
		liveMonster.SetIsGoOutside(true);
		liveMonster.SetBattleTemp(true);
	}
	void Room::SetIsMonsterIn(bool flag)
	{
		isMonsterIn = flag;
	}
	void Room::SetMonsterIntohome() //怪物到達門後的動作
	{
		liveMonster.SetIntoHouse(true);
		isMonsterIn = true;
		isDoorOpen = true;
	}
	bool Room::MonsterGoHome()  //讓怪物移動回家
	{
		int Floor_x[3] = { 1150,750,1150 };
		int _monsterFloor = liveMonster.GetFloor();
		if (_monsterFloor == floor)
		{
			if (MovingLR(_x+40)) {
				SetMonsterIntohome();
				isMonsterGoHome = false;
				return false;
			}
		}
		else if (_monsterFloor<floor) {                      //上樓
			if (MovingLR(Floor_x[_monsterFloor])) {
				liveMonster.SetMovingUp(true);
			}
		}
		else {                                              //下樓
			if (MovingLR(Floor_x[_monsterFloor - 1])) {
				liveMonster.SetMovingDown(true);
			}
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