#pragma once
#include <string.h>
#include "MagicAttack.h"
#include "MonsterDataBoard.h"
using namespace std;
namespace game_framework
{
enum Attack_Type{ Ad,	 Ap};
enum MovingAnimation_Type   //���ʪ��A
{
    Forward,       //�V�e
    Back,			//�V��
    Moving_Left,
    Moving_Right,
    Attack_Left,
    Attack_Right,
    Hide
};
class npcObject
{
    public:
        npcObject();
        ~npcObject();
        void operator=(npcObject obj);
        void OnMove();			// ����
        void OnShow();			// �N�ϧζK��e��
        void SetPoint(int _x, int _y);
        void SetMovingType(MovingAnimation_Type _MovingType);
        void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
        void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
        void SetMovingRight(bool flag); // �]�w�O�_���b���k����
        void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
        void SetIntoHouse(bool flag);
        void SetIsGoOutside(bool flag); //�O�_�~�X
        void SetIsAlive(bool flag);     //�O�_����
        void SetIsOnBattle(bool flag);  //�O�_�b�԰�
        void SetBattleTemp(bool flag);
        void BeingAttack(int damge, Attack_Type type);
		void SetTimeLevel(int _timeLevel);
        int GetFloor();
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();
        int GetHp();
        int GetApDefense();
        int GetAdDefense();
        int GetAttackPower();
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
        bool MagicAttack_event(int _x1, int _x2, string type);
        bool PhysicalAttack_event(int tar_x1, int tar_x2);
        bool GetIsOnBattle();
        bool GetIsAlive();
        bool IsMouseOn(CPoint point);
        Attack_Type GetAttackType();
		MovingAnimation_Type GetMovingType();
    protected:
        int _x, _y;				//�y��
        int movingSpeed;     //���ʳt��
        int floor;            //�Ҧb���Ӽh
        int MaxHp;
        int Hp;					//��q
        int ApDefense;			//�]�k���m
        int AdDefense;			//���z���m
        int AttackPower;        //�����O
		int timeLevel;           //�]�w�ɶ��ֺC
		int AttackCount;        //�����P�w�ɶ�
		int timecount;
        bool isMovingDown;			// �O�_���b���U����
        bool isMovingLeft;			// �O�_���b��������
        bool isMovingRight;			// �O�_���b���k����
        bool isMovingUp;			// �O�_���b���W����
        bool isIntoHouse;
        bool isGoOutside;
        bool isAlive;                //�O�_�s��
        bool isFirstShot;
        bool isOnBattle;
        bool isMusicEffectOn;
        bool isMouseOn;
		bool isKid;                 //�O�_���p��(�Ǫ�)
        bool BattleTemp;
        Attack_Type AttackType; //�����Ҧ�
        MovingAnimation_Type nowMovingType;
        CAnimation* animation[7];
        MagicAttack* magicAttack[3];
        time_t nowTime, setTime;
    private:
};
}
