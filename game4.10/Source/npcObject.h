#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	enum Attack_Type
	{
		Ad,		//物理攻擊 0
		Ap		//魔法攻擊 1		
	};
	class npcObject
	{
	public:
		npcObject();
		~npcObject();
		void LoadBitmap();		// 載入圖形
		void OnMove();			// 移動
		void OnShow();			// 將圖形貼到畫面
		void SetPoint(int _x, int _y);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		int GetX();				
		int GetY();
		int GetHp();
		int GetApDefense();
		int GetAdDefense();
		int GetAttackPower();
		int GetAttackType();

	private:
		int x, y;				//座標
		int Hp;					//血量
		int ApDefense;			//魔法防禦
		int AdDefense;			//物理防禦
		int AttackPower;        //攻擊力
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		CAnimation animation;   //動畫
		Attack_Type AttackType; //攻擊模式

	};
}
