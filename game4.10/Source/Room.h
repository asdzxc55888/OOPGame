#pragma once
#include "Monster.h"
namespace game_framework
{
class Room
{
    public:
        Room(int x, int y);
        ~Room();
        void LoadBitmap();
		void OnShow(bool flag);
        void OnMove();
        Monster GetLiveMonster();
		void LetMonsterGohome();
		bool IsMouseOn(CPoint point);
		void SetMonsterIntohome(bool flag);
        void SetMonsterlivingRoom(Monster *_monster);
    private:
        int _x, _y; //�y��
		int counter;
        Monster liveMonster;	//�~��Ǫ�
        CAnimation animation;  //�ʵe
		bool MonsterGoHome(); //�Y�٨S��F�a�̱o���СA�^�� true �A��F�F�^��false
        bool isMonsterIn;		
        bool isDoorOpen;
		bool isMonsterGoHome;
		bool MonsterGohomeEvent;
};
}


