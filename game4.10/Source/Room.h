#pragma once
#include "Monster.h"
namespace game_framework
{
	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,				// 2
		AUDIO_DOOROPEN,
		AUDIO_DOORCLOSE
	};
class Room
{
    public:
        Room(int x, int y);
        ~Room();
        void LoadBitmap();
		void OnShow(bool flag);//true ��������� false�����Ǫ����
        void OnMove();
        Monster* GetLiveMonster();
		bool GetIsMonsterLiving();
		bool GetIsMonsterIn();
		bool GetIsMonsterFight();
		void LetMonsterGohome();
		bool IsMouseOn(CPoint point); //�ˬd�ƹ��O�_�b�W��
		bool MovingLR(int x);
		void SetMonsterFight(bool flag);
		void SetIsMonsterIn(bool flag);
        void SetMonsterlivingRoom(Monster **_monster); //���Ǫ���i�Фl�A�^��NULL���бN�쥻���Ǫ��٥h
    private:
        int _x, _y; //�y��
		int counter;
		int floor;
        Monster liveMonster;	//�~��Ǫ�
        CAnimation animation;  //�ʵe
		void SetMonsterIntohome(); //�Ǫ��i�����ʧ@
		bool MonsterGoHome(); //�Y�٨S��F�a�̱o���СA�^�� true �A��F�F�^��false
		bool isMonsterLiving; //�O�_�~��Ǫ�
        bool isMonsterIn;		//�~���Ǫ��O�_�b�̭�
        bool isDoorOpen;		//�����S���}
		bool isMonsterGoHome;	//�Ǫ��O�_���b���ʶi��
		bool isMonsterFight;    //�Ǫ��O�_�԰�
};
}


