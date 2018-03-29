#pragma once
#include "npcObject.h"

namespace game_framework {
	
	class Monster :public npcObject
	{
	
	public:
		Monster();
		void operator= (Monster &obj);
		void SetMonsterType(string _monsterType);
		void SetMonsterIsExist(bool flag);
		bool GetIsExist();
	private:
		string monsterType;
		int name;
		bool isExist;
	};
	
}
