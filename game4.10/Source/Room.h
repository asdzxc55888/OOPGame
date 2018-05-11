#pragma once
#include "Monster.h"
#include "RoomDataBoard.h"
namespace game_framework
{
class Room
{
    public:
        Room(int x, int y);
        ~Room();
        void LoadBitmap();
        void Initial();
        void OnShow(bool flag);//true ��������� false�����Ǫ����
        void OnMove();
		int GetX();
        Monster* GetLiveMonster(int index);
        bool GetIsMonsterLiving();
        bool GetIsMonsterIn(int monsterIndex);
        bool GetIsMonsterFight(int monsterIndex);
		int GetLiveMonsterSize();
        void LetMonsterGohome(int monsterIndex);
        bool IsMouseOn(CPoint point); //�ˬd�ƹ��O�_�b�W��
        bool MovingLR(int x, int MonsterIndex);
        void MonsterDeath(int monsterIndex);
        void SetMonsterFight(bool flag);
        void SetIsMonsterIn(bool flag, int monsterIndex);
        void SetMonsterlivingRoom(Monster** _monster); //���Ǫ���i�Фl�A�^��NULL���бN�쥻���Ǫ��٥h
    private:
        int _x, _y; //�y��
        int floor;
		int liveMonsterSize;     //�~��Ǫ��Ӽ�
		int RoomNumber;
		int timecount;
        Monster* liveMonster[3];	//�~��Ǫ�
		RoomDataBoard *myDataBoard;
        CAnimation animation;  //�ʵe
        void SetMonsterIntohome(int monsterIndex); //�Ǫ��i�����ʧ@
		void ResortLiveMonster();
		bool monsterGoOutsideTemp[3];
        bool MonsterGoHome(int monsterIndex); //�Y�٨S��F�a�̱o���СA�^�� true �A��F�F�^��false
        bool isMonsterLiving; //�O�_�~��Ǫ�
        bool isMonsterIn[3];		//�~���Ǫ��O�_�b�̭�
        bool isDoorOpen;		//�����S���}
        bool isMonsterGoHome[3];	//�Ǫ��O�_���b���ʶi��
        bool isMonsterFight[3];    //�Ǫ��O�_�԰�
		bool isMouseOn;
		bool isMusicEffectOn;
};
}


