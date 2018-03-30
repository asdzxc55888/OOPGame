#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"
namespace game_framework {
	Monster::Monster(string _monsterTpye)
	{
		monsterType = _monsterTpye;
		isExist = false;
	}
	Monster::Monster()
	{
		monsterType = "tentacle";
		isExist = false;
	}
	void Monster::operator=(Monster &obj)
	{
		_x = obj._x;
		_y = obj._y;
		Hp = obj.Hp;								//血量
		ApDefense = obj.ApDefense;
		AdDefense = obj.AdDefense;
		AttackPower = obj.AttackPower;				//攻擊力
		isMovingDown = obj.isMovingDown;			// 是否正在往下移動
		isMovingLeft = obj.isMovingLeft;			// 是否正在往左移動
		isMovingRight = obj.isMovingRight;			// 是否正在往右移動
		isMovingUp = obj.isMovingRight;				// 是否正在往上移動
		AttackType = obj.AttackType;				//攻擊模式
		nowMovingType = obj.nowMovingType;			//移動模式
		monsterType = obj.monsterType;				//怪物種類
		npcObject::LoadBitmap(monsterType);
		isExist = true;
	}
	
	void Monster::SetMonsterType(string _monsterType)
	{
		monsterType = _monsterType;
	}
	void Monster::SetMonsterState(Monster_state _state)
	{
		nowMonsterState = _state;
	}
	void Monster::SetMonsterIsExist(bool flag)
	{
		isExist = flag;
	}
	Monster_state Monster::GetMonsterState()
	{
		return nowMonsterState;
	}
	string Monster::GetMonsterType()
	{
		return monsterType;
	}
	bool Monster::GetIsExist()
	{
		return isExist;
	}
}