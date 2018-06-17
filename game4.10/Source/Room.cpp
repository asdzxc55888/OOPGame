#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Room.h"
namespace game_framework
{
Room::Room(int x, int y, int _roomNumber) : _x(x), _y(y), RoomNumber(_roomNumber) //������
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
    for (int i = 0; i < 3; i++)liveMonster[i] = NULL;

    myDataBoard = NULL;
    floor = 0;
    liveMonsterSize = 0;
    timecount = 0;
    rent = 15;
    isDoorOpen = false;
    isMouseOn = false;
    isMusicEffectOn = false;

    for (int i = 0; i < 3; i++) isMonsterIn[i] = false;

    for (int i = 0; i < 3; i++) isMonsterGoHome[i] = false;

    for (int i = 0; i < 3; i++) isMonsterFight[i] = false;

    for (int i = 0; i < 3; i++) monsterGoOutsideTemp[i] = false;

    animation.SetDelayCount(10);
}
void Room::OnShow(bool flag)  //true ��������� false�����Ǫ����
{
    if (isMouseOn)                     //����檺���
    {
        if (!isMusicEffectOn)
        {
            CAudio::Instance()->Play(AUDIO_DING);
            isMusicEffectOn = true;
        }

        if (GetLiveMonsterSize() > 0)myDataBoard->OnShow();
    }
    else
    {
        isMusicEffectOn = false;
    }

    if (flag)
    {
        animation.SetTopLeft(_x, _y);
        animation.OnShow();
    }
    else
    {
        for (int i = 0; i < liveMonsterSize; i++)if (liveMonster[i] != NULL)liveMonster[i]->OnShow();                           //�Ǫ��s�b�a�ϤW�P�_
    }
}
void Room::OnMove()
{
    for (int i = 0; i < liveMonsterSize; i++)
    {
        if (isMonsterGoHome[i])isMonsterGoHome[i] = MonsterGoHome(i);// �Ǫ��^�a����
    }

    for (int i = 0; i < liveMonsterSize; i++)if (liveMonster[i] != NULL)liveMonster[i]->OnMove();

    if (isDoorOpen)                             //�}�����ʵe
    {
        if (!animation.IsFinalBitmap())
        {
            animation.OnMove();        //�Y���O�̫�@�ӹϧΡA�NOnMove��̫�@�ӹϧΫᰱ��C
            animation.SetDelayCount(50);
            CAudio::Instance()->Play(AUDIO_DOOROPEN);
        }
        else
        {
            animation.OnMove();
            animation.SetDelayCount(10);
            CAudio::Instance()->Play(AUDIO_DOORCLOSE);

            if (animation.GetCurrentBitmapNumber() == 0)isDoorOpen = false;
        }
    }

    for (int i = 0; i < liveMonsterSize; i++)                                 ///////////////�Ǫ��X���w�R
    {
        if (timecount > 150 && monsterGoOutsideTemp[i])
        {
            liveMonster[i]->SetIsGoOutside(true);
            isMonsterIn[i] = false;
            isDoorOpen = true;
            monsterGoOutsideTemp[i] = false;
            timecount = 0;
            break;
        }
        else
        {
            timecount++;
        }
    }
}
int Room::GetX()
{
    return _x;
}
Monster* Room::GetLiveMonster(int index)
{
    return liveMonster[index];
}
bool Room::GetIsMonsterIn(int monsterIndex)
{
    return isMonsterIn[monsterIndex];
}
bool Room::GetIsMonsterFight(int monsterIndex)
{
    return isMonsterFight[monsterIndex];
}
bool Room::GetIsMouseOn()
{
	return isMouseOn;
}
int Room::GetLiveMonsterSize()
{
    int size = 0;

    for (int i = 0; i < 3; i++)
    {
        if (liveMonster[i] != NULL)
        {
            size += 1;
        }
    }

    return size;
}
int Room::GetRoomNumber()
{
	return RoomNumber;
}
void Room::LetMonsterGohome(int MonsterIndex)
{
    isMonsterGoHome[MonsterIndex] = true;
    isMonsterFight[MonsterIndex] = false;
}
int Room::GetRent()
{
    return rent;
}
bool Room::IsMouseOn(CPoint point)
{
    if (point.x > _x && point.x <= _x + animation.Width() && point.y > _y && point.y <= _y + animation.Height())
    {
        isMouseOn = true;
        return true;
    }

    isMouseOn = false;
    return false;
}
bool Room::MovingLR(int x, int MonsterIndex)
{
    if (liveMonster[MonsterIndex]->GetX() > x - 35)
    {
        liveMonster[MonsterIndex]->SetMovingLeft(true);
        liveMonster[MonsterIndex]->SetMovingRight(false);
    }
    else if (liveMonster[MonsterIndex]->GetX() <= x - 45)
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

    if (liveMonsterSize > 0)
    {
        ResortLiveMonster();
    }
}
void Room::MonsterLeave(int monsterIndex)
{
    liveMonster[monsterIndex] = NULL;
    liveMonsterSize--;
    isMonsterFight[monsterIndex] = false;
    isMonsterIn[monsterIndex] = false;
    isMonsterGoHome[monsterIndex] = false;

    if (liveMonsterSize > 0)
    {
        ResortLiveMonster();
    }
}
void Room::SetDoorOpen()
{
    isDoorOpen = true;
}
void Room::SetRent(int _rent)
{
    rent = _rent;
}
void Room::SetMonsterFight(bool flag)  //�Ǫ��԰�
{
    for (int i = 0; i < liveMonsterSize; i++)
    {
        if (!liveMonster[i]->GetIsOnBattle())
        {
            monsterGoOutsideTemp[i] = true;
            liveMonster[i]->SetPoint(liveMonster[i]->GetX() + 5 * i, liveMonster[i]->GetY());
            liveMonster[i]->SetBattleTemp(true);
            isMonsterFight[i] = true;
        }
    }
}
void Room::SetIsMonsterIn(bool flag, int monsterIndex)
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
void Room::ResortLiveMonster()     //���s�ƦC�Ǫ�����
{
    for (int i = 0; i < 2; i++)
    {
        if (liveMonster[i] == NULL)
        {
            for (int k = i + 1; k < 3; k++)
            {
                if (liveMonster[k] != NULL)
                {
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
    int Floor_x[3] = { 1150, 750, 1150 };
    int _monsterFloor = liveMonster[monsterIndex]->GetFloor();

    if (_monsterFloor == floor)
    {
        if (MovingLR(_x + 40, monsterIndex))
        {
            SetMonsterIntohome(monsterIndex);
            isMonsterGoHome[monsterIndex] = false;
            return false;
        }
    }
    else if (_monsterFloor < floor)                      //�W��
    {
        if (MovingLR(Floor_x[_monsterFloor], monsterIndex))
        {
            liveMonster[monsterIndex]->SetMovingUp(true);
        }
    }
    else                                                //�U��
    {
        if (MovingLR(Floor_x[_monsterFloor - 1], monsterIndex))
        {
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

    if (myDataBoard != NULL)
    {
        delete myDataBoard;
        myDataBoard = NULL;
    }

    SetRoomBoard();
}
void Room::SetRoomBoard()
{
    string _monsterType[3], _monsterName[3];
    bool _monsterIsKid[3];
    int _monsterGender[3];

    for (int i = 0; i < liveMonsterSize; i++)
    {
        _monsterType[i] = liveMonster[i]->GetMonsterType();
        _monsterName[i] = liveMonster[i]->GetMonsterName();
        _monsterGender[i] = liveMonster[i]->GetMonsterGender();
        _monsterIsKid[i] = liveMonster[i]->GetIsKid();
    }

    myDataBoard = new RoomDataBoard(liveMonsterSize, _monsterType, _monsterGender, _monsterName, _monsterIsKid, RoomNumber,rent);
}
}
