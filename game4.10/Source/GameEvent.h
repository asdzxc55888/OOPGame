#pragma once
#include "Room.h"
#include "Warrior.h"
#include "obstacle.h"
#include "TaskBoard.h"
namespace game_framework {
	class GameEvent
	{
	public:
		GameEvent();
		~GameEvent();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnEvent();                                 // �ƥ�B�z
		bool GameOver();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetObstacle();
		bool GetIsRoomFull();     //�ЫάO�_�Ⱥ�
		////////////////////////////////////////////////////////////////////////////�Ǫ��ƥ�////////////////////////////////////////////////////////
		void MonsterFindHouse(Monster **_monster); //�Ǫ��ݫΨƥ� 
		void MonsterlivingHouse_event(Room* _room, Monster** _monster);
		void MonsterGohome_event(Room *_room, int monsterIndex);                  //�Ǫ��i�Шƥ�A���P�Ǫ���Ψƥ�
		void MonsterBeingClick(Monster **_monster); //�Ǫ��Q�I���ƥ�
		bool MonsterLeave(Monster **_monster);                                      //�Ǫ����}�A�����������������}
		bool Moving(Monster **_monster, int x, int floor);                          //�Ǫ�����
		bool MovingLR(Monster **_monster, int x);
		bool HitWarrior(Monster* _monster, Warrior* _warrior);          //�P�_���L�I��i��
		void CreateMonster_event(Monster **_monster);
		////////////////////////////////////////////////////////////////////////////�i�̨ƥ�//////////////////////////////////////////////////////////
		bool Moving(Warrior **_warrior, int x, int floor);
		bool MovingLR(Warrior **_warrior, int x);
		void CreateWarrior_event(Warrior **_warrior, warrior_type type);
		void DeleteWarrior_event(Warrior **_warrior);
		bool HitMonster(Warrior *_warrior, Monster *_monster);
		/////////////////////////////////////////////////////////////////////////////////�԰��ƥ�/////////////////////////////////////////////////////
		void WarriorAttack_event(Warrior *_warrior, Monster **target);
		void MonsterAttack_event(Monster *_monster, Warrior ** target);
		void MonsterPositionFix();        //�Ǫ���m�ץ�
		Monster* findMonsterTarget(Warrior *_warrior);
		Warrior* findWarriorTarget(Monster *_monster);
		void BattleEnd();
		void SeleteTaskBattle();
		void BattleTest1();
		///////////////////////////////////////////////////////////////////�ɶ�����//////////////////////////////////////////////////////////////////
		void timeControl();
		//////////////////////////////////////////////////////////////////////�ʷR�ƥ�///////////////////////////////////////////////////
		void ComingMonsterFallInLoveEvent();             //���X�Ǫ��ʷR�ƥ�
		void MonsterMatingEvent();    //�Ǫ���t�ƥ�
		void MonsterBorn(int roomNum);  //�Ǫ��X��
	private:
		CMovingBitmap Background;                  //�I����
		CMovingBitmap Warning;                    //ĵ�i��
		CAnimation SpeedControlBtn[3];            //�t�ױ����
		CInteger Money;
		TaskBoard myTaskBoard;
		Obstacle mapObstacle;
		Room* gameRoom[4];
		Monster* comingMonster;                    //�ӬݩФl���Ǫ�
		Warrior* warrior[10];
		time_t Settime, nowtime;
		int TimeLevel;                            //�ɶ��ֺC
		int Clock;
		int houseLevele;
		int roomSize;
		int battleCount;
		bool isGamePause;
		bool isIntoBattle;                        //�O�_��i�J�԰�
		bool isOnBattle;						  //�O�_�b�԰�
		bool isSpeedControlOn[3];
		bool isMonsterDataBoardShow;
		bool isMonsterGoingOut;
		bool GameOverFlag;                       //���H�J��N��true �P�_�O�_���C����}�l
		bool WarningQuit;
	};
	
}