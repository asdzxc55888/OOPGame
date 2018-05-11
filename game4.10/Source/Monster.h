#pragma once
#include "npcObject.h"
class Warrior;
#include"Warrior.h"
#define totalMonsterType_size  2
namespace game_framework {
	enum Monster_state {
		leave,
		nothing,
		wolking,
		lookHouse,
		findHouse,
		fallInLove
	};
	enum Gender {
		male,
		female
	};
	class Monster :public npcObject
	{
	public:
		Monster(string _monsterTpye);
		Monster();
		void operator= (Monster &obj);
		void LoadBitmap(string monsterName);
		void SetMonsterType(string _monsterType);	//�]�w�Ǫ����� �ǤJ�������r��
		void SetMonsterState(Monster_state _state);	//�o�w�Ǫ����A
		void SetMonsterIsExist(bool flag);			//�]�w�Ǫ��O�_��ܦb�a�ϤW
		void SetIsChild(bool flag);
		void ShowHpBar();
		void OnShow();
		Monster_state GetMonsterState();            //�����Ǫ����A
		string GetMonsterType();
		string GetMonsterName();
		int GetMonsterGender();
		bool GetIsExist();							//���o�Ǫ��O�_��ܦb�a�ϤW
		bool IsMouseOn(CPoint point);
	private:
		void RandMonsterType();
		void RandBasicAbility();
		void RandName();
		void RandGender();
		bool isMusicEffectOn;
		bool isExist;
		bool isMouseOn;
		string name;
		string monsterType;                         //�Ǫ�����
		Gender monsterGender;
		Monster_state nowMonsterState;				//�Ǫ���e���A
		MonsterDataBoard *MyBoard;                  //��T��
		CMovingBitmap headImg[3];                      //�Y�W�Ÿ�

	};
	
}
