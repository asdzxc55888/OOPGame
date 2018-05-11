#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
namespace game_framework
{
void SetObstacle(Room** gameRoom, Warrior** _warriors, Obstacle* obs, int roomSize)
{
    for (int i = 0; i < roomSize; i++)
    {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetIsMonsterFight(k) && gameRoom[i]->GetLiveMonster(k)->GetMovingType()!=Hide)
			{
				Monster* _monster = gameRoom[i]->GetLiveMonster(k);
				int _x1 = _monster->GetX();
				int _x2 = _monster->GetWidth() + _x1;
				int _y1 = _monster->GetY();
				int _y2 = _monster->GetHeight() + _y1;
				obs->SetXY(_x1, _x2, _y1, _y2);
			}
		}
    }

    for (int i = 0; i < 10; i++)
    {
        if (_warriors[i] != NULL)
        {
            int _x1 = _warriors[i]->GetX();
            int _x2 = _warriors[i]->GetWidth() + _x1;
            int _y1 = _warriors[i]->GetY();
            int _y2 = _warriors[i]->GetHeight() + _y1;
            obs->SetXY(_x1, _x2, _y1, _y2);
        }
    }
}
void MonsterFindHouse(Monster** _monster, int TaskBoard_x, int TaskBoard_Width) //怪物找房
{
    if (Moving(_monster, TaskBoard_x + 60, 0, Obstacle()))
    {
        (*_monster)->SetMovingType(Back);
		int randvalue = rand() % 2000;
		if (randvalue < 20) {
			(*_monster)->SetMonsterState(findHouse);
		}else if (randvalue > 1990 )
		{
			(*_monster)->SetMonsterState(leave);
		}
	}
	else {
		(*_monster)->SetMonsterState(lookHouse);
	}
}
void MonsterlivingHouse_event(Room* _room, Monster** _monster)
{
    _room->SetMonsterlivingRoom(_monster);
}
void MonsterGohome_event(Room* _room,int monsterIndex)
{
    _room->LetMonsterGohome(monsterIndex);
}
void MonsterBeingClick(Monster** _monster, int room_size, Room** gameroom)
{
    Monster_state nowState = (*_monster)->GetMonsterState();

    switch (nowState)
    {
        case game_framework::nothing:

            break;
        case game_framework::findHouse:                   //同意怪物住進防屋
            for (int i = 0; i < room_size; i++)
            {
                if (!(gameroom)[i]->GetIsMonsterLiving())    //沒怪物住的話就分配到那間房
                {
                    MonsterlivingHouse_event((gameroom)[i], _monster);
					(gameroom)[i]->GetLiveMonster(0)->SetMonsterState(nothing);
					MonsterGohome_event(gameroom[i], 0);
                    break;
                }
            }

            break;

        default:
            break;
    }
}
bool MonsterLeave(Monster** _monster)  //已經離開回傳true
{
    if (Moving(_monster, -100, 0, Obstacle()))
    {
        delete *_monster;
        *_monster = NULL;
        return true;
    }

    return false;
}
bool Moving(Monster** _monster, int x, int floor, Obstacle obs = Obstacle())
{
    int Floor_x[3] = { 1150, 750, 1150 };
    int _monsterFloor = (*_monster)->GetFloor();
    int x1 = (*_monster)->GetX();
    int x2 = x1 + (*_monster)->GetWidth();
	bool obsDirection = false,monsterMovingDirection=false; //在左為TRUE 在右為FALSE
    if (obs.isHit(x1, x2, (*_monster)->GetY(), (*_monster)->GetY() + (*_monster)->GetHeight(),&obsDirection))
    {
        if ((x1 > x && x1 <= x + 20) || (x2 > x && x2 <= x + 20) && _monsterFloor == floor)
        {
            return true;       //抵達目的
        }
		if ((*_monster)->GetMovingType() == Moving_Left) {
			monsterMovingDirection = true;
		}
		else {
			monsterMovingDirection = false;
		}
		if (monsterMovingDirection == obsDirection) {
			(*_monster)->SetMovingLeft(false);
			(*_monster)->SetMovingRight(false);
			return false;
		}
    }

    if (_monsterFloor == floor)
    {
        return MovingLR(_monster, x);
    }
    else if (_monsterFloor < floor)                     //上樓
    {
        if (MovingLR(_monster, Floor_x[_monsterFloor]))
        {
            (*_monster)->SetMovingUp(true);
        }
    }
    else                                                //下樓
    {
        if (MovingLR(_monster, Floor_x[_monsterFloor - 1]))
        {
            (*_monster)->SetMovingDown(true);
        }
    }

    return false;
}
bool MovingLR(Monster** _monster, int x)
{
    if ((*_monster)->GetX() > x + 40)
    {
        (*_monster)->SetMovingLeft(true);
        (*_monster)->SetMovingRight(false);
    }
    else if ((*_monster)->GetX() <= x - 40)
    {
        (*_monster)->SetMovingRight(true);
        (*_monster)->SetMovingLeft(false);
    }
    else
    {
        (*_monster)->SetMovingLeft(false);
        (*_monster)->SetMovingRight(false);
        return true;
    }

    return false;
}
void AttackWarrior(Monster* _monster, Warrior** _warrior)
{
}
bool HitWarrior(Monster* _monster, Warrior* _warrior)
{
    return _monster->HitRectangle(_warrior->GetX(), _warrior->GetY(), _warrior->GetX() + _warrior->GetWidth(), _warrior->GetY() - _warrior->GetHeight());
}
void CreateMonster_event(Monster** _monster)
{
    int result = 0;
    result = rand() % 1000;

    if (result < 20)
    {
        (*_monster) = new Monster();
        (*_monster)->LoadBitmap((*_monster)->GetMonsterType());
        (*_monster)->SetMonsterIsExist(true);
        (*_monster)->SetMonsterState(nothing);
        (*_monster)->SetPoint(-100, 530);
    }
}
bool MovingLR(Warrior** _warrior, int x)
{
    if ((*_warrior)->GetX() > x + 40)
    {
        (*_warrior)->SetMovingLeft(true);
        (*_warrior)->SetMovingRight(false);
    }
    else if ((*_warrior)->GetX() <= x - 40)
    {
        (*_warrior)->SetMovingRight(true);
        (*_warrior)->SetMovingLeft(false);
    }
    else
    {
        (*_warrior)->SetMovingLeft(false);
        (*_warrior)->SetMovingRight(false);
        return true;
    }

    return false;
}
bool Moving(Warrior** _warrior, int x, int floor, Obstacle obs = Obstacle())
{
    int Floor_x[3] = { 1150, 750, 1150 };
    int _warriorFloor = (*_warrior)->GetFloor();
    int x1 = (*_warrior)->GetX();
    int x2 = x1 + (*_warrior)->GetWidth();
	bool obsDirection = false, monsterMovingDirection = false; //在左為TRUE 在右為FALSE
    if (obs.isHit(x1, x2, (*_warrior)->GetY(), (*_warrior)->GetY() + (*_warrior)->GetHeight()))
    {
        if ((x1 > x && x1 <= x + 20) || (x2 > x && x2 <= x + 20) && _warriorFloor == floor)   //防卡住
        {
            return true;
        }

		if ((*_warrior)->GetMovingType() == Moving_Left) {
			monsterMovingDirection = true;
		}
		else {
			monsterMovingDirection = false;
		}
		if (monsterMovingDirection == obsDirection) {
			(*_warrior)->SetMovingLeft(false);
			(*_warrior)->SetMovingRight(false);
			return false;
		}
    }

    if (_warriorFloor == floor)
    {
        return MovingLR(_warrior, x);
    }
    else if (_warriorFloor < floor)                      //上樓
    {
        if (MovingLR(_warrior, Floor_x[_warriorFloor]))
        {
            (*_warrior)->SetMovingUp(true);
        }
    }
    else                                                //下樓
    {
        if (MovingLR(_warrior, Floor_x[_warriorFloor - 1]))
        {
            (*_warrior)->SetMovingDown(true);
        }
    }

    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateWarrior_event(Warrior** _warrior, warrior_type type)
{
    (*_warrior) = new Warrior(type);
    (*_warrior)->SetPoint(-100, 540);
}
void DeleteWarrior_event(Warrior** _warrior)
{
    if (*_warrior != NULL)
    {
        delete *_warrior;
        *_warrior = NULL;
    }
}
bool HitMonster(Warrior* _warrior, Monster* _monster)
{
    return _warrior->HitRectangle(_monster->GetX(), _monster->GetY(), _monster->GetX() + _monster->GetWidth(), _monster->GetY() - _monster->GetHeight());
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void WarriorAttack_event(Warrior* _warrior, Monster** target, Obstacle obs)
{
    switch (_warrior->GetAttackType())
    {
        case Ad:
            if (Moving(&_warrior, (*target)->GetX(), (*target)->GetFloor(), obs) || HitMonster(_warrior, (*target)))
            {
                if (_warrior->PhysicalAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth()))
                {
                    (*target)->BeingAttack(_warrior->GetAttackPower(), _warrior->GetAttackType());  //受到攻擊
                    _warrior->SetMovingLeft(false);
                    _warrior->SetMovingRight(false);
                }
            }

            break;

        case Ap:
			int targetX = (*target)->GetX();

			if (_warrior->GetX() > targetX)    // 敵人在左
			{
				targetX += 200;

				if (targetX > 1150)targetX = 1100;

				_warrior->SetMovingType(Moving_Left);
			}
			else                              //敵人在右
			{
				targetX -= 200;

				if (targetX < 50)targetX = 50;

				_warrior->SetMovingType(Moving_Right);
			}

			if (Moving((&_warrior), targetX, (*target)->GetFloor(), obs) || (abs((*target)->GetX() - _warrior->GetX()) < 200 && (*target)->GetFloor() == _warrior->GetFloor()))
			{
				_warrior->SetMovingLeft(false);
				_warrior->SetMovingRight(false);

				if (_warrior->MagicAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth(), _warrior->GetWarriorType()))
				{
					(*target)->BeingAttack(_warrior->GetAttackPower(), _warrior->GetAttackType());  //受到攻擊
				}
			}
			break;
    }
}
void MonsterAttack_event(Monster* _monster, Warrior** target, Obstacle obs)
{
    switch (_monster->GetAttackType())
    {
        case Ad:
            if (Moving((&_monster), (*target)->GetX(), (*target)->GetFloor(), obs) || HitWarrior(_monster, (*target)))
            {
                if (_monster->PhysicalAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth()))
                {
                    (*target)->BeingAttack(_monster->GetAttackPower(), _monster->GetAttackType());  //受到攻擊
                    _monster->SetMovingLeft(false);
                    _monster->SetMovingRight(false);

                    if (!(*target)->GetIsAlive()) DeleteWarrior_event(target); //死亡
                }
            }

            break;

        case Ap:
            int targetX = (*target)->GetX();

            if (_monster->GetX() > targetX)    // 敵人在左
            {
                targetX += 200;

                if (targetX > 1150)targetX = 1100;

                _monster->SetMovingType(Moving_Left);
            }
            else                              //敵人在右
            {
                targetX -= 200;

                if (targetX < 50 )targetX = 50;

                _monster->SetMovingType(Moving_Right);
            }

            if (Moving((&_monster), targetX, (*target)->GetFloor(),obs) || (abs((*target)->GetX() - _monster->GetX()) < 200 && (*target)->GetFloor() == _monster->GetFloor()))
            {
                _monster->SetMovingLeft(false);
                _monster->SetMovingRight(false);

                if (_monster->MagicAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth(), _monster->GetMonsterType()))
                {
                    (*target)->BeingAttack(_monster->GetAttackPower(), _monster->GetAttackType());  //受到攻擊

                    if (!(*target)->GetIsAlive()) DeleteWarrior_event(target); //死亡
                }
            }

            break;
    }
}
void MonsterPositionFix(Room ** gameRoom, Obstacle obs,int roomSize)
{
	for (int i = 0; i < roomSize; i++) {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			Monster *_monster = gameRoom[i]->GetLiveMonster(k);
			int x1= _monster->GetX();
			int x2 = x1 + _monster->GetWidth();
			int y1 = _monster->GetY();
			int y2 = y1 + _monster->GetHeight();
			bool obsDirection = false; //true 為在左
			if(_monster->GetIsOnBattle() && obs.isOverlapping(x1, x2, y1, y2,&obsDirection))
			{
				if (obsDirection) {
					_monster->SetPoint(x1 + 10, y1);
				}else _monster->SetPoint(x1 - 10, y1);
				return;
			}
		}
	}
}
Monster* findMonsterTarget(Warrior* _warrior, Room** gameroom, int room_size)
{
    Monster* result = NULL;
    int minX = 9999;

    for (int i = 0; i < room_size; i++)
    {
		for (int k = 0; k < gameroom[i]->GetLiveMonsterSize(); k++) {
			if ( gameroom[i]->GetLiveMonster(k)->GetIsOnBattle())  //判斷怪物是否正在戰鬥
			{
				int dx = abs(_warrior->GetX() - (gameroom[i]->GetLiveMonster(k))->GetX());          //距離差

				if (gameroom[i]->GetLiveMonster(k)->GetFloor() != _warrior->GetFloor())
				{
					int dFloor = abs(gameroom[i]->GetLiveMonster(k)->GetFloor() - _warrior->GetFloor());   //樓層差
					dx += dFloor * 400;
				}

				if (dx < minX)
				{
					minX = dx;
					result = (gameroom[i]->GetLiveMonster(k));
				}
			}
		}
    }

    return result;
}
Warrior* findWarriorTarget(Monster* _monster, Warrior** _warrior)
{
    Warrior* result = NULL;
    int minX = 9999;

    for (int i = 0; i < 10; i++)
    {
        if (_warrior[i] != NULL)
        {
            int dx = abs(_monster->GetX() - _warrior[i]->GetX());

            if (_monster->GetFloor() != _warrior[i]->GetFloor())
            {
                int dFloor = abs(_monster->GetFloor() - _warrior[i]->GetFloor());   //樓層差
                dx += dFloor * 400;
            }

            if (dx < minX)
            {
                minX = dx;
                result = _warrior[i];
            }
        }
    }

    return result;
}
void BattleEnd(Room** gameRoom, int roomsize)
{
    for (int i = 0; i < roomsize; i++)
    {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())
			{
				gameRoom[i]->LetMonsterGohome(k);
				gameRoom[i]->GetLiveMonster(k)->SetIsOnBattle(false);
			}
		}
    }
}

void BattleTest1(Warrior** _warrior, bool& isIntoBattle, Room** gameRoom)
{
    isIntoBattle = true;
//	CreateWarrior_event(&_warrior[0], villager);
    CreateWarrior_event(&_warrior[1],firemagic);
	for (int i = 0; _warrior[i] != NULL; i++) {
		_warrior[i]->SetPoint(-100-(60*i), 540);
	}
}
void timeControl(int * timelevel, bool isSpeedControlOn[3])
{
	if (isSpeedControlOn[0]) *timelevel = 1;
	if (isSpeedControlOn[1]) *timelevel = 2;
	if (isSpeedControlOn[2]) *timelevel = 3;
}

void ComingMonsterFallInLoveEvent(Monster **_monster, Room ** gameRoom, int roomSize)
{
	for (int i = 0; i < roomSize; i++) {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonsterSize()==1  && (*_monster)->GetMonsterType() == gameRoom[i]->GetLiveMonster(k)->GetMonsterType() && (gameRoom[i]->GetLiveMonster(k)->GetMonsterGender()!= (*_monster)->GetMonsterGender())) {
				MonsterlivingHouse_event(gameRoom[i], _monster);
				gameRoom[i]->GetLiveMonster(gameRoom[i]->GetLiveMonsterSize()-1)->SetMonsterState(fallInLove);
				MonsterGohome_event(gameRoom[i], 1);
				return;
			}
		}
	}
}

void MonsterMatingEvent(Room ** gameRoom, int roomSize)
{
	for(int i=0;i<roomSize;i++)
	{
		int randValue = rand() % 1000;
		if (randValue<2 && gameRoom[i]->GetLiveMonsterSize() == 2 && gameRoom[i]->GetIsMonsterIn(0) && gameRoom[i]->GetIsMonsterIn(1)) {
			gameRoom[i]->GetLiveMonster(0)->SetMonsterState(fallInLove);
			gameRoom[i]->GetLiveMonster(0)->SetTimecount(0);
			int childRandvalue= rand() % 1000;
			if (childRandvalue < 500)MonsterBorn(&gameRoom[i],roomSize);  //怪物出生
		}
	}
}

void MonsterBorn(Room ** gameRoom, int roomSize)
{
	Monster *newMonster;
	newMonster = new Monster((*gameRoom)->GetLiveMonster(0)->GetMonsterType());
	newMonster->SetIsChild(true);
	newMonster->LoadBitmap(newMonster->GetMonsterType());
	newMonster->SetMonsterIsExist(false);
	newMonster->SetMonsterState(nothing);

	(*gameRoom)->SetMonsterlivingRoom(&newMonster);
	(*gameRoom)->GetLiveMonster(2)->SetPoint((*gameRoom)->GetX(), (*gameRoom)->GetLiveMonster(2)->GetY()+20); //高度修正
	(*gameRoom)->GetLiveMonster(2)->SetIsGoOutside(false);
	(*gameRoom)->GetLiveMonster(2)->SetMovingType(Hide);
	(*gameRoom)->SetIsMonsterIn(true, 2);
}

}