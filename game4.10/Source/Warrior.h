#pragma once
#include "npcObject.h"

namespace game_framework {
#define warrior_type_size 1
	enum warrior_type {
		villager
	};
	class Warrior :public npcObject
	{
	public:
		Warrior();
		Warrior(warrior_type type);
		~Warrior();
		void LoadBitmap(string str);
		void OnShow();
		string GetWarriorType();
	private:
		void RandWarroirType();
		void RandBasicAbility();
		warrior_type warriorType;
		MonsterDataBoard *MyBoard;
	};

}