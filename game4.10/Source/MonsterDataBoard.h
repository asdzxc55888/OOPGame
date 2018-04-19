#pragma once
namespace game_framework {
	class MonsterDataBoard
	{
	public:
		MonsterDataBoard();	
		void Initialize();
		~MonsterDataBoard();

	private:

		CInteger Hp;
		CInteger AttackPower;
		CInteger AdDefense;
		CInteger ApDefense;
	};
}

