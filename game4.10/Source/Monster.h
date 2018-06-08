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
		void InheritAbility(Monster *father,Monster *mother);    //怪物繼承能力
		void Initial();                                          //初始化
		void SetMonsterType(string _monsterType);	//設定怪物種類 傳入物種類字串
		void SetMonsterState(Monster_state _state);	//這定怪物狀態
		void SetIsChild(bool flag);
		void SetHeadImgcount(int time);
		void ShowHpBar();
		void OnShow();
		void MonsterLoad(char *str, int index);
		Monster_state GetMonsterState();            //取的怪物狀態
		MonsterDataBoard* GetMonsterDataBoard();
		Gender GetMonsterGendet();
		string GetMonsterType();
		string GetMonsterName();
		int GetMonsterGender();
		bool GetIsKid();
		bool IsMouseOn(CPoint point);
	private:
		int monsterAge;
		int HpCount;          //生命回復計數
		int HeadImgCount;
		void RandMonsterType();
		void RandBasicAbility();
		void RandName();
		void RandGender();
		void HpResume();
		void GrowUp();                              //怪物長大
		bool isMusicEffectOn;
		bool isMouseOn;
		bool isHeadImgRoad;
		string name;                                //怪物名稱
		string monsterType;                         //怪物類型
		Gender monsterGender;                       //怪物性別
		Monster_state nowMonsterState;				//怪物當前狀態
		MonsterDataBoard *MyBoard;                  //資訊欄
<<<<<<< HEAD
		CMovingBitmap headImg[4];                      //頭上符號
=======
		CMovingBitmap headImg[3];                   //頭上符號
>>>>>>> 3b21e7391739cf8b94bdfad85e11d65b170ab95e

	};
	
}
