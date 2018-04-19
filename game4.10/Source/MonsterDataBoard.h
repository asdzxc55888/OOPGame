#pragma once
namespace game_framework {
	class MonsterDataBoard
	{
	public:
		MonsterDataBoard(int MaxHp ,int ApD, int AdD ,int dps,string MonsterType,bool flag);
		MonsterDataBoard();	
		~MonsterDataBoard();
		void Initialize(int MaxHp, int ApD, int AdD, int dps, string MonsterType, bool flag);
		void ShowHpBar(int percent);
		void SetData(int hp,int maxHp, int ApD, int AdD, int dps);
		void OnShow();
	private:
		int GetDigit(int x);
		int x, y;
		CMovingBitmap Board,Picture;
		CInteger *Hp,*MaxHp;
		CInteger *AttackPower;
		CInteger *AdDefense;
		CInteger *ApDefense;
		bool isLoadBitmaps;
	};
}

