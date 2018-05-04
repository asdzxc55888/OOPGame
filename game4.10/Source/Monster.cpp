#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include<iostream>
#include<fstream>
#include<vector>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"

using namespace std;
namespace game_framework {
	Monster::Monster(string _monsterTpye)
	{
		monsterType = _monsterTpye;
		RandName();
		RandBasicAbility();
		isExist = false;
		isMouseOn = false;
		isMusicEffectOn = false;
	}
	Monster::Monster()
	{
		RandGender();
		RandName();
		RandMonsterType();
		RandBasicAbility();
		isExist = false;
		isMouseOn = false;
		isMusicEffectOn = false;
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, monsterType, true,name);
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
		isAlive = obj.isAlive;
		LoadBitmap(monsterType);
		isExist = true;
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, monsterType, true,name);

	}

	void Monster::LoadBitmap(string monsterName)
	{
		monsterName += ".bmp";
		string strGender = "";
		if (monsterGender == male) {
			strGender = "m_";
		}
		else {
			strGender = "w_";
		}
		string root = "Bitmaps\\monster\\monster_";
		root += strGender;
		root += monsterName;
		char test[100];
		strcpy(test, root.c_str());
		animation[Forward]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack1_"+ strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack2_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft1_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft2_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight1_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight2_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackLeft1_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackLeft2_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackRight1_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackRight2_" + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		animation[Hide]->AddBitmap("Bitmaps\\monster\\monsterHide.bmp", RGB(255, 255, 255));
		/////////////////////////////////////////////////////////////////////////////////////

		headImg[0].LoadBitmap("Bitmaps\\headimg\\lookhouse.bmp", RGB(255, 255, 255));
		headImg[1].LoadBitmap("Bitmaps\\headimg\\findhouse.bmp", RGB(255, 255, 255));
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
	void Monster::ShowHpBar()
	{
		if (isOnBattle) {
			if (!SHOW_LOAD_PROGRESS)
				return;
			int percent = Hp * 100 / MaxHp;
			const int bar_width = 50;
			const int bar_height = 8;
			const int x1 = _x ;
			const int x2 = x1 + bar_width;
			const int y1 = _y ;
			const int y2 = y1 + bar_height;
			const int pen_width = bar_height / 8;
			const int progress_x1 = x1 + pen_width;
			const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
			const int progress_x2_end = x2 - pen_width;
			const int progress_y1 = y1 + pen_width;
			const int progress_y2 = y2 - pen_width;

			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
			pp = pDC->SelectObject(&p);
			if (percent >= 50) {
				CBrush b2(RGB(0, 255, 0));					// 畫黃色 progrss進度
				pDC->SelectObject(&b2);
				pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
			}
			else {
				int Green = 255 - (50 - percent) * 8;
				if (Green <= 0)Green = 0;
				CBrush b3(RGB(255, Green, 0));					// 畫黃色 progrss進度
				pDC->SelectObject(&b3);
				pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
			}

			pDC->SelectObject(pp);						// 釋放 pen
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}

	}
	void Monster::OnShow()
	{
		npcObject::OnShow();

		if (isMouseOn && nowMovingType != Hide) {                   //資料欄的顯示
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

		switch (nowMonsterState)
		{
		case game_framework::lookHouse:
			headImg[0].SetTopLeft(_x + 5, _y - 20);
			headImg[0].ShowBitmap();
			break;
		case game_framework::findHouse:
			headImg[1].SetTopLeft(_x + 5, _y - 20);
			headImg[1].ShowBitmap();
			break;
		}

		ShowHpBar();             //顯示血條
	}
	Monster_state Monster::GetMonsterState()
	{
		return nowMonsterState;
	}
	string Monster::GetMonsterType()
	{
		return monsterType;
	}
	string Monster::GetMonsterName()
	{
		return name;
	}
	bool Monster::GetIsExist()
	{
		return isExist;
	}
	bool Monster::IsMouseOn(CPoint point)
	{
		if (point.x > _x && point.x <= _x + GetWidth() && point.y > _y && point.y <= _y + GetHeight()) {
			isMouseOn = true;
			return isMouseOn;
		}
		isMouseOn = false;
		return isMouseOn;
	}
	void Monster::RandMonsterType()
	{
		string totalMonsterType[totalMonsterType_size] = { "tentacle","kappa" };
		int result = rand() % totalMonsterType_size;
		monsterType = totalMonsterType[result];
	}
	void Monster::RandBasicAbility()   //隨機能力
	{
		int randValue[4];
		randValue[0] = rand() % 20;
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 4;
		//基礎能力
		if (monsterType == "tentacle") {
			AttackType = Ap;
			Hp = 100;					//血量
			ApDefense = 3;			//魔法防禦
			AdDefense = 2;			//物理防禦
			AttackPower = 10;         //攻擊力
			AttackType = Ap;			//攻擊模式
		}
		else if (monsterType == "kappa") {
			Hp = 120;					//血量
			ApDefense = 2;			//魔法防禦
			AdDefense = 3;			//物理防禦
			AttackPower = 12;         //攻擊力
			AttackType = Ad;			//攻擊模式
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
	void Monster::RandName()
	{
		char line[50] = "";
		int count = 0;
		vector<string> nameData;
		fstream nameFile;
		nameFile.open("Source\\NameData.txt", ios::in);
		while (nameFile.getline(line, sizeof(line), '\n')) {
			nameData.push_back(line);
			count++;
		}
		int randValue = rand() % count;
		name = nameData[randValue];
	}
	void Monster::RandGender()
	{
		int randValue = rand() % 2;
		monsterGender = (Gender)randValue;
	}
}