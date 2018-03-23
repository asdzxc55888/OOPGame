#pragma once
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
		Moving_Right
	};
	class npcObject
	{
	public:
		npcObject();
		~npcObject();
		void LoadBitmap(string monsterName);		// ���J�ϧ�
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
		void SetPoint(int _x, int _y);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		int GetX();				
		int GetY();
		int GetHp();
		int GetApDefense();
		int GetAdDefense();
		int GetAttackPower();
		int GetAttackType();

	private:
		int _x, _y;				//�y��
		int Hp;					//��q
		int ApDefense;			//�]�k���m
		int AdDefense;			//���z���m
		int AttackPower;        //�����O
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		
		CAnimation  *animation[4];   //�ʵe
		Attack_Type AttackType; //�����Ҧ�
		MovingAnimation_Type nowMovingType;
	};
}
