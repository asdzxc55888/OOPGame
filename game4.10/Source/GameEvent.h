#pragma once
#include "Room.h"
#include "Warrior.h"
#include "obstacle.h"
#include "TaskBoard.h"
namespace game_framework {
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
		bool GameOver();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetObstacle();
		bool GetIsRoomFull();     //房屋是否客滿
		////////////////////////////////////////////////////////////////////////////怪物事件////////////////////////////////////////////////////////
		void MonsterFindHouse(Monster **_monster); //怪物看屋事件 
		void MonsterlivingHouse_event(Room* _room, Monster** _monster);
		void MonsterGohome_event(Room *_room, int monsterIndex);                  //怪物進房事件，等同怪物住屋事件
		void MonsterBeingClick(Monster **_monster); //怪物被點擊事件
		bool MonsterLeave(Monster **_monster);                                      //怪物離開，直接消失的那種離開
		bool Moving(Monster **_monster, int x, int floor);                          //怪物移動
		bool MovingLR(Monster **_monster, int x);
		bool HitWarrior(Monster* _monster, Warrior* _warrior);          //判斷有無碰到勇者
		void CreateMonster_event(Monster **_monster);
		////////////////////////////////////////////////////////////////////////////勇者事件//////////////////////////////////////////////////////////
		bool Moving(Warrior **_warrior, int x, int floor);
		bool MovingLR(Warrior **_warrior, int x);
		void CreateWarrior_event(Warrior **_warrior, warrior_type type);
		void DeleteWarrior_event(Warrior **_warrior);
		bool HitMonster(Warrior *_warrior, Monster *_monster);
		/////////////////////////////////////////////////////////////////////////////////戰鬥事件/////////////////////////////////////////////////////
		void WarriorAttack_event(Warrior *_warrior, Monster **target);
		void MonsterAttack_event(Monster *_monster, Warrior ** target);
		void MonsterPositionFix();        //怪物位置修正
		Monster* findMonsterTarget(Warrior *_warrior);
		Warrior* findWarriorTarget(Monster *_monster);
		void BattleEnd();
		void SeleteTaskBattle();
		void BattleTest1();
		///////////////////////////////////////////////////////////////////時間控制//////////////////////////////////////////////////////////////////
		void timeControl();
		//////////////////////////////////////////////////////////////////////戀愛事件///////////////////////////////////////////////////
		void ComingMonsterFallInLoveEvent();             //拜訪怪物戀愛事件
		void MonsterMatingEvent();    //怪物交配事件
		void MonsterBorn(int roomNum);  //怪物出身
	private:
		CMovingBitmap Background;                  //背景圖
		CMovingBitmap Warning;                    //警告圖
		CAnimation SpeedControlBtn[3];            //速度控制圖
		CInteger Money;
		TaskBoard myTaskBoard;
		Obstacle mapObstacle;
		Room* gameRoom[4];
		Monster* comingMonster;                    //來看房子的怪物
		Warrior* warrior[10];
		time_t Settime, nowtime;
		int TimeLevel;                            //時間快慢
		int Clock;
		int houseLevele;
		int roomSize;
		int battleCount;
		bool isGamePause;
		bool isIntoBattle;                        //是否剛進入戰鬥
		bool isOnBattle;						  //是否在戰鬥
		bool isSpeedControlOn[3];
		bool isMonsterDataBoardShow;
		bool isMonsterGoingOut;
		bool GameOverFlag;                       //有人入住就為true 判斷是否為遊戲剛開始
		bool WarningQuit;
	};
	
}