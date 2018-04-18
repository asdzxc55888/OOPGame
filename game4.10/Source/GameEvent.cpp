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
        if (gameRoom[i]->GetIsMonsterLiving() && gameRoom[i]->GetIsMonsterFight())
        {
            Monster* _monster = gameRoom[i]->GetLiveMonster();
            int _x1 = _monster->GetX();
            int _x2 = _monster->GetWidth() + _x1;
            int _y1 = _monster->GetY();
            int _y2 = _monster->GetHeight() + _y1;
            obs->SetXY(_x1, _x2, _y1, _y2);
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
void ChoseEvent(GameEvent_number event)
{
    switch (event)
    {
        case game_framework::MonsterGohome_eventNumber:
            //MonsterGohome_event(Room *_room);
            break;

        default:
            break;
    }
}
void MonsterFindHouse(Monster** _monster, int TaskBoard_x, int TaskBoard_Width) //怪物找房
{
    if (Moving(_monster, TaskBoard_x + 60, 0,Obstacle()))
    {
        (*_monster)->SetMovingType(Back);
        (*_monster)->SetMonsterState(findHouse);
    }
}
void MonsterlivingHouse_event(Room* _room, Monster** _monster)
{
    _room->SetMonsterlivingRoom(_monster);
    MonsterGohome_event(_room);
}
void MonsterGohome_event(Room* _room)
{
    _room->LetMonsterGohome();
}
void MonsterBeingClick(Monster** _monster, int room_size, Room** gameroom)
{
    Monster_state nowState = (*_monster)->GetMonsterState();

    switch (nowState)
    {
        case game_framework::wolking:
            break;

        case game_framework::findHouse:                   //同意怪物住進防屋
            for (int i = 0; i < room_size; i++)
            {
                if (!(gameroom)[i]->GetIsMonsterLiving())    //沒怪物住的話就分配到那間房
                {
                    MonsterlivingHouse_event((gameroom)[i], _monster);
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
    if (Moving(_monster, -100, 0,Obstacle()))
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

    if (obs.isHit((*_monster)->GetX(), (*_monster)->GetX() + (*_monster)->GetWidth(), (*_monster)->GetY(), (*_monster)->GetY() + (*_monster)->GetHeight()))
    {
		(*_monster)->SetMovingLeft(false);
		(*_monster)->SetMovingLeft(false);
        return false;
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
    int __warriorFloor = (*_warrior)->GetFloor();

    if (obs.isHit((*_warrior)->GetX(), (*_warrior)->GetX() + (*_warrior)->GetWidth(), (*_warrior)->GetY(), (*_warrior)->GetY() + (*_warrior)->GetHeight()))
    {
		(*_warrior)->SetMovingLeft(false);
		(*_warrior)->SetMovingRight(false);
        return true;
    }

    if (__warriorFloor == floor)
    {
        return MovingLR(_warrior, x);
    }
    else if (__warriorFloor < floor)                      //上樓
    {
        if (MovingLR(_warrior, Floor_x[__warriorFloor]))
        {
            (*_warrior)->SetMovingUp(true);
        }
    }
    else                                                //下樓
    {
        if (MovingLR(_warrior, Floor_x[__warriorFloor - 1]))
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
    if ((*_warrior) != NULL)
    {
        delete *_warrior;
        (*_warrior) = NULL;
    }
}
bool HitMonster(Warrior* _warrior, Monster* _monster)
{
    return _warrior->HitRectangle(_monster->GetX(), _monster->GetY(), _monster->GetX() + _monster->GetWidth(), _monster->GetY() - _monster->GetHeight());
}
void WarriorAttack_event(Warrior* _warrior, Monster** target, Obstacle obs)
{
    switch (_warrior->GetAttackType())
    {
        case Ad:
            if (Moving(&_warrior, (*target)->GetX(), (*target)->GetFloor(), obs) && HitMonster(_warrior, (*target)))
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
            if (_warrior->GetX() > (*target)->GetX())    //
            {
            }

            break;
    }
}
void MonsterAttack_event(Monster* _monster, Warrior** target, Obstacle obs)
{
    switch (_monster->GetAttackType())
    {
        case Ad:
            if (Moving((&_monster), (*target)->GetX(), (*target)->GetFloor(), obs) )
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

            if (Moving((&_monster), targetX, (*target)->GetFloor())|| (abs((*target)->GetX() - _monster->GetX()) < 200 && (*target)->GetFloor() == _monster->GetFloor()))
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
Monster* findMonsterTarget(Warrior* _warrior, Room** gameroom, int room_size)
{
    Monster* result = NULL;
    int minX = 9999;

    for (int i = 0; i < room_size; i++)
    {
        if (gameroom[i] ->GetIsMonsterLiving() && gameroom[i]->GetLiveMonster()->GetIsOnBattle())  //判斷怪物是否正在戰鬥
        {
            int dx = abs(_warrior->GetX() - (gameroom[i]->GetLiveMonster())->GetX());          //距離差

            if (gameroom[i]->GetLiveMonster()->GetFloor() != _warrior->GetFloor())
            {
                int dFloor = abs(gameroom[i]->GetLiveMonster()->GetFloor() - _warrior->GetFloor());   //樓層差
                dx += dFloor * 400;
            }

            if (dx < minX)
            {
                minX = dx;
                result = (gameroom[i]->GetLiveMonster());
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
        if (gameRoom[i]->GetLiveMonster()!=NULL && gameRoom[i]->GetLiveMonster()->GetIsOnBattle())
        {
            gameRoom[i]->LetMonsterGohome();
            gameRoom[i]->GetLiveMonster()->SetIsOnBattle(false);
        }
    }
}
void WarriorAdAttack(Warrior* _warrior, Monster _monster)
{
}

void BattleTest1(Warrior** _warrior, bool& isIntoBattle, Room** gameRoom)
{
    isIntoBattle = true;
    CreateWarrior_event(&_warrior[0], villager);
}
}