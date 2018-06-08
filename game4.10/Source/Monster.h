#pragma once
#include "npcObject.h"
class Warrior;
#include"Warrior.h"
#define totalMonsterType_size  4
#define GrowupTime 3000
namespace game_framework {
	enum Monster_state {
		leave,
		nothing,
		working,
		lookHouse,
		findHouse,
		finishhouse,
		fallInLove,
	};
	enum Gender {male,female};
	class Monster :public npcObject
	{
	public:
		Monster(string _monsterTpye);
		Monster();
		void operator= (Monster &obj);
		void LoadBitmap(string monsterName);
		void InheritAbility(Monster *father,Monster *mother);    //�Ǫ��~�ӯ�O
		void Initial();                                          //��l��
		void SetMonsterType(string _monsterType);	//�]�w�Ǫ����� �ǤJ�������r��
		void SetMonsterState(Monster_state _state);	//�o�w�Ǫ����A
		void SetIsChild(bool flag);
		void SetHeadImgcount(int time);
		void ShowHpBar();
		void OnShow();
		void MonsterLoad(char *str, int index);
		Monster_state GetMonsterState();            //�����Ǫ����A
		MonsterDataBoard* GetMonsterDataBoard();
		Gender GetMonsterGendet();
		string GetMonsterType();
		string GetMonsterName();
		int GetMonsterGender();
		bool GetIsKid();
		bool IsMouseOn(CPoint point);
	private:
		int monsterAge;
		int HpCount;          //�ͩR�^�_�p��
		int HeadImgCount;
		void RandMonsterType();
		void RandBasicAbility();
		void RandName();
		void RandGender();
		void HpResume();
		void GrowUp();                              //�Ǫ����j
		bool isMusicEffectOn;
		bool isMouseOn;
		bool isHeadImgRoad;
		string name;                                //�Ǫ��W��
		string monsterType;                         //�Ǫ�����
		Gender monsterGender;                       //�Ǫ��ʧO
		Monster_state nowMonsterState;				//�Ǫ���e���A
		MonsterDataBoard *MyBoard;                  //��T��
<<<<<<< HEAD
		CMovingBitmap headImg[4];                      //�Y�W�Ÿ�
=======
		CMovingBitmap headImg[3];                   //�Y�W�Ÿ�
>>>>>>> 3b21e7391739cf8b94bdfad85e11d65b170ab95e

	};
	
}
