#pragma once
#include "npcObject.h"

namespace game_framework {
	enum Monster_state {
		wolking,
		findHouse
	};
	class Monster :public npcObject
	{
	public:
		Monster(string _monsterTpye);
		Monster();
		void operator= (Monster &obj);
		void SetMonsterType(string _monsterType);	//�]�w�Ǫ����� �ǤJ�������r��
		void SetMonsterState(Monster_state _state);	//�o�w�Ǫ����A
		void SetMonsterIsExist(bool flag);			//�]�w�Ǫ��O�_��ܦb�a�ϤW
		Monster_state GetMonsterState();            //�����Ǫ����A
		string GetMonsterType();
		bool GetIsExist();							//���o�Ǫ��O�_��ܦb�a�ϤW
	private:
		string monsterType;                          //�Ǫ�����
		Monster_state nowMonsterState;				//�Ǫ���e���A
		bool isExist;
	};
	
}
