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
        int _x, _y; //座標
		int counter;
        Monster liveMonster;	//居住怪物
        CAnimation animation;  //動畫
		bool MonsterGoHome(); //若還沒到達家裡得坐標，回傳 true ，到達了回傳false
        bool isMonsterIn;		
        bool isDoorOpen;
		bool isMonsterGoHome;
		bool MonsterGohomeEvent;
};
}


