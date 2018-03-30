#pragma once
#include "npcObject.h"

namespace game_framework {
	
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
		int name;
		bool isExist;
	};
	
}
