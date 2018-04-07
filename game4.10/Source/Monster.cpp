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
		RandBasicAbility();
		isExist = false;
	}
	Monster::Monster()
	{
		RandMonsterType();
		RandBasicAbility();
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
		LoadBitmap(monsterType);
		isExist = true;
	}

	void Monster::LoadBitmap(string monsterName)
	{
		monsterName += ".bmp";
		string root = "Bitmaps\\monster\\monster_";
		root += monsterName;
		char test[100];
		strcpy(test, root.c_str());
		animation[Forward]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack1_" + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack2_" + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft1_" + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft2_" + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight1_" + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight2_" + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		animation[Hide]->AddBitmap("Bitmaps\\monster\\monsterHide.bmp", RGB(255, 255, 255));
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
	bool Monster::IsMouseOn(CPoint point)
	{
		if (point.x > _x && point.x <= _x + GetWidth() && point.y > _y && point.y <= _y + GetHeight()) {
			return true;
		}
		return false;
	}
	void Monster::RandMonsterType()
	{
		string totalMonsterType[totalMonsterType_size] = { "tentacle","kappa" };
		int result = rand() % totalMonsterType_size;
		monsterType = totalMonsterType[result];
	}
	void Monster::RandBasicAbility()   //�H����O
	{
		int randValue[4];
		randValue[0] = rand() % 20;
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 5;
		//��¦��O
		if (monsterType == "tentacle") {
			Hp=100;					//��q
			ApDefense=8;			//�]�k���m
			AdDefense=5;			//���z���m
			AttackPower=10;         //�����O
			AttackType=Ap;			//�����Ҧ�
		}
		else if (monsterType == "kappa") {
			Hp = 120;					//��q
			ApDefense = 5;			//�]�k���m
			AdDefense = 9;			//���z���m
			AttackPower = 12;         //�����O
			AttackType = Ad;			//�����Ҧ�
		}
		//�H����O
		Hp += randValue[0];
		ApDefense += randValue[1];
		AdDefense += randValue[2];
		AttackPower += randValue[3];
	}
}