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
		void LoadBitmap(string str);
		string GetWarriorType();
	private:
		void RandWarroirType();
		void RandBasicAbility();
		warrior_type warriorType;
	};

}