#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
namespace game_framework
{
GameEvent::GameEvent()
{
	comingMonster = NULL;
	Clock = NULL;
	int room_x = 650, room_y = 510;

	for (int i = 0; i < 4; i++)gameRoom[i] = new Room(room_x + i * 115, room_y);
}

GameEvent::~GameEvent()
{
}

void GameEvent::OnBeginState()
{
	Warning.SetTopLeft(-1280, 100);
	roomSize = 4;
	battleCount = 0;
	addMoney = 0;
	riseMoney = 0;
	Clock = int(time(&nowtime)) + 60000;
	isGamePause = false;
	GameOverFlag = false;
	isOnBattle = false;
	isIntoBattle = false;
	isMonsterGoingOut = false;
	WarningQuit = false;
	isMonsterDataBoardShow = false;
	myMoney.SetValue(1000);
	///////////////////////////時間設定/////////////////////
	TimeLevel = 1;
	isSpeedControlOn[0] = true;

	for (int i = 1; i < 3; i++)isSpeedControlOn[i] = false;

	////////////////////////////////////////////////////////
	for (int i = 0; i < 10; i++)warrior[i] = NULL;
}

void GameEvent::OnInit()
{
	Background.LoadBitmap("Bitmaps\\gameBackground1.bmp");
	Warning.LoadBitmap("Bitmaps\\Warning.bmp", RGB(255, 255, 255));
	myTaskBoard.LoadBitmap();
	SpeedControlBtn[0].AddBitmap("Bitmaps\\gameRun\\SpeedButton1_2.bmp", RGB(255, 255, 255));
	SpeedControlBtn[0].AddBitmap("Bitmaps\\gameRun\\SpeedButton1_1.bmp", RGB(255, 255, 255));
	SpeedControlBtn[1].AddBitmap("Bitmaps\\gameRun\\SpeedButton2_2.bmp", RGB(255, 255, 255));
	SpeedControlBtn[1].AddBitmap("Bitmaps\\gameRun\\SpeedButton2_1.bmp", RGB(255, 255, 255));
	SpeedControlBtn[2].AddBitmap("Bitmaps\\gameRun\\SpeedButton3_2.bmp", RGB(255, 255, 255));
	SpeedControlBtn[2].AddBitmap("Bitmaps\\gameRun\\SpeedButton3_1.bmp", RGB(255, 255, 255));
	SpeedControlBtn[0].SetTopLeft(1035, 675);
	SpeedControlBtn[1].SetTopLeft(1122, 675);
	SpeedControlBtn[2].SetTopLeft(1209, 675);
	///////////////////////////////////////////////////////////////////
	CAudio::Instance()->Load(AUDIO_DOOROPEN, "Sounds\\RoomOpen.mp3");
	CAudio::Instance()->Load(AUDIO_DOORCLOSE, "Sounds\\RoomClose.mp3");
	CAudio::Instance()->Load(AUDIO_WARNING, "Sounds\\battle.mp3");

	for (int i = 0; i < 4; i++)gameRoom[i]->LoadBitmap();
	myTaskBoard.Initial();
}

void GameEvent::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭

	if (nChar == KEY_LEFT)
	{
	}
	else if (nChar == KEY_RIGHT)
	{
	}
	else if (nChar == KEY_UP)
	{
		BattleTest1();
	}
	else if (nChar == KEY_DOWN)  //測試
	{
		riseMoney = 0;
		addMoney = -100;
	}
}

void GameEvent::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (comingMonster != NULL && comingMonster->IsMouseOn(point)) //若點選到拜訪的怪物
	{
		MonsterBeingClick(&comingMonster);
	}

	for (int i = 0; i < 3; i++)                                  //時間控制按鈕
	{
		int _x = SpeedControlBtn[i].Left();
		int _x2 = _x + SpeedControlBtn[i].Width();
		int _y = SpeedControlBtn[i].Top();
		int _y2 = SpeedControlBtn[i].Height() + _y;

		if (point.x > _x && point.x <= _x2 && point.y > _y && point.y <= _y2)
		{
			if (!isSpeedControlOn[i])
			{
				CAudio::Instance()->Play(AUDIO_DING);

				for (int k = 0; k < 3; k++)isSpeedControlOn[k] = false;

				isSpeedControlOn[i] = true;
			}
		}
	}
	if(myTaskBoard.IsTaskOnClick(point))isGamePause=true;
}

void GameEvent::OnMouseMove(UINT nFlags, CPoint point)
{
	for (int i = 0; i < 4; i++) {                            //處理介面顯示
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonster(k)->IsMouseOn(point) && gameRoom[i]->GetLiveMonster(k)->GetMovingType() != Hide) {
				isMonsterDataBoardShow = true;
				i = 5;
				break;
			}
			isMonsterDataBoardShow = false;
		}
	}
	for (int i = 0; i < 4; i++) {                            //處理介面顯示
		if (!isMonsterDataBoardShow) {
			if(gameRoom[i]->IsMouseOn(point))gameRoom[i]->SetRoomBoard();
		}
	}

	if (comingMonster != NULL) {                            //處理介面顯示
		comingMonster->IsMouseOn(point);
	}
	for (int i = 0; i < 10; i++) {                          //處理介面顯示
		if (warrior[i] != NULL) {
			warrior[i]->IsMouseOn(point);
		}
	}
	myTaskBoard.IsMouseOnTaskBoard(point);
}

void GameEvent::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (isOnBattle)
	{
		for (int i = 0; i < roomSize; i++)
		{
			for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
				Monster* _monster = gameRoom[i]->GetLiveMonster(k);

				if (_monster->GetIsOnBattle() && _monster->IsMouseOn(point))  //怪物被點擊的事件，怪物回家
				{
					MonsterGohome_event(gameRoom[i], k);
					_monster->SetIsOnBattle(false);
					return;
				}
			}
			for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
				if (gameRoom[i]->IsMouseOn(point) && gameRoom[i]->GetIsMonsterIn(k))//房屋被點擊的事件，怪物戰鬥
				{
					gameRoom[i]->SetMonsterFight(true);
					isMonsterGoingOut = true;
				}

			}
		}
	}
	if(myTaskBoard.OnRButtonDown(nFlags, point))isGamePause=false;
}

void GameEvent::OnMove()
{
	if (!isGamePause) {
		/////////////////////////////////時間控制按鈕////////////////////////////////////////////
		for (int i = 0; i < 3; i++)
		{
			if (isSpeedControlOn[i])
			{
				if (!SpeedControlBtn[i].IsFinalBitmap())
				{
					SpeedControlBtn[i].OnMove();
				}
			}
			else
			{
				SpeedControlBtn[i].Reset();
			}
		}

		timeControl();

		for (int i = 0; i < roomSize; i++)
		{
			for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
			{
				gameRoom[i]->GetLiveMonster(k)->SetTimeLevel(TimeLevel);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (warrior[i] != NULL) warrior[i]->SetTimeLevel(TimeLevel);
		}

		if (comingMonster != NULL)comingMonster->SetTimeLevel(TimeLevel);

		/////////////////////////////////時間控制按鈕/////////////////////////////////////////////////
		OnEvent();

		if (Warning.Left() > -1280)                                    //警告圖片向左移動
		{
			Warning.SetTopLeft(Warning.Left() - 6 * TimeLevel, Warning.Top());
		}

		if (comingMonster != NULL)
		{
			comingMonster->OnMove();
		}

		for (int i = 0; i < 10; i++)
		{
			if (warrior[i] != NULL)
			{
				warrior[i]->OnMove();
			}
		}

		for (int i = 0; i < 4; i++)
		{
			gameRoom[i]->OnMove();
		}
	}
	myMoney.OnMove();
}

void GameEvent::OnShow()
{
	Background.ShowBitmap();
	SpeedControlBtn[0].OnShow();
	SpeedControlBtn[1].OnShow();
	SpeedControlBtn[2].OnShow();

	for (int i = 0; i < 4; i++)gameRoom[i]->OnShow(true);

	for (int i = 0; i < 4; i++)gameRoom[i]->OnShow(false);

	for (int i = 0; i < 10; i++)
	{
		if (warrior[i] != NULL)
		{
			warrior[i]->OnShow();
		}
	}

	if (comingMonster != NULL)
	{
		comingMonster->OnShow();
	}
	myMoney.OnShow();
	Warning.ShowBitmap();
	myTaskBoard.OnShow();
}

void GameEvent::OnEvent()
{
	SeleteTaskBattle();
	if (isIntoBattle)  ////////////////////////////////////////////////進入戰鬥時的事件
	{
		Warning.SetTopLeft(1280, 100); //警告圖片
		CAudio::Instance()->Stop(AUDIO_GAMEBGM);
		CAudio::Instance()->Play(AUDIO_WARNING);

		if (comingMonster != NULL)comingMonster->SetMonsterState(leave); //拜訪怪物離開

		for (int i = 0; i < roomSize; i++)
		{
			for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
			{
				if (gameRoom[i]->GetIsMonsterLiving() && !gameRoom[i]->GetIsMonsterIn(k))
				{
					MonsterGohome_event(gameRoom[i], k);
				}
			}
		}

		Clock = int(time(&nowtime));
		isIntoBattle = false;
		isOnBattle = true;
	}
	//////////////////////////////////////////////////////////////////////////設置障礙物
	mapObstacle.Initial();
	SetObstacle();

	/////////////////////////////////////////////////////////////////////////////勇者攻擊事件
	if (isOnBattle && difftime(time(&nowtime), Clock) > 5)
	{
		for (int i = 0; i < 10; i++) {
			if (warrior[i] != NULL)
			{
				Monster* target = findMonsterTarget(warrior[i]);

				if (target != NULL)
				{
					WarriorAttack_event(warrior[i], &target);
				}
				else
				{
					Moving((&warrior[i]), 700, 1);
				}
			}
		}
	}

	for (int i = 0; i < roomSize; i++)                        //判斷怪物是否活著
	{
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
		{
			Monster* _monster = gameRoom[i]->GetLiveMonster(k);

			if (_monster != NULL)
			{
				if (!_monster->GetIsAlive())
				{
					gameRoom[i]->MonsterDeath(k);
					gameRoom[i]->SetRoomBoard();
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////怪物攻擊事件
	if (isOnBattle)
	{
		for (int i = 0; i < roomSize; i++)
		{
			for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
				if (gameRoom[i]->GetLiveMonster(k) != NULL && gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())
				{
					Monster* _monster = gameRoom[i]->GetLiveMonster(k);
					Warrior* target = findWarriorTarget(_monster);
					Warrior* temp = target;
					if (target != NULL)
					{
						MonsterAttack_event(_monster, &target);
						if (target == NULL) {                   //刪除勇士記憶體
							for (int n = 0; n < 10; n++) {
								if (temp == warrior[n])
								{
									warrior[n] = NULL;
									break;
								}
							}
						}
					}
					else                                           //結束戰鬥
					{
						//BattleEnd(gameRoom, roomSize);
						CAudio::Instance()->Stop(AUDIO_WARNING);
						CAudio::Instance()->Play(AUDIO_GAMEBGM);
						isOnBattle = false;
						BattleFinish();
						break;
					}
				}
			}
		}
	}
	if (!isOnBattle) {
		BattleEnd();
	}

	MonsterPositionFix();
	//////////////////////////////////////////////////////////////////////////////////////來臨怪物事件
	if (comingMonster != NULL)
	{
		Monster_state comingMonsterState = comingMonster->GetMonsterState();
		int randvalue = rand() % 2000;

		switch (comingMonsterState)
		{
		case game_framework::leave:
			MonsterLeave(&comingMonster);
			break;

		case game_framework::nothing:
			MonsterFindHouse(&comingMonster);
			break;

		case game_framework::lookHouse:
			MonsterFindHouse(&comingMonster);    //怪物找房
			break;

		case game_framework::findHouse:
			if (randvalue < 5 * TimeLevel)
			{
				comingMonster->SetMonsterState(leave);
			}
			break;

		default:
			break;
		}
	}
	else
	{
		if (!isOnBattle)CreateMonster_event(&comingMonster);
	}

	if (!isOnBattle)	MonsterMatingEvent();   //怪物交配事件
}

bool GameEvent::GameOver()
{
	if (GameOverFlag) {
		for (int i = 0; i < roomSize; i++) {
			if (gameRoom[i]->GetLiveMonsterSize() > 0) {
				return false;
			}
		}
		CAudio::Instance()->Stop(AUDIO_WARNING);
		return true;
	}
	return false;
}

void GameEvent::SetObstacle()
{
	for (int i = 0; i < roomSize; i++)
	{
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetIsMonsterFight(k) && gameRoom[i]->GetLiveMonster(k)->GetMovingType() != Hide)
			{
				Monster* _monster = gameRoom[i]->GetLiveMonster(k);
				int _x1 = _monster->GetX();
				int _x2 = _monster->GetWidth() + _x1;
				int _y1 = _monster->GetY();
				int _y2 = _monster->GetHeight() + _y1;
				mapObstacle.SetXY(_x1, _x2, _y1, _y2);
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (warrior[i] != NULL)
		{
			int _x1 = warrior[i]->GetX();
			int _x2 = warrior[i]->GetWidth() + _x1;
			int _y1 = warrior[i]->GetY();
			int _y2 = warrior[i]->GetHeight() + _y1;
			mapObstacle.SetXY(_x1, _x2, _y1, _y2);
		}
	}
}

bool GameEvent::GetIsRoomFull()
{
	for (int i = 0; i < roomSize; i++) {
		if (gameRoom[i]->GetLiveMonsterSize() == 0)return false;
	}
	return true;
}

void GameEvent::MonsterFindHouse(Monster **_monster)
{
	if (Moving(_monster, myTaskBoard.GetTaskBoardX() + 60, 0))
	{
		(*_monster)->SetMovingType(Back);
		int randvalue = rand() % 2000;
		if (randvalue < 30 && !GetIsRoomFull()) {
			(*_monster)->SetMonsterState(findHouse);
		}
		else if (randvalue > 1990)
		{
			(*_monster)->SetMonsterState(leave);
		}
		else if (randvalue >= 30 && randvalue <= 100) {                                 //怪物戀愛
			ComingMonsterFallInLoveEvent();
		}
	}
	else {
		(*_monster)->SetMonsterState(lookHouse);
	}
}

void GameEvent::MonsterlivingHouse_event(Room * _room, Monster ** _monster)
{
	_room->SetMonsterlivingRoom(_monster);
	GameOverFlag = true;
}

void GameEvent::MonsterGohome_event(Room * _room, int monsterIndex)
{
	_room->LetMonsterGohome(monsterIndex);
}

void GameEvent::MonsterBeingClick(Monster ** _monster)
{
	Monster_state nowState = (*_monster)->GetMonsterState();

	switch (nowState)
	{
	case game_framework::nothing:

		break;
	case game_framework::findHouse:                   //同意怪物住進防屋
		for (int i = 0; i < roomSize; i++)
		{
			if (!(gameRoom)[i]->GetIsMonsterLiving())    //沒怪物住的話就分配到那間房
			{
				MonsterlivingHouse_event((gameRoom)[i], _monster);
				(gameRoom)[i]->GetLiveMonster(0)->SetMonsterState(nothing);
				MonsterGohome_event(gameRoom[i], 0);
				break;
			}
		}

		break;

	default:
		break;
	}
}

bool GameEvent::MonsterLeave(Monster **_monster)
{
	if (Moving(_monster, -100, 0))
	{
		delete *_monster;
		*_monster = NULL;
		return true;
	}

	return false;
}

bool GameEvent::Moving(Monster ** _monster, int x, int floor)
{
	int Floor_x[3] = { 1150, 750, 1150 };
	int _monsterFloor = (*_monster)->GetFloor();
	int x1 = (*_monster)->GetX();
	int x2 = x1 + (*_monster)->GetWidth();
	bool obsDirection = false, monsterMovingDirection = false; //在左為TRUE 在右為FALSE
	if (mapObstacle.isHit(x1, x2, (*_monster)->GetY(), (*_monster)->GetY() + (*_monster)->GetHeight(), &obsDirection))
	{
		if ((x1 > x && x1 <= x + 20) || (x2 > x && x2 <= x + 20) && _monsterFloor == floor)
		{
			return true;       //抵達目的
		}
		if ((*_monster)->GetMovingType() == Moving_Left) {
			monsterMovingDirection = true;
		}
		else {
			monsterMovingDirection = false;
		}
		if (monsterMovingDirection == obsDirection) {
			(*_monster)->SetMovingLeft(false);
			(*_monster)->SetMovingRight(false);
			return false;
		}
	}

	if (_monsterFloor == floor)
	{
		return MovingLR(_monster, x);
	}
	else if (_monsterFloor < floor)                     //上樓
	{
		if (MovingLR(_monster, Floor_x[_monsterFloor]))
		{
			(*_monster)->SetMovingUp(true);
		}
	}
	else                                                //下樓
	{
		if (MovingLR(_monster, Floor_x[_monsterFloor - 1]))
		{
			(*_monster)->SetMovingDown(true);
		}
	}

	return false;
}

bool GameEvent::MovingLR(Monster ** _monster, int x)
{
	if ((*_monster)->GetX() > x + 40)
	{
		(*_monster)->SetMovingLeft(true);
		(*_monster)->SetMovingRight(false);
	}
	else if ((*_monster)->GetX() <= x - 40)
	{
		(*_monster)->SetMovingRight(true);
		(*_monster)->SetMovingLeft(false);
	}
	else
	{
		(*_monster)->SetMovingLeft(false);
		(*_monster)->SetMovingRight(false);
		return true;
	}

	return false;
}

bool GameEvent::HitWarrior(Monster * _monster, Warrior * _warrior)
{
	return _monster->HitRectangle(_warrior->GetX(), _warrior->GetY(), _warrior->GetX() + _warrior->GetWidth(), _warrior->GetY() - _warrior->GetHeight());
}

void GameEvent::CreateMonster_event(Monster **_monster)
{
	int result = 0;
	result = rand() % 1000;

	if (result < 20)
	{
		(*_monster) = new Monster();
		(*_monster)->LoadBitmap((*_monster)->GetMonsterType());
		(*_monster)->SetMonsterIsExist(true);
		(*_monster)->SetMonsterState(nothing);
		(*_monster)->SetPoint(-100, 530);
	}
}

bool GameEvent::Moving(Warrior ** _warrior, int x, int floor)
{
	int Floor_x[3] = { 1150, 750, 1150 };
	int _warriorFloor = (*_warrior)->GetFloor();
	int x1 = (*_warrior)->GetX();
	int x2 = x1 + (*_warrior)->GetWidth();
	bool obsDirection = false, monsterMovingDirection = false; //在左為TRUE 在右為FALSE
	if (mapObstacle.isHit(x1, x2, (*_warrior)->GetY(), (*_warrior)->GetY() + (*_warrior)->GetHeight()))
	{
		if ((x1 > x && x1 <= x + 20) || (x2 > x && x2 <= x + 20) && _warriorFloor == floor)   //防卡住
		{
			return true;
		}

		if ((*_warrior)->GetMovingType() == Moving_Left) {
			monsterMovingDirection = true;
		}
		else {
			monsterMovingDirection = false;
		}
		if (monsterMovingDirection == obsDirection) {
			(*_warrior)->SetMovingLeft(false);
			(*_warrior)->SetMovingRight(false);
			return false;
		}
	}

	if (_warriorFloor == floor)
	{
		return MovingLR(_warrior, x);
	}
	else if (_warriorFloor < floor)                      //上樓
	{
		if (MovingLR(_warrior, Floor_x[_warriorFloor]))
		{
			(*_warrior)->SetMovingUp(true);
		}
	}
	else                                                //下樓
	{
		if (MovingLR(_warrior, Floor_x[_warriorFloor - 1]))
		{
			(*_warrior)->SetMovingDown(true);
		}
	}

	return false;
}

bool GameEvent::MovingLR(Warrior ** _warrior, int x)
{
	if ((*_warrior)->GetX() > x + 40)
	{
		((*_warrior))->SetMovingLeft(true);
		(*_warrior)->SetMovingRight(false);
	}
	else if ((*_warrior)->GetX() <= x - 40)
	{
		(*_warrior)->SetMovingRight(true);
		(*_warrior)->SetMovingLeft(false);
	}
	else
	{
		(*_warrior)->SetMovingLeft(false);
		(*_warrior)->SetMovingRight(false);
		return true;
	}

	return false;
}

void GameEvent::CreateWarrior_event(Warrior ** _warrior, warrior_type type)
{
	(*_warrior) = new Warrior(type);
	(*_warrior)->SetPoint(-100, 540);
}

void GameEvent::DeleteWarrior_event(Warrior ** _warrior)
{
	if (*_warrior != NULL)
	{
		delete *_warrior;
		*_warrior = NULL;
	}
}

bool GameEvent::HitMonster(Warrior * _warrior, Monster * _monster)
{
	return _warrior->HitRectangle(_monster->GetX(), _monster->GetY(), _monster->GetX() + _monster->GetWidth(), _monster->GetY() - _monster->GetHeight());
}

void GameEvent::WarriorAttack_event(Warrior * _warrior, Monster ** target)
{
	switch (_warrior->GetAttackType())
	{
	case Ad:
		if (Moving(&_warrior, (*target)->GetX(), (*target)->GetFloor()) || HitMonster(_warrior, (*target)))
		{
			if (_warrior->PhysicalAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth()))
			{
				(*target)->BeingAttack(_warrior->GetAttackPower(), _warrior->GetAttackType());  //受到攻擊
				_warrior->SetMovingLeft(false);
				_warrior->SetMovingRight(false);
			}
		}

		break;

	case Ap:
		int targetX = (*target)->GetX();

		if (_warrior->GetX() > targetX)    // 敵人在左
		{
			targetX += 200;

			if (targetX > 1150)targetX = 1100;

			_warrior->SetMovingType(Moving_Left);
		}
		else                              //敵人在右
		{
			targetX -= 200;

			if (targetX < 50)targetX = 50;

			_warrior->SetMovingType(Moving_Right);
		}

		if (Moving(&_warrior, targetX, (*target)->GetFloor()) || (abs((*target)->GetX() - _warrior->GetX()) < 200 && (*target)->GetFloor() == _warrior->GetFloor()))
		{
			_warrior->SetMovingLeft(false);
			_warrior->SetMovingRight(false);

			if (_warrior->MagicAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth(), _warrior->GetWarriorType()))
			{
				(*target)->BeingAttack(_warrior->GetAttackPower(), _warrior->GetAttackType());  //受到攻擊
			}
		}
		break;
	}
}

void GameEvent::MonsterAttack_event(Monster * _monster, Warrior ** target)
{
	switch (_monster->GetAttackType())
	{
	case Ad:
		if (Moving((&_monster), (*target)->GetX(), (*target)->GetFloor()) || HitWarrior(_monster, (*target)))
		{
			if (_monster->PhysicalAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth()))
			{
				(*target)->BeingAttack(_monster->GetAttackPower(), _monster->GetAttackType());  //受到攻擊
				_monster->SetMovingLeft(false);
				_monster->SetMovingRight(false);

				if (!(*target)->GetIsAlive()) DeleteWarrior_event(target); //死亡
			}
		}

		break;

	case Ap:
		int targetX = (*target)->GetX();

		if (_monster->GetX() > targetX)    // 敵人在左
		{
			targetX += 200;

			if (targetX > 1150)targetX = 1100;

			_monster->SetMovingType(Moving_Left);
		}
		else                              //敵人在右
		{
			targetX -= 200;

			if (targetX < 50)targetX = 50;

			_monster->SetMovingType(Moving_Right);
		}

		if (Moving((&_monster), targetX, (*target)->GetFloor()) || (abs((*target)->GetX() - _monster->GetX()) < 200 && (*target)->GetFloor() == _monster->GetFloor()))
		{
			_monster->SetMovingLeft(false);
			_monster->SetMovingRight(false);

			if (_monster->MagicAttack_event((*target)->GetX(), (*target)->GetX() + (*target)->GetWidth(), _monster->GetMonsterType()))
			{
				(*target)->BeingAttack(_monster->GetAttackPower(), _monster->GetAttackType());  //受到攻擊

				if (!(*target)->GetIsAlive()) DeleteWarrior_event(target); //死亡
			}
		}

		break;
	}
}

void GameEvent::MonsterPositionFix()
{
	for (int i = 0; i < roomSize; i++) {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			Monster *_monster = gameRoom[i]->GetLiveMonster(k);
			int x1 = _monster->GetX();
			int x2 = x1 + _monster->GetWidth();
			int y1 = _monster->GetY();
			int y2 = y1 + _monster->GetHeight();
			bool obsDirection = false; //true 為在左
			if (_monster->GetIsOnBattle() && mapObstacle.isOverlapping(x1, x2, y1, y2, &obsDirection))
			{
				if (obsDirection) {
					_monster->SetPoint(x1 + 1, y1);
				}
				else _monster->SetPoint(x1 - 2, y1);
				//return;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		if (warrior[i] != NULL) {
			Warrior *_warrior = warrior[i];
			int x1 = _warrior->GetX();
			int x2 = x1 + _warrior->GetWidth();
			int y1 = _warrior->GetY();
			int y2 = y1 + _warrior->GetHeight();
			bool obsDirection = false; //true 為在左
			if (_warrior->GetIsOnBattle() && mapObstacle.isOverlapping(x1, x2, y1, y2, &obsDirection))
			{
				if (obsDirection) {
					_warrior->SetPoint(x1 + 2, y1);
				}
				else _warrior->SetPoint(x1 - 1, y1);
				return;
			}
		}
	}
}

Monster * GameEvent::findMonsterTarget(Warrior * _warrior)
{
	Monster* result = NULL;
	int minX = 9999;

	for (int i = 0; i < roomSize; i++)
	{
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())  //判斷怪物是否正在戰鬥
			{
				int dx = abs(_warrior->GetX() - (gameRoom[i]->GetLiveMonster(k))->GetX());          //距離差

				if (gameRoom[i]->GetLiveMonster(k)->GetFloor() != _warrior->GetFloor())
				{
					int dFloor = abs(gameRoom[i]->GetLiveMonster(k)->GetFloor() - _warrior->GetFloor());   //樓層差
					dx += dFloor * 400;
				}

				if (dx < minX)
				{
					minX = dx;
					result = (gameRoom[i]->GetLiveMonster(k));
				}
			}
		}
	}

	return result;
}

Warrior * GameEvent::findWarriorTarget(Monster * _monster)
{
	Warrior* result = NULL;
	int minX = 9999;

	for (int i = 0; i < 10; i++)
	{
		if (warrior[i] != NULL)
		{
			int dx = abs(_monster->GetX() - warrior[i]->GetX());

			if (_monster->GetFloor() != warrior[i]->GetFloor())
			{
				int dFloor = abs(_monster->GetFloor() - warrior[i]->GetFloor());   //樓層差
				dx += dFloor * 400;
			}

			if (dx < minX)
			{
				minX = dx;
				result = warrior[i];
			}
		}
	}

	return result;
}

void GameEvent::BattleEnd()
{
	for (int i = 0; i < roomSize; i++)
	{
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())
			{
				gameRoom[i]->LetMonsterGohome(k);
				gameRoom[i]->GetLiveMonster(k)->SetIsOnBattle(false);
			}
		}
	}
	if (riseMoney != addMoney) {
		int add = addMoney / 100;
		myMoney.SetValue(myMoney.GetValue() + add);
		riseMoney+= add;
	}
}

void GameEvent::BattleFinish()
{
	switch (myTaskBoard.GetNowTask())
	{
	case FirstTask:
		riseMoney = 0;
		addMoney = 10000;
		myTaskBoard.SetNowTask(TaskList::nothing);
		break;
	default:
		break;
	}
}

void GameEvent::SeleteTaskBattle()
{	
	if (!isOnBattle) {
		switch (myTaskBoard.GetNowTask())
		{
		case TaskList::nothing:
			if (battleCount > 4000 - (TimeLevel * 500)) {
				isIntoBattle = true;
				CreateWarrior_event(&warrior[0], villager);
				for (int i = 0; warrior[i] != NULL; i++) {
					warrior[i]->SetPoint(-100 - (60 * i), 540);
				}
				battleCount = 0;
			}
			break;
		case TaskList::FirstTask:
			if (battleCount > 3000 - (TimeLevel * 500)) {
				isIntoBattle = true;
				CreateWarrior_event(&warrior[0], villager);
				CreateWarrior_event(&warrior[1], firemagic);
				for (int i = 0; warrior[i] != NULL; i++) {
					warrior[i]->SetPoint(-100 - (60 * i), 540);
				}
				battleCount = 0;
			}
			break;
		default:
			break;
		}
		battleCount++;
	}
}

void GameEvent::BattleTest1()
{
	isIntoBattle = true;
	CreateWarrior_event(&warrior[0], villager);
	CreateWarrior_event(&warrior[1], firemagic);
	for (int i = 0; warrior[i] != NULL; i++) {
		warrior[i]->SetPoint(-100 - (60 * i), 540);
	}
}

void GameEvent::timeControl()
{
	if (isSpeedControlOn[0]) TimeLevel = 1;
	if (isSpeedControlOn[1]) TimeLevel = 2;
	if (isSpeedControlOn[2]) TimeLevel = 3;
}

void GameEvent::ComingMonsterFallInLoveEvent()
{
	for (int i = 0; i < roomSize; i++) {
		for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++) {
			if (gameRoom[i]->GetLiveMonsterSize() == 1 && (comingMonster)->GetMonsterType() == gameRoom[i]->GetLiveMonster(k)->GetMonsterType() && (gameRoom[i]->GetLiveMonster(k)->GetMonsterGender() != (comingMonster)->GetMonsterGender())) {
				MonsterlivingHouse_event(gameRoom[i], &comingMonster);
				gameRoom[i]->GetLiveMonster(gameRoom[i]->GetLiveMonsterSize() - 1)->SetMonsterState(fallInLove);
				MonsterGohome_event(gameRoom[i], 1);
				return;
			}
		}
	}
}

void GameEvent::MonsterMatingEvent()
{
	for (int i = 0; i<roomSize; i++)
	{
		int randValue = rand() % 1000;
		if (randValue<2 && gameRoom[i]->GetLiveMonsterSize() == 2 && gameRoom[i]->GetIsMonsterIn(0) && gameRoom[i]->GetIsMonsterIn(1) ) {
			gameRoom[i]->GetLiveMonster(0)->SetMonsterState(fallInLove);
			gameRoom[i]->GetLiveMonster(0)->SetTimecount(0);
			int childRandvalue = rand() % 1000;
			if (childRandvalue < 500)MonsterBorn(i);  //怪物出生
		}
	}
}

void GameEvent::MonsterBorn(int roomNum)
{
	Monster *newMonster;
	newMonster = new Monster((gameRoom[roomNum])->GetLiveMonster(0)->GetMonsterType());
	newMonster->SetIsChild(true);
	newMonster->LoadBitmap(newMonster->GetMonsterType());
	newMonster->SetMonsterIsExist(false);
	newMonster->SetMonsterState(nothing);

	(gameRoom[roomNum])->SetMonsterlivingRoom(&newMonster);
	(gameRoom[roomNum])->GetLiveMonster(2)->SetPoint((gameRoom[roomNum])->GetX(), (gameRoom[roomNum])->GetLiveMonster(0)->GetY() + 20); //高度修正
	(gameRoom[roomNum])->GetLiveMonster(2)->SetIsGoOutside(false);
	(gameRoom[roomNum])->GetLiveMonster(2)->SetMovingType(Hide);
	(gameRoom[roomNum])->GetLiveMonster(2)->InheritAbility(gameRoom[roomNum]->GetLiveMonster(0), gameRoom[roomNum]->GetLiveMonster(1));
	(gameRoom[roomNum])->SetIsMonsterIn(true, 2);
}

}