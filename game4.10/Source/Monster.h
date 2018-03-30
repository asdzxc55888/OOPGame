#pragma once
#include "npcObject.h"

namespace game_framework {
	enum Monster_state {
		wolking,
		findHouse
	};
	class Monster :public npcObject
	{
	
	public:
		Monster(string _monsterTpye);
		Monster();
		void operator= (Monster &obj);
		void SetMonsterType(string _monsterType);
		void SetMonsterIsExist(bool flag);
		string GetMonsterType();
		bool GetIsExist();
	private:
		string monsterType;
		Monster_state nowMonsterState;
		int name;
		bool isExist;
	};
	
}
