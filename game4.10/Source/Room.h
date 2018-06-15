#pragma once
#include "Monster.h"
#include "RoomDataBoard.h"
namespace game_framework
{
class Room
{
    public:
        Room(int x, int y, int _roomNumber);
        ~Room();
        void LoadBitmap();
        void Initial();                       //��l��
        void OnShow(bool flag);//true ��������� false�����Ǫ����
        void OnMove();
        void MonsterDeath(int monsterIndex);
        void MonsterLeave(int monsterIndex);
        void SetDoorOpen();
        void SetRent(int _rent);
        void SetMonsterFight(bool flag);
        void SetIsMonsterIn(bool flag, int monsterIndex);  //�]�w�Ǫ��O�_�b�a
        void SetMonsterlivingRoom(Monster** _monster);     //���Ǫ���i�Фl
        void SetRoomBoard();                               //�]�m�Ыθ�ƪ�
        void LetMonsterGohome(int monsterIndex);
        int  GetRent();
        int  GetX();
        int  GetLiveMonsterSize();
		int  GetRoomNumber();
        bool GetIsMonsterIn(int monsterIndex);
        bool GetIsMonsterFight(int monsterIndex);
        bool IsMouseOn(CPoint point);                      //�ˬd�ƹ��O�_�b�W��
        bool MovingLR(int x, int MonsterIndex);
        Monster* GetLiveMonster(int index);
    private:
        int  _x, _y; //�y��
        int  floor;                           //�Ӽh
        int  liveMonsterSize;     //�~��Ǫ��Ӽ�
        int  RoomNumber;
        int  timecount;
        int  rent;                           //����
        void SetMonsterIntohome(int monsterIndex); //�Ǫ��i�����ʧ@
        void ResortLiveMonster();
        bool monsterGoOutsideTemp[3];
        bool MonsterGoHome(int monsterIndex); //�Y�٨S��F�a�̱o���СA�^�� true �A��F�F�^��false
        bool isMonsterIn[3];		//�~���Ǫ��O�_�b�̭�
        bool isDoorOpen;		//�����S���}
        bool isMonsterGoHome[3];	//�Ǫ��O�_���b���ʶi��
        bool isMonsterFight[3];    //�Ǫ��O�_�԰�
        bool isMouseOn;
        bool isMusicEffectOn;
        Monster* liveMonster[3];	//�~��Ǫ�
        RoomDataBoard* myDataBoard;
        CAnimation animation;  //�ʵe
};
}


