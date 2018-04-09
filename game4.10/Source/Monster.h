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
		findHouse,
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
		Monster_state GetMonsterState();            //取的怪物狀態
		string GetMonsterType();
		bool GetIsExist();							//取得怪物是否顯示在地圖上
		bool IsMouseOn(CPoint point);
	private:
		void RandMonsterType();
		void RandBasicAbility();
		string monsterType;                          //怪物類型
		Monster_state nowMonsterState;				//怪物當前狀態
		bool isExist;
	};
	
}
