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
        void OnShow(bool flag);//true 為讓門顯示 false試讓怪物顯示
        void OnMove();
		int GetX();
        Monster* GetLiveMonster(int index);
        bool GetIsMonsterLiving();
        bool GetIsMonsterIn(int monsterIndex);
        bool GetIsMonsterFight(int monsterIndex);
		int GetLiveMonsterSize();
        void LetMonsterGohome(int monsterIndex);
        bool IsMouseOn(CPoint point); //檢查滑鼠是否在上面
        bool MovingLR(int x, int MonsterIndex);
        void MonsterDeath(int monsterIndex);
        void SetMonsterFight(bool flag);
        void SetIsMonsterIn(bool flag, int monsterIndex);
        void SetMonsterlivingRoom(Monster** _monster); //讓怪物住進房子，回傳NULL指標將原本的怪物抹去
    private:
        int _x, _y; //座標
        int floor;
		int liveMonsterSize;     //居住怪物個數
		int RoomNumber;
		int timecount;
        Monster* liveMonster[3];	//居住怪物
		RoomDataBoard *myDataBoard;
        CAnimation animation;  //動畫
        void SetMonsterIntohome(int monsterIndex); //怪物進門的動作
		void ResortLiveMonster();
		bool monsterGoOutsideTemp[3];
        bool MonsterGoHome(int monsterIndex); //若還沒到達家裡得坐標，回傳 true ，到達了回傳false
        bool isMonsterLiving; //是否居住怪物
        bool isMonsterIn[3];		//居住的怪物是否在裡面
        bool isDoorOpen;		//門有沒有開
        bool isMonsterGoHome[3];	//怪物是否正在移動進屋
        bool isMonsterFight[3];    //怪物是否戰鬥
		bool isMouseOn;
		bool isMusicEffectOn;
};
}


