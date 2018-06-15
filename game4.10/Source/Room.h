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
        void Initial();                       //初始化
        void OnShow(bool flag);//true 為讓門顯示 false試讓怪物顯示
        void OnMove();
        void MonsterDeath(int monsterIndex);
        void MonsterLeave(int monsterIndex);
        void SetDoorOpen();
        void SetRent(int _rent);
        void SetMonsterFight(bool flag);
        void SetIsMonsterIn(bool flag, int monsterIndex);  //設定怪物是否在家
        void SetMonsterlivingRoom(Monster** _monster);     //讓怪物住進房子
        void SetRoomBoard();                               //設置房屋資料版
        void LetMonsterGohome(int monsterIndex);
        int  GetRent();
        int  GetX();
        int  GetLiveMonsterSize();
		int  GetRoomNumber();
        bool GetIsMonsterIn(int monsterIndex);
        bool GetIsMonsterFight(int monsterIndex);
        bool IsMouseOn(CPoint point);                      //檢查滑鼠是否在上面
        bool MovingLR(int x, int MonsterIndex);
        Monster* GetLiveMonster(int index);
    private:
        int  _x, _y; //座標
        int  floor;                           //樓層
        int  liveMonsterSize;     //居住怪物個數
        int  RoomNumber;
        int  timecount;
        int  rent;                           //租金
        void SetMonsterIntohome(int monsterIndex); //怪物進門的動作
        void ResortLiveMonster();
        bool monsterGoOutsideTemp[3];
        bool MonsterGoHome(int monsterIndex); //若還沒到達家裡得坐標，回傳 true ，到達了回傳false
        bool isMonsterIn[3];		//居住的怪物是否在裡面
        bool isDoorOpen;		//門有沒有開
        bool isMonsterGoHome[3];	//怪物是否正在移動進屋
        bool isMonsterFight[3];    //怪物是否戰鬥
        bool isMouseOn;
        bool isMusicEffectOn;
        Monster* liveMonster[3];	//居住怪物
        RoomDataBoard* myDataBoard;
        CAnimation animation;  //動畫
};
}


