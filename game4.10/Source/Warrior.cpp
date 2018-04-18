#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Warrior.h"
namespace game_framework {
	Warrior::Warrior()
	{
		RandWarroirType();
		string LoadBmpString = "";
		switch (warriorType)
		{
		case game_framework::villager:
			LoadBmpString = "villager";
			break;
		default:
			break;
		}
		LoadBitmap(LoadBmpString);
		RandBasicAbility();
	}
	Warrior::Warrior(warrior_type type)
	{
		string LoadBmpString = "";
		switch (type)
		{
		case game_framework::villager:
			LoadBmpString = "villager";
			warriorType = villager;
			break; 
		default:
			break;
		}
		LoadBitmap(LoadBmpString);
		RandBasicAbility();
	}
	void Warrior::LoadBitmap(string str)
	{
		str += ".bmp";
		string root = "Bitmaps\\warrior\\warrior_";
		root += str;
		char test[100];
		strcpy(test, root.c_str());
		animation[Forward]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorBack1_" + str;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorBack2_" + str;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorLeft1_" + str;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorLeft2_" + str;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorRight1_" + str;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorRight2_" + str;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorAttackLeft1_" + str;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorAttackLeft2_" + str;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorAttackRight1_" + str;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\warrior\\warriorAttackRight2_" + str;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		animation[Hide]->AddBitmap("Bitmaps\\warrior\\warriorHide.bmp", RGB(255, 255, 255));
	}
	string Warrior::GetWarriorType()
	{
		switch (warriorType)
		{
		case game_framework::villager:
			return "villager";
			break;
		default:
			break;
		}
		return "";
	}
	void Warrior::RandWarroirType()
	{
		int randValue = rand() % warrior_type_size;
		warriorType = (warrior_type)randValue;
	}
	void Warrior::RandBasicAbility()
	{
		int randValue[4];
		randValue[0] = rand() % 20;
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 5;
		//基礎能力
		switch (warriorType)
		{
		case game_framework::villager:
			Hp = 100;					//血量
			ApDefense = 4;			//魔法防禦
			AdDefense = 2;			//物理防禦
			AttackPower = 20;         //攻擊力
			AttackType = Ad;			//攻擊模式
			break;
		default:
			break;
		}
		//隨機能力
		Hp += randValue[0];
		ApDefense += randValue[1];
		AdDefense += randValue[2];
		AttackPower += randValue[3];
		switch (AttackType)
		{
		case game_framework::Ad:
			movingSpeed = 4;
			break;
		case game_framework::Ap:
			movingSpeed = 5;
			break;
		}
	}
}