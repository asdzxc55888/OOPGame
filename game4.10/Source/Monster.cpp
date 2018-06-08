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
		RandGender();
		RandName();
		RandBasicAbility();
		Initial();
	}
	Monster::Monster()
	{
		RandGender();
		RandName();
		RandMonsterType();
		RandBasicAbility();
		Initial();
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
		isAlive = obj.isAlive;
		isKid = obj.isKid;
		LoadBitmap(monsterType);
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, monsterType, (int)monsterGender, true, name);

	}

	void Monster::LoadBitmap(string monsterName)
	{
		delete *animation;
		for (int i = 0; i<7; i++)animation[i] = new CAnimation;

		monsterName += ".bmp";
		string strGender = "";
		if (monsterGender == male) {
			strGender = "m_";
		}
		else {
			strGender = "w_";
		}
		string root = "Bitmaps\\monster\\monster_";
		string childStr = "";
		if (isKid)childStr = "child_";
		root += strGender;
		root += monsterName;
		char test[100];
		strcpy(test, root.c_str());
		animation[Forward]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack1_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterBack2_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Back]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft1_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterLeft2_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight1_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterRight2_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Moving_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackLeft1_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackLeft2_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Left]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackRight1_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		root = "Bitmaps\\monster\\monsterAttackRight2_" + childStr + strGender + monsterName;
		strcpy(test, root.c_str());
		animation[Attack_Right]->AddBitmap(test, RGB(255, 255, 255));
		/////////////////////////////////////////////////////////////////////////////////////
		if (!isHeadImgRoad) {
			headImg[0].LoadBitmap("Bitmaps\\headimg\\lookhouse.bmp", RGB(255, 255, 255));
			headImg[1].LoadBitmap("Bitmaps\\headimg\\findhouse.bmp", RGB(255, 255, 255));
			headImg[2].LoadBitmap("Bitmaps\\headimg\\love.bmp", RGB(255, 255, 255));
			isHeadImgRoad = true;
		}
	}

	void Monster::InheritAbility(Monster *father, Monster *mother)
	{
		int randValue[4];
		randValue[0] = rand() % 10;
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 4;
		//��¦��O
		Hp = (father->Hp+mother->Hp)/4 + randValue[0];					//��q
		MaxHp = Hp;
		ApDefense = (father->ApDefense + mother->ApDefense) / 4 + randValue[1];			//�]�k���m
		AdDefense = (father->AdDefense + mother->AdDefense) / 4 + randValue[2];			//���z���m
		AttackPower = (father->AttackPower + mother->AttackPower) / 4 + randValue[3];         //�����O
	}

	void Monster::Initial()
	{
		monsterAge = 0;
		isMouseOn = false;
		isMusicEffectOn = false;
		isKid = false;
		isHeadImgRoad = false;
		HpCount = 0;
		MyBoard = new MonsterDataBoard(Hp, ApDefense, AdDefense, AttackPower, monsterType, (int)monsterGender, true, name);
	}

	void Monster::SetMonsterType(string _monsterType)
	{
		monsterType = _monsterType;
	}
	void Monster::SetMonsterState(Monster_state _state)
	{
		nowMonsterState = _state;
	}
	void Monster::SetIsChild(bool flag)
	{
		isKid = flag;
	}
	void Monster::SetHeadImgcount(int time)
	{
		HeadImgCount = time;
	}
	void Monster::ShowHpBar()
	{
		if (isOnBattle) {
			if (!SHOW_LOAD_PROGRESS)
				return;
			int percent = Hp * 100 / MaxHp;
			const int bar_width = 40;
			const int bar_height = 8;
			const int x1 = _x + 5;
			const int x2 = x1 + bar_width;
			const int y1 = _y;
			const int y2 = y1 + bar_height;
			const int pen_width = bar_height / 8;
			const int progress_x1 = x1 + pen_width;
			const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
			const int progress_x2_end = x2 - pen_width;
			const int progress_y1 = y1 + pen_width;
			const int progress_y2 = y2 - pen_width;

			CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
			CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// �M��pen
			pp = pDC->SelectObject(&p);
			if (percent >= 50) {
				CBrush b2(RGB(0, 255, 0));					// �e���� progrss�i��
				pDC->SelectObject(&b2);
				pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
			}
			else {
				int Green = 255 - (50 - percent) * 8;
				if (Green <= 0)Green = 0;
				CBrush b3(RGB(255, Green, 0));					// �e���� progrss�i��
				pDC->SelectObject(&b3);
				pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);
			}

			pDC->SelectObject(pp);						// ���� pen
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}

	}
	void Monster::OnShow()
	{
		npcObject::OnShow();
		HpResume();
		if (isMouseOn && isOnShow) {                   //����檺���
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
		case game_framework::fallInLove:
			headImg[2].SetTopLeft(_x + 5, _y - 20);
			headImg[2].ShowBitmap();
			break;
		}

		ShowHpBar();             //��ܦ��
		if (isIntoHouse ||(nowMonsterState==fallInLove && HeadImgCount >300)) {
			nowMonsterState = nothing;
		}
		else HeadImgCount++;

		if (isKid && monsterAge > GrowupTime) { //�����ɶ�
			GrowUp();
		}
		else if (isKid) monsterAge++;

	}
	void Monster::MonsterLoad(char * str, int index)
	{
		char indexstr = '0' + index;
		char temp_str[1024] = "Monster" ;
		temp_str[7] = indexstr;
		str = strstr(str, temp_str);
		str += 9;

		str = strstr(str, "MonsterType");         //�Ǫ�����
		str += 12;
		strcpy(temp_str, str);
		monsterType =strtok(temp_str, "\n");

		str = strstr(str, "MonsterName");         //�Ǫ��W�l
		str += 12;
		strcpy(temp_str, str);
		name = strtok(temp_str, "\n");
		
		str = strstr(str, "MonsterGender");         //�ʧO
		str += 14;
		monsterGender = (Gender)atoi(str);

		str = strstr(str, "X");         //�y��
		str += 2;
		_x = atoi(str);
		str = strstr(str, "Y");       
		str += 2;
		_y = atoi(str);

		str = strstr(str, "AttackType");         //�����覡
		str += 11;
		AttackType= (Attack_Type)atoi(str);

		str = strstr(str, "MaxHp");         //��q
		str += 6;
		Hp = atoi(str);
		MaxHp = Hp;

		str = strstr(str, "AttackPower");         //�����O
		str += 12;
		AttackPower= atoi(str);

		str = strstr(str, "AdDenfense");         //���z���m
		str += 11;
		AdDefense= atoi(str);

		str = strstr(str, "ApDenfense");         //���z���m
		str += 11;
		ApDefense = atoi(str);

		str = strstr(str, "IsOnShow");       
		str += 9;
		if (atoi(str) == 0) {
			isOnShow = false;
		}else isOnShow = true;

		Initial();
		LoadBitmap(monsterType);
	}
	Monster_state Monster::GetMonsterState()
	{
		return nowMonsterState;
	}
	MonsterDataBoard* Monster::GetMonsterDataBoard()
	{
		return MyBoard;
	}
	Gender Monster::GetMonsterGendet()
	{
		return monsterGender;
	}
	string Monster::GetMonsterType()
	{
		return monsterType;
	}
	string Monster::GetMonsterName()
	{
		return name;
	}
	int Monster::GetMonsterGender()
	{
		return monsterGender;
	}
	bool Monster::GetIsKid()
	{
		return isKid;
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
		string totalMonsterType[totalMonsterType_size] = { "tentacle","kappa","eye" };
		int result = rand() % totalMonsterType_size;
		monsterType = totalMonsterType[result];
	}
	void Monster::RandBasicAbility()   //�H����O
	{
		int randValue[4];
		randValue[0] = rand() % 20;
		for (int i = 1; i < 4; i++)randValue[i] = rand() % 4;
		//��¦��O
		if (monsterType == "tentacle") {
			AttackType = Ap;
			Hp = 100;					//��q
			ApDefense = 3;			//�]�k���m
			AdDefense = 2;			//���z���m
			AttackPower = 10;         //�����O
			AttackType = Ap;			//�����Ҧ�
		}
		else if (monsterType == "kappa") {
			Hp = 120;					//��q
			ApDefense = 2;			//�]�k���m
			AdDefense = 3;			//���z���m
			AttackPower = 12;         //�����O
			AttackType = Ad;			//�����Ҧ�
		}
		else if (monsterType == "eye") {
			Hp = 140;					//��q
			ApDefense = 4;			//�]�k���m
			AdDefense = 3;			//���z���m
			AttackPower = 14;         //�����O
			AttackType = Ad;			//�����Ҧ�
		}
		//�H����O
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
	void Monster::HpResume()
	{
		if (Hp < MaxHp) {
			if (HpCount > (500) - (timeLevel * 150)) {
				Hp += MaxHp / 50;
				if (Hp > MaxHp)Hp = MaxHp;
				HpCount = 0;
			}
			else HpCount++;
		}
	}
	void Monster::GrowUp()
	{
		isKid = false;
		LoadBitmap(monsterType);
		_y -= 20; //���׭ץ�
		Hp *=2;					//��q
		MaxHp *=2;
		ApDefense*=2;			//�]�k���m
		AdDefense*=2;			//���z���m
		AttackPower *=2;         //�����O
	}
}
