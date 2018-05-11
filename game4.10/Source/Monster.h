#pragma once
#include "npcObject.h"
class Warrior;
#include"Warrior.h"
#define totalMonsterType_size  2
namespace game_framework {
	enum Monster_state {
		leave,
		nothing,
		wolking,
		lookHouse,
		findHouse,
		fallInLove
	};
	enum Gender {
		male,
		female
	};
	class Monster :public npcObject
	{
	public:
		Monster(string _monsterTpye);
		Monster();
		void operator= (Monster &obj);
		void LoadBitmap(string monsterName);
		void SetMonsterType(string _monsterType);	//設定怪物種類 傳入物種類字串
		void SetMonsterState(Monster_state _state);	//這定怪物狀態
		void SetMonsterIsExist(bool flag);			//設定怪物是否顯示在地圖上
		void SetIsChild(bool flag);
		void ShowHpBar();
		void OnShow();
		Monster_state GetMonsterState();            //取的怪物狀態
		string GetMonsterType();
		string GetMonsterName();
		int GetMonsterGender();
		bool GetIsExist();							//取得怪物是否顯示在地圖上
		bool IsMouseOn(CPoint point);
	private:
		void RandMonsterType();
		void RandBasicAbility();
		void RandName();
		void RandGender();
		bool isMusicEffectOn;
		bool isExist;
		bool isMouseOn;
		string name;
		string monsterType;                         //怪物類型
		Gender monsterGender;
		Monster_state nowMonsterState;				//怪物當前狀態
		MonsterDataBoard *MyBoard;                  //資訊欄
		CMovingBitmap headImg[3];                      //頭上符號

	};
	
}
