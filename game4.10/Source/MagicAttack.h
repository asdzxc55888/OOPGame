#pragma once

namespace game_framework {
	enum Direction {
		Left,
		Right
	};
	class MagicAttack
	{
	public:
		MagicAttack(int _x, int _y, int _damge, string type);
		~MagicAttack();
		void SetDirection(Direction _direction);
		void SetTarget(int _tx1, int _tx2);
		void LoadBitmap(string type);
		bool HitTarget();        //是否碰到目標
		int GetX();
		int GetY();
		int GetDamge();
		void OnMove();
		void OnShow();
	private:
		int x, y;
		int tx1, tx2;            //目標座標
		int damge;
		CMovingBitmap bmp[2];
		Direction nowDirection;
		bool isMovingLeft;
		bool isMovingRight;
	};
}

