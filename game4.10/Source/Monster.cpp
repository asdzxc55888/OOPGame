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
		Hp = obj.Hp;								//��q
		ApDefense = obj.ApDefense;
		AdDefense = obj.AdDefense;
		AttackPower = obj.AttackPower;				//�����O
		isMovingDown = obj.isMovingDown;			// �O�_���b���U����
		isMovingLeft = obj.isMovingLeft;			// �O�_���b��������
		isMovingRight = obj.isMovingRight;			// �O�_���b���k����
		isMovingUp = obj.isMovingRight;				// �O�_���b���W����
		AttackType = obj.AttackType;				//�����Ҧ�
		nowMovingType = obj.nowMovingType;			//���ʼҦ�
		monsterType = obj.monsterType;				//�Ǫ�����
		npcObject::LoadBitmap(monsterType);
		name=obj.name;
		isExist = true;
	}
	
	void Monster::SetMonsterType(string _monsterType)
	{
		monsterType = _monsterType;
	}
	void Monster::SetMonsterIsExist(bool flag)
	{
		isExist = flag;
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