#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	enum Attack_Type
	{
		Ad,		//���z���� 0
		Ap		//�]�k���� 1		
	};
	class npcObject
	{
	public:
		npcObject();
		~npcObject();
		void LoadBitmap();		// ���J�ϧ�
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
		int x, y;				//�y��
		int Hp;					//��q
		int ApDefense;			//�]�k���m
		int AdDefense;			//���z���m
		int AttackPower;        //�����O
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		CAnimation animation;   //�ʵe
		Attack_Type AttackType; //�����Ҧ�

	};
}
