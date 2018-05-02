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
		Initial();
	}
	Room::~Room()
	{
	}
	void Room::LoadBitmap()
	{
		animation.AddBitmap("Bitmaps\\gameRun\\room.bmp", RGB(255, 255, 255));
		animation.AddBitmap("Bitmaps\\gameRun\\room1.bmp", RGB(255, 255, 255));
	}
	void Room::Initial()
	{
		for (int i = 0; i < 3;i++)liveMonster[i] = NULL;
		floor = 0; 
		liveMonsterSize = 0;
		isDoorOpen = false;
		isMonsterLiving = false;
		for (int i = 0; i < 3; i++) isMonsterIn[i] = false;
		for (int i = 0; i < 3;i++) isMonsterGoHome[i] = false;
		for (int i = 0; i < 3; i++) isMonsterFight[i] = false;
		animation.SetDelayCount(10);
	}
	void Room::OnShow(bool flag)  //true ��������� false�����Ǫ����
	{
		if (flag) {
			animation.SetTopLeft(_x, _y);
			animation.OnShow();
		}
		else {
			for (int i = 0; i < liveMonsterSize;i++)if (liveMonster[i] != NULL)liveMonster[i]->OnShow();  //�Ǫ��s�b�a�ϤW�P�_
		}


	}
	void Room::OnMove()
	{
		for (int i = 0; i < liveMonsterSize; i++) {
			if (isMonsterGoHome[i])isMonsterGoHome[i] = MonsterGoHome(i);// �Ǫ��^�a����
		}

		for (int i = 0; i < liveMonsterSize; i++)if (liveMonster[i]!=NULL)liveMonster[i]->OnMove();

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
	Monster* Room::GetLiveMonster(int index)
	{
		return liveMonster[index];
	}
	bool Room::GetIsMonsterLiving()
	{
		return isMonsterLiving;
	}
	bool Room::GetIsMonsterIn(int monsterIndex)
	{
		return isMonsterIn[monsterIndex];
	}
	bool Room::GetIsMonsterFight(int monsterIndex)
	{
		return isMonsterFight[monsterIndex];
	}
	int Room::GetLiveMonsterSize()
	{
		return liveMonsterSize;
	}
	void Room::LetMonsterGohome(int MonsterIndex)
	{
		isMonsterGoHome[MonsterIndex] = true;
		isMonsterLiving = true;
	}
	bool Room::IsMouseOn(CPoint point)
	{
		if (point.x > _x && point.x <= _x + animation.Width() && point.y > _y && point.y <= _y + animation.Height()) {
			return true;
		}
		return false;
	}
	bool Room::MovingLR(int x,int MonsterIndex)
	{
		if (liveMonster[MonsterIndex]->GetX() > x -40)
		{
			liveMonster[MonsterIndex]->SetMovingLeft(true);
			liveMonster[MonsterIndex]->SetMovingRight(false);
		}
		else if (liveMonster[MonsterIndex]->GetX() <= x -45)
		{
			liveMonster[MonsterIndex]->SetMovingRight(true);
			liveMonster[MonsterIndex]->SetMovingLeft(false);
		}
		else
		{
			liveMonster[MonsterIndex]->SetMovingLeft(false);
			liveMonster[MonsterIndex]->SetMovingRight(false);
			return true;
		}
		return false;
	}
	void Room::MonsterDeath(int monsterIndex)
	{
		delete liveMonster[monsterIndex];
		liveMonster[monsterIndex] = NULL;
		liveMonsterSize--;
		isMonsterFight[monsterIndex] = false;
		isMonsterIn[monsterIndex] = false;
		isMonsterGoHome[monsterIndex] = false;
		if (liveMonsterSize > 0) {
			ResortLiveMonster();
		}
		else {
			isMonsterLiving = false;
		}
	}
	void Room::SetMonsterFight(bool flag)
	{
		for (int i = 0; i < liveMonsterSize;i++)isMonsterFight[i] = flag;
		for (int i = 0; i < liveMonsterSize;i++)isMonsterIn[i] = false;
		isDoorOpen = true;
		for (int i = 0; i < liveMonsterSize; i++) {
			liveMonster[i]->SetIsGoOutside(true);
			liveMonster[i]->SetBattleTemp(true);
		}
	}
	void Room::SetIsMonsterIn(bool flag,int monsterIndex)
	{
		isMonsterIn[monsterIndex] = flag;
	}
	void Room::SetMonsterIntohome(int monsterIndex) //�Ǫ���F���᪺�ʧ@
	{
		liveMonster[monsterIndex]->SetIntoHouse(true);
		isMonsterIn[monsterIndex] = true;
		isDoorOpen = true;
		isMonsterFight[monsterIndex] = false;
	}
	void Room::ResortLiveMonster()
	{
		for (int i = 0; i < 2; i++) {
			if (liveMonster[i] == NULL) {
				for (int k = i+1; k < 3; k++) {
					if (liveMonster[k] != NULL) {
						liveMonster[i] = liveMonster[k];
						liveMonster[k] = NULL;
						break;
					}
				}
			}
		}
	}
	bool Room::MonsterGoHome(int monsterIndex)  //���Ǫ����ʦ^�a
	{
		int Floor_x[3] = { 1150,750,1150 };
		int _monsterFloor = liveMonster[monsterIndex]->GetFloor();
		if (_monsterFloor == floor)
		{
			if (MovingLR(_x+40,monsterIndex)) {
				SetMonsterIntohome(monsterIndex);
				isMonsterGoHome[monsterIndex] = false;
				return false;
			}
		}
		else if (_monsterFloor<floor) {                      //�W��
			if (MovingLR(Floor_x[_monsterFloor],monsterIndex)) {
				liveMonster[monsterIndex]->SetMovingUp(true);
			}
		}
		else {                                              //�U��
			if (MovingLR(Floor_x[_monsterFloor - 1],monsterIndex)) {
				liveMonster[monsterIndex]->SetMovingDown(true);
			}
		}
		return true;
	}
	void Room::SetMonsterlivingRoom(Monster** _monster)
	{
		if (liveMonsterSize >= 3)return;
		liveMonster[liveMonsterSize++] = *_monster;
		*_monster = NULL;
	}
}