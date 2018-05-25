#pragma once
#include "npcObject.h"
class Warrior;
#include"Warrior.h"
#define totalMonsterType_size  3
#define GrowupTime 3000
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
		void InheritAbility(Monster *father,Monster *mother);
		void SetMonsterType(string _monsterType);	//設定怪物種類 傳入物種類字串
		void SetMonsterState(Monster_state _state);	//這定怪物狀態
		void SetMonsterIsExist(bool flag);			//設定怪物是否顯示在地圖上
		void SetIsChild(bool flag);
		void SetTimecount(int time);
		void ShowHpBar();
		void OnShow();
		Monster_state GetMonsterState();            //取的怪物狀態
		Gender GetMonsterGendet();
		string GetMonsterType();
		string GetMonsterName();
		int GetMonsterGender();
		bool GetIsExist();							//取得怪物是否顯示在地圖上
		bool GetIsKid();
		bool IsMouseOn(CPoint point);
	private:
		int monsterAge;
		int HpCount;          //生命回復計數
		void RandMonsterType();
		void RandBasicAbility();
		void RandName();
		void RandGender();
		void HpResume();
		void GrowUp();  //怪物長大
		bool isMusicEffectOn;
		bool isExist;
		bool isMouseOn;
		bool isHeadImgRoad;
		string name;
		string monsterType;                         //怪物類型
		Gender monsterGender;
		Monster_state nowMonsterState;				//怪物當前狀態
		MonsterDataBoard *MyBoard;                  //資訊欄
		CMovingBitmap headImg[3];                      //頭上符號

	};
	
}
