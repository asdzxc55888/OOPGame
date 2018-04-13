#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Room.h"
namespace game_framework
{
	Room::Room(int x, int y) : _x(x), _y(y) //������
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
	void Room::OnShow(bool flag)  //true ��������� false�����Ǫ����
	{
		if (flag) {
			animation.SetTopLeft(_x, _y);
			animation.OnShow();
		}
		else {
			if (liveMonster.GetIsExist())liveMonster.OnShow();  //�Ǫ��s�b�a�ϤW�P�_
		}


	}
	void Room::OnMove()
	{
		if (isMonsterGoHome)isMonsterGoHome = MonsterGoHome();// �Ǫ��^�a����
		if (liveMonster.GetIsExist())liveMonster.OnMove();
		if (isDoorOpen) {                           //�}�����ʵe
			if (!animation.IsFinalBitmap()) {
				animation.OnMove();        //�Y���O�̫�@�ӹϧΡA�NOnMove��̫�@�ӹϧΫᰱ��C
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
	void Room::SetMonsterIntohome() //�Ǫ���F���᪺�ʧ@
	{
		liveMonster.SetIntoHouse(true);
		isMonsterIn = true;
		isDoorOpen = true;
	}
	bool Room::MonsterGoHome()  //���Ǫ����ʦ^�a
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
		else if (_monsterFloor<floor) {                      //�W��
			if (MovingLR(Floor_x[_monsterFloor])) {
				liveMonster.SetMovingUp(true);
			}
		}
		else {                                              //�U��
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