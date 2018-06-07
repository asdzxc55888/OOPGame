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
		case game_framework::firemagic:
			LoadBmpString = "firemagic";
			break;
		default:
			break;
		}
		LoadBitmap(LoadBmpString);
		RandBasicAbility();
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, LoadBmpString,0,false," ");
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
		case game_framework::firemagic:
			LoadBmpString = "firemagic";
			warriorType = firemagic;
			break;
		default:
			break;
		}
		LoadBitmap(LoadBmpString);
		RandBasicAbility();
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, LoadBmpString,0,false," ");
	}
	Warrior::~Warrior()
	{
		delete MyBoard;
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
	}
	void Warrior::OnShow()
	{
		npcObject::OnShow();
		if (isMouseOn ) {                   //資料欄的顯示
			if (!isMusicEffectOn) {
				CAudio::Instance()->Play(AUDIO_DING);
				isMusicEffectOn = true;
			}
			MyBoard->SetData(Hp, MaxHp, ApDefense, AdDefense, AttackPower);
			MyBoard->OnShow();
		}
		else {
			isMusicEffectOn = false;
		}

	}
	string Warrior::GetWarriorType()
	{
		switch (warriorType)
		{
		case game_framework::villager:
			return "villager";
			break;
		case game_framework::firemagic:
			return "firemagic";
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
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 4;
		//基礎能力
		switch (warriorType)
		{
		case game_framework::villager:
			Hp = 200;					//血量
			ApDefense = 3;			//魔法防禦
			AdDefense = 3;			//物理防禦
			AttackPower = 10;         //攻擊力
			AttackType = Ad;			//攻擊模式
			break;
		case game_framework::firemagic:
			Hp = 200;
			ApDefense = 3;
			AdDefense = 3;
			AttackPower = 10;
			AttackType = Ap;
			break;
		default:
			break;
		}
		//隨機能力
		Hp += randValue[0];
		MaxHp = Hp;
		ApDefense += randValue[1];
		AdDefense += randValue[2];
		AttackPower += randValue[3];
		switch (AttackType)
		{
		case game_framework::Ad:
			movingSpeed = 2;
			break;
		case game_framework::Ap:
			movingSpeed = 2;
			break;
		}
	}
}