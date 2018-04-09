#pragma once
#include <string.h>
using namespace std;
namespace game_framework {
	enum Attack_Type
	{
		Ad,		//���z���� 0
		Ap		//�]�k���� 1		
	};
	enum MovingAnimation_Type { //���ʪ��A
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
		void SetIsAlive(bool flag);
		void BeingAttack(int damge,Attack_Type type);
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
		int GetFloor();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		int GetHp();
		int GetApDefense();
		int GetAdDefense();
		int GetAttackPower();
		Attack_Type GetAttackType();
	protected:
		int _x, _y;				//�y��
		int floor;            //�Ҧb���Ӽh
		int Hp;					//��q
		int ApDefense;			//�]�k���m
		int AdDefense;			//���z���m
		int AttackPower;        //�����O
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isIntoHouse;
		bool isAlive;                //�O�_�s��
		Attack_Type AttackType; //�����Ҧ�
		MovingAnimation_Type nowMovingType;
		CAnimation *animation[7];
	private:

	};
}
