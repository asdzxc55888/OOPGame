#pragma once
#include "Room.h"
#include "Warrior.h"
#include "obstacle.h"
#include "TaskBoard.h"
#include "GMoney.h"
#include "RoomInterface.h"
#include "MenuInterface.h"
namespace game_framework
{
#define room_x 650
#define room_y 510
class GameEvent
{
    public:
        GameEvent();
        ~GameEvent();
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
        void OnEvent();                                 // 事件處理
        bool GameOver();                                // 判斷是否結束，true代表結束
        bool SaveGame(string saveName);                 // 儲存遊戲
        bool LoadGame(string saveName);					// 讀取遊戲
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void SetObstacle();                             // 設定障礙物
        bool GetIsRoomFull();                           // 房屋是否客滿
        void GetMoneyEvent();                           // 把收取到的錢給玩家
        void CollectRentEvent();                        // 收取房租
        ////////////////////////////////////////////////////////////////////////////怪物事件/////////////////////////////////////////////////
        void MonsterStateEvent();                                            // 怪物狀態事件處理
        void MonsterFindHouse(Monster** _monster);                           // 怪物看屋事件
        void MonsterlivingHouse_event(Room* _room, Monster** _monster);      // 怪物住房事件
        void MonsterGohome_event(Room* _room, int monsterIndex);             // 怪物進房事件，等同怪物住屋事件
        void MonsterBeingClick(Monster** _monster);                          // 怪物被點擊事件
        bool MonsterLeave(Monster** _monster);                               // 怪物離開，直接消失的那種離開
        bool Moving(Monster** _monster, int x, int floor);                   // 怪物移動
        bool MovingLR(Monster** _monster, int x);
        bool HitWarrior(Monster* _monster, Warrior* _warrior);               // 判斷有無碰到勇者
        void CreateMonster_event(Monster** _monster);
        ////////////////////////////////////////////////////////////////////////////勇者事件///////////////////////////////////////////////////
        bool Moving(Warrior** _warrior, int x, int floor);
        bool MovingLR(Warrior** _warrior, int x);
        void CreateWarrior_event(Warrior** _warrior, warrior_type type);
        void DeleteWarrior_event(Warrior** _warrior);
        bool HitMonster(Warrior* _warrior, Monster* _monster);
        ////////////////////////////////////////////////////////////////////////////戰鬥事件///////////////////////////////////////////////////
        void WarriorAttack_event(Warrior* _warrior, Monster** target);
        void MonsterAttack_event(Monster* _monster, Warrior** target);
        void MonsterPositionFix();                                                      // 怪物位置修正
        Monster* findMonsterTarget(Warrior* _warrior);
        Warrior* findWarriorTarget(Monster* _monster);
        void BattleFinish();															// 戰鬥完成
        void SeleteTaskBattle();														// 依任務選擇出場勇者，計數下一次戰鬥時間
        void BattleTest1();
        ////////////////////////////////////////////////////////////////////////////時間控制///////////////////////////////////////////////////
        void timeControl();
        ////////////////////////////////////////////////////////////////////////////戀愛事件///////////////////////////////////////////////////
        void ComingMonsterFallInLoveEvent();             //拜訪怪物戀愛事件
        void MonsterMatingEvent();    //怪物交配事件
        void MonsterBorn(int roomNum);  //怪物出身
    private:
        CMovingBitmap  Background;                  //背景圖
        CMovingBitmap  Warning;                     //警告圖
		CAnimation     fall;                        //失敗圖
        CAnimation     SpeedControlBtn[3];          //速度控制圖
        GMoney         myMoney;						//金錢
        TaskBoard      myTaskBoard;					//任務版 管理任務的物件
        Obstacle       mapObstacle;					//怪物與勇者的座標 用來做障礙物判斷
        Room*          gameRoom[4];					//房間
        RoomInterface* myRoomInterface;				//房間資訊
		MenuInterface  myMenu;						//主選單
        Monster*       comingMonster;               //來看房子的怪物
        Warrior*       warrior[10];					//勇者
        time_t         Settime, nowtime;
		int addMoney;                             //增加的金錢
		int battleCount;                          //剩餘發生戰鬥時間
        int CollectRentTime;
		int Clock;
		int DevilRoom_x;						  //魔王房間的座標
		int DevilRoom_floor;                      //魔王房間的樓層
        int TimeLevel;                            //時間快慢
        int roomSize;                             //房間大小
        int riseMoney;                            //正在增加的金錢
		bool isFall;
        bool isGamePause;                         //遊戲是否暫停
        bool isIntoBattle;                        //是否剛進入戰鬥
        bool isOnBattle;						  //是否在戰鬥
        bool isSpeedControlOn[3];
        bool isMonsterDataBoardShow;
		bool isRoomDataBoardShow;
        bool isMonsterGoingOut;
		bool isEffectMusicOn;
        bool GameOverFlag;                        //遊戲結束
};

}