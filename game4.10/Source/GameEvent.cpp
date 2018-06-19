#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
#include <fstream>
#include <sstream>

namespace game_framework
{
GameEvent::GameEvent()
{
    comingMonster = NULL;
    Clock = NULL;

    for (int i = 0; i < 4; i++)gameRoom[i] = new Room(room_x + i * 115, room_y, 101 + i);
}

GameEvent::~GameEvent()
{
}

void GameEvent::OnBeginState()
{
    myRoomInterface = new RoomInterface(gameRoom);
	isRoomDataBoardShow = false;
    Warning.SetTopLeft(-1280, 100);
	fall.Reset();
	fall.SetTopLeft(0,0);
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
    isMonsterDataBoardShow = false;
    isEffectMusicOn = false;
	isFall = false;
    myMoney.SetValue(1000);
    ///////////////////////////時間設定/////////////////////
    TimeLevel = 1;
    isSpeedControlOn[0] = true;

    for (int i = 1; i < 3; i++)isSpeedControlOn[i] = false;

    ////////////////////////////////////////////////////////
    for (int i = 0; i < 10; i++)warrior[i] = NULL;

	DevilRoom_x = 660;
	DevilRoom_floor = 1;
}

void GameEvent::OnInit()
{
    CollectRentTime = 0;
    Background.LoadBitmap("Bitmaps\\gameBackground1.bmp");
    Warning.LoadBitmap("Bitmaps\\Warning.bmp", RGB(255, 255, 255));
    myTaskBoard.LoadBitmap();
    myMenu.LoadBitmap();
    SpeedControlBtn[0].AddBitmap("Bitmaps\\gameRun\\SpeedButton1_2.bmp", RGB(255, 255, 255));
    SpeedControlBtn[0].AddBitmap("Bitmaps\\gameRun\\SpeedButton1_1.bmp", RGB(255, 255, 255));
    SpeedControlBtn[1].AddBitmap("Bitmaps\\gameRun\\SpeedButton2_2.bmp", RGB(255, 255, 255));
    SpeedControlBtn[1].AddBitmap("Bitmaps\\gameRun\\SpeedButton2_1.bmp", RGB(255, 255, 255));
    SpeedControlBtn[2].AddBitmap("Bitmaps\\gameRun\\SpeedButton3_2.bmp", RGB(255, 255, 255));
    SpeedControlBtn[2].AddBitmap("Bitmaps\\gameRun\\SpeedButton3_1.bmp", RGB(255, 255, 255));
    SpeedControlBtn[0].SetTopLeft(1035, 675);
    SpeedControlBtn[1].SetTopLeft(1122, 675);
    SpeedControlBtn[2].SetTopLeft(1209, 675);

	for (int i = 0; i < 15; i++) {
		string temp = "Bitmaps\\GameFall\\quest_lose_";
		stringstream ss;
		ss << i;
		temp += ss.str();
		temp += ".bmp";
		char root[100];
		strcpy(root, temp.c_str());
		fall.AddBitmap(root, RGB(255, 255, 255));
	}
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
    const char KEY_ESC = 27;

    if (nChar == KEY_LEFT)
    {
       
    }
    else if (nChar == KEY_RIGHT)
    {
        
    }
    else if (nChar == KEY_UP)
    {
      
    }
    else if (nChar == KEY_DOWN)  //測試
    {
        riseMoney = 0;
        addMoney = -100;
    }
    else if (nChar == KEY_ESC)
    {
        if (myMenu.GetIsOnShow())
        {
            if (myMenu.SetIsOnShow(false))isGamePause = false; //取消
        }
        else
        {
			myMenu.SetIsOnShow(true);
            isGamePause = true;
        }
    }
}

void GameEvent::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (comingMonster != NULL && comingMonster->IsMouseOn(point)) //若點選到拜訪的怪物
    {
        MonsterBeingClick(&comingMonster);
    }

    for (int i = 0; i < 3; i++)                                   //時間控制按鈕
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

    if (myRoomInterface->GetIsShow())                          //房務介面動作
    {
        myRoomInterface->IsMouseClick(point);

        for (int i = 0; i < 3; i++)
        {
			myRoomInterface->IsMouseClick(point, i);
        }

		if (myRoomInterface->GetIsConfirmOnShow())
		{
			int leaveMonsterIndex = myRoomInterface->IsConfirmOnClick();
			if (leaveMonsterIndex != -1)
			{
				gameRoom[myRoomInterface->GetRoomSelector()]->SetDoorOpen();
				gameRoom[myRoomInterface->GetRoomSelector()]->GetLiveMonster(leaveMonsterIndex)->SetIsGoOutside(true);
				gameRoom[myRoomInterface->GetRoomSelector()]->GetLiveMonster(leaveMonsterIndex)->SetMonsterState(leave);
				myRoomInterface->SetInterfaceShow(false);
				isGamePause = false;
			}
		}
    }

    if (myMenu.GetIsOnShow())
    {
        myMenu.IsMouseClick();

        if (myMenu.GetIsSaveDataOnShow())
        {
            int SaveIndex = myMenu.SaveDataOnClick();

            if (SaveIndex != 0 && myMenu.GetState()==Save)
            {
                string save_str = "save";
                save_str += ('0' + SaveIndex);
                SaveGame(save_str);
                isGamePause = false;
			}
			else if (SaveIndex != 0 && myMenu.GetState() == Load)
			{
				string save_str = "save";
				save_str += ('0' + SaveIndex);
				LoadGame(save_str);
				isGamePause = false;
			}
        }
    }

    if (myTaskBoard.IsTaskOnClick(point))isGamePause = true;   //任務版介面動作
}

void GameEvent::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!isGamePause)
    {
        for (int i = 0; i < 4; i++)                              //處理介面顯示
        {
            for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
            {
                if (gameRoom[i]->GetLiveMonster(k)->IsMouseOn(point) && gameRoom[i]->GetLiveMonster(k)->GetIsOnShow())
                {
                    isMonsterDataBoardShow = true;
                    i = 5;
                    break;
                }

                isMonsterDataBoardShow = false;
            }
        }
		
		for (int i = 0; i < 4; i++)                              //處理介面顯示
		{
			if (!isMonsterDataBoardShow)
			{
				if (gameRoom[i]->IsMouseOn(point))
				{
					gameRoom[i]->SetRoomBoard();
					isRoomDataBoardShow = true;
					break;
				}
			}
		}

        if (comingMonster != NULL)                              //處理介面顯示
        {
            comingMonster->IsMouseOn(point);
        }

        for (int i = 0; i < 10; i++)                            //處理介面顯示
        {
            if (warrior[i] != NULL)
            {
                warrior[i]->IsMouseOn(point);
            }
        }
    }

    if (myRoomInterface->GetIsShow())
    {
        myRoomInterface->IsMouseOn(point);
    }
    else if (myMenu.GetIsOnShow())
    {
        if (myMenu.IsMouseOn(point))
        {
            if (!isEffectMusicOn)CAudio::Instance()->Play(AUDIO_DING);

            isEffectMusicOn = true;
        }
        else
        {
            isEffectMusicOn = false;
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
            for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
            {
                Monster* _monster = gameRoom[i]->GetLiveMonster(k);

                if (_monster->GetIsOnBattle() && _monster->IsMouseOn(point))  //怪物被點擊的事件，怪物回家
                {
                    MonsterGohome_event(gameRoom[i], k);
                    _monster->SetIsOnBattle(false);
                    return;
                }
            }

            for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
            {
                if (gameRoom[i]->IsMouseOn(point) && gameRoom[i]->GetIsMonsterIn(k))//房屋被點擊的事件，怪物戰鬥
                {
                    gameRoom[i]->SetMonsterFight(true);
                    isMonsterGoingOut = true;
                }
            }
        }
    }
    else
    {
		if (!myRoomInterface->GetIsShow()) {
			for (int i = 0; i < roomSize; i++)
			{
				if (gameRoom[i]->IsMouseOn(point))             //房屋介面滑鼠事件
				{
					myRoomInterface->SetRoomSelector(i);
					myRoomInterface->SetInterfaceShow(true);
					isGamePause = true;
				}
			}
		}
		else
		{
			myRoomInterface->SetInterfaceShow(false);
			isGamePause = false;
		}
    }

	 if (myMenu.GetIsOnShow())                           // 主選單界面取消
	{
		if (myMenu.SetIsOnShow(false)) isGamePause = false;
	}

    if (myTaskBoard.GetIsOnShow() && myTaskBoard.OnRButtonDown(nFlags, point))isGamePause = false;
}

void GameEvent::OnMove()
{
    if (!isGamePause)
    {
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

        timeControl();                                  //設定時間變數

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

		if (isFall)                    //失敗動畫
		{
			if (fall.IsFinalBitmap())GameOverFlag = true;
			fall.OnMove();
		}
    }
    myMoney.OnMove();
    myRoomInterface->OnMove();
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

	if (isFall)                    //失敗動畫
	{
		fall.OnShow();
	}

    myMoney.OnShow();
    Warning.ShowBitmap();
    myTaskBoard.OnShow();
    myRoomInterface->OnShow();
    myMenu.OnShow();
}

void GameEvent::OnEvent()
{
    MonsterStateEvent();
    SeleteTaskBattle();
    CollectRentEvent();                      //收取房租事件
    GetMoneyEvent();

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
                if (gameRoom[i]->GetLiveMonsterSize() > 0 && !gameRoom[i]->GetIsMonsterIn(k) && gameRoom[i]->GetLiveMonster(k)!=NULL)
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
        for (int i = 0; i < 10; i++)
        {
            if (warrior[i] != NULL)
            {
                Monster* target = findMonsterTarget(warrior[i]);

                if (target != NULL)
                {
                    WarriorAttack_event(warrior[i], &target);
                }
                else                                    //落沒有怪物擇去魔王帳篷
                {
					if (Moving((&warrior[i]), DevilRoom_x, DevilRoom_floor)&& !isFall)
					{
						CAudio::Instance()->Pause();
						CAudio::Instance()->Play(AUDIO_Fail);
						warrior[i]->SetIntoHouse(true);
						isFall = true;
					}
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
            for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
            {
                if (gameRoom[i]->GetLiveMonster(k) != NULL && gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())
                {
                    Monster* _monster = gameRoom[i]->GetLiveMonster(k);
                    Warrior* target = findWarriorTarget(_monster);
                    Warrior* temp = target;

                    if (target != NULL)
                    {
                        MonsterAttack_event(_monster, &target);

                        if (target == NULL)                     //刪除勇士記憶體
                        {
                            for (int n = 0; n < 10; n++)
                            {
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

    //////////////////////////////////////////////////////////////////////////////////////來臨怪物事件->

    if (!isOnBattle)	MonsterMatingEvent();                       //怪物交配事件

}


bool GameEvent::GameOver()
{
    return GameOverFlag;
}

bool GameEvent::SaveGame(string saveName)
{
    fstream saveFile;
    std::stringstream ss;
    string saveRoot = "Save\\" + saveName + ".txt";
    saveFile.open(saveRoot, ios::out);
    time(&nowtime);
    ss << saveName << " " << ctime(&nowtime) << "\n";
    ss << "Money\n" << myMoney.GetValue() << "\n";               //金錢
    ss << "RoomSize\n" << roomSize << "\n";                      //房間SIZE

    for (int i = 0; i < roomSize; i++)
    {
        ss << "gameRoomMonster" << i << "\n" ;
		ss << "Rent" << gameRoom[i]->GetRent() << "\n";
        ss << "MonsterSize" << gameRoom[i]->GetLiveMonsterSize() << "\n";

        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            ss << "Monster" << k << "\n" ;
            ss << "MonsterType" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetMonsterType() << "\n";
            ss << "MonsterName" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetMonsterName() << "\n";
            ss << "MonsterGender" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetMonsterGender() << "\n";
            ss << "MonsterState" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetMonsterState() << "\n";
            ss << "X" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetX() << "\n";
            ss << "Y" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetY() << "\n";
            ss << "AttackType" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetAttackType() << "\n";
            ss << "MaxHp" <<  "\n" << gameRoom[i]->GetLiveMonster(k)->GetHp() << "\n";
            ss << "AttackPower" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetAttackPower() << "\n";
            ss << "AdDenfense" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetAdDefense() << "\n";
            ss << "ApDenfense" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetApDefense() << "\n";
            ss << "IsOnShow" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetIsOnShow() << "\n";
            ss << "IsKid" << "\n" << gameRoom[i]->GetLiveMonster(k)->GetIsKid() << "\n";
        }
    }

    saveFile << ss.str();
    saveFile.close();
    return false;
}

bool GameEvent::LoadGame(string saveName)
{
    fstream saveFile;
    char buf[10240];
    char* str;        //字串位置
	OnBeginState();
    string saveRoot = "Save\\" + saveName + ".txt";
    saveFile.open(saveRoot, ios::in);
    saveFile.read(buf, sizeof(buf));

    for (int i = 0; i < roomSize; i++)
    {
        delete gameRoom[i];
    }

    str = strstr(buf, "Money");                           //金錢讀取
    str += 6;
    myMoney.SetValue(atoi(str));
    str = strstr(buf, "RoomSize");						  //房間大小讀取
    str += 9;
    roomSize = (atoi(str));

    for (int i = 0; i < roomSize; i++)
    {
        gameRoom[i] = new Room(room_x + i * 115, room_y, 101 + i);
        gameRoom[i]->LoadBitmap();
    }

    for (int i = 0; i < roomSize; i++)                    //居民讀取
    {
        str = strstr(str, "gameRoomMonster");
        str += 17;

		str = strstr(str, "Rent");               //房租讀取
		str += 4;
		gameRoom[i]->SetRent((atoi(str)));

        str = strstr(str, "MonsterSize" );
        str += 11;
        int monsterSize = (atoi(str));

        for (int k = 0; k < monsterSize; k++)
        {
            Monster* _monster = new Monster;
            _monster->MonsterLoad(str, k);
            gameRoom[i]->SetMonsterlivingRoom(&_monster);
            gameRoom[i]->SetIsMonsterIn(true, k);
            delete _monster;
        }
    }

    delete comingMonster;
    comingMonster = NULL;
    saveFile.close();
    return false;
}

void GameEvent::SetObstacle()
{
    for (int i = 0; i < roomSize; i++)
    {
        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            if (gameRoom[i]->GetIsMonsterFight(k) && gameRoom[i]->GetLiveMonster(k)->GetIsOnShow())
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
        if (warrior[i] != NULL && warrior[i]->GetIsOnShow())
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
    for (int i = 0; i < roomSize; i++)
    {
        if (gameRoom[i]->GetLiveMonsterSize() == 0)return false;
    }

    return true;
}

void GameEvent::GetMoneyEvent()
{
    if (riseMoney != addMoney)
    {
        int add = addMoney / 100;

        if (add == 0)add = 1;

        myMoney.SetValue(myMoney.GetValue() + add);
        riseMoney += add;

        if (abs(riseMoney) > abs(addMoney))                                                                                                  //金錢修正
        {
            riseMoney -= abs(riseMoney) - abs(addMoney);
            myMoney.SetValue(myMoney.GetValue() + abs(riseMoney) - abs(addMoney));
        }
        else if (riseMoney == addMoney)
        {
            riseMoney = 0;
            addMoney = 0;
        }
    }
}

void GameEvent::CollectRentEvent()
{
    if (CollectRentTime > 3500)
    {
        for (int i = 0; i < roomSize; i++)
        {
            if (gameRoom[i]->GetLiveMonsterSize() > 0)addMoney += gameRoom[i]->GetRent();
        }

        riseMoney = 0;
        CollectRentTime = 0;
    }
    else CollectRentTime += TimeLevel;
}

void GameEvent::MonsterStateEvent()
{
    for (int i = 0; i < roomSize; i++)                                      //居民狀態處理
    {
        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            Monster* _monster = gameRoom[i]->GetLiveMonster(k);
            Monster_state monster_state = _monster->GetMonsterState();

            switch (monster_state)
            {
                case game_framework::leave:
                    if (MonsterLeave(&_monster))
                    {
                        gameRoom[i]->MonsterLeave(k);
                    }

                    break;

                case game_framework::working:
                    break;

                case game_framework::nothing:
                    if (!isOnBattle && _monster->GetIsOnBattle())
                    {
                        gameRoom[i]->LetMonsterGohome(k);
                        gameRoom[i]->GetLiveMonster(k)->SetIsOnBattle(false);
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

void GameEvent::MonsterFindHouse(Monster** _monster)
{
    if (Moving(_monster, myTaskBoard.GetTaskBoardX() + 60, 0))
    {
        (*_monster)->SetMovingType(Back);
        int randvalue = rand() % 2000;

        if (randvalue < 30 && !GetIsRoomFull())
        {
            (*_monster)->SetMonsterState(findHouse);
        }
        else if (randvalue > 1990)
        {
            (*_monster)->SetMonsterState(leave);
        }
        else if (randvalue >= 30 && randvalue <= 100)                                   //怪物戀愛
        {
            ComingMonsterFallInLoveEvent();
        }
    }
    else
    {
        (*_monster)->SetMonsterState(lookHouse);
    }
}

void GameEvent::MonsterlivingHouse_event(Room* _room, Monster** _monster)
{
    _room->SetMonsterlivingRoom(_monster);
}

void GameEvent::MonsterGohome_event(Room* _room, int monsterIndex)
{
    _room->LetMonsterGohome(monsterIndex);
}

void GameEvent::MonsterBeingClick(Monster** _monster)
{
    Monster_state nowState = (*_monster)->GetMonsterState();

    switch (nowState)
    {
        case game_framework::nothing:
            break;

        case game_framework::findHouse:                   //同意怪物住進防屋
            for (int i = 0; i < roomSize; i++)
            {
                if (!((gameRoom)[i]->GetLiveMonsterSize() > 0))  //沒怪物住的話就分配到那間房
                {
                    MonsterlivingHouse_event((gameRoom)[i], _monster);
                    (gameRoom)[i]->GetLiveMonster(0)->SetMonsterState(finishhouse);
                    MonsterGohome_event(gameRoom[i], 0);
                    break;
                }
            }

            break;

        default:
            break;
    }
}

bool GameEvent::MonsterLeave(Monster** _monster)
{
    if (Moving(_monster, -100, 0))
    {
        delete *_monster;
        *_monster = NULL;
        return true;
    }

    return false;
}

bool GameEvent::Moving(Monster** _monster, int x, int floor)
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

        if ((*_monster)->GetMovingType() == Moving_Left)
        {
            monsterMovingDirection = true;
        }
		else if ((*_monster)->GetMovingType() == Moving_Right)
		{
			monsterMovingDirection = false;
		}
		else
		{
			if (x < x1)
			{
				monsterMovingDirection = true;
			}
			else
			{
				monsterMovingDirection = false;
			}

		}

        if (monsterMovingDirection == obsDirection)
        {
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

bool GameEvent::MovingLR(Monster** _monster, int x)
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

bool GameEvent::HitWarrior(Monster* _monster, Warrior* _warrior)
{
    return _monster->HitRectangle(_warrior->GetX(), _warrior->GetY(), _warrior->GetX() + _warrior->GetWidth(), _warrior->GetY() - _warrior->GetHeight());
}

void GameEvent::CreateMonster_event(Monster** _monster)
{
    int result = 0;
    result = rand() % 1000;

    if (result < 20)
    {
        (*_monster) = new Monster();
        (*_monster)->LoadBitmap((*_monster)->GetMonsterType());
        (*_monster)->SetIsOnShow(true);
        (*_monster)->SetMonsterState(nothing);
        (*_monster)->SetPoint(-100, 530);
    }
}

bool GameEvent::Moving(Warrior** _warrior, int x, int floor)
{
    int Floor_x[3] = { 1150, 750, 1150 };
    int _warriorFloor = (*_warrior)->GetFloor();
    int x1 = (*_warrior)->GetX();
    int x2 = x1 + (*_warrior)->GetWidth();
    bool obsDirection = false, monsterMovingDirection = false; //在左為TRUE 在右為FALSE

    if (mapObstacle.isHit(x1, x2, (*_warrior)->GetY(), (*_warrior)->GetY() + (*_warrior)->GetHeight(), &obsDirection))
    {
        if ((x1 > x && x1 <= x + 20) || (x2 > x && x2 <= x + 20) && _warriorFloor == floor)   //防卡住
        {
            return true;
        }

        if ((*_warrior)->GetMovingType() == Moving_Left)
        {
            monsterMovingDirection = true;
        }
        else if((*_warrior)->GetMovingType() == Moving_Right)
        {
            monsterMovingDirection = false;
		}
		else
		{
			if (x < x1)
			{
				monsterMovingDirection = true;
			}
			else
			{
				monsterMovingDirection = false;
			}

		}

        if (monsterMovingDirection == obsDirection)
        {
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

bool GameEvent::MovingLR(Warrior** _warrior, int x)
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

void GameEvent::CreateWarrior_event(Warrior** _warrior, warrior_type type)
{
    (*_warrior) = new Warrior(type);
    (*_warrior)->SetPoint(-100, 540);
}

void GameEvent::DeleteWarrior_event(Warrior** _warrior)
{
    if (*_warrior != NULL)
    {
        delete *_warrior;
        *_warrior = NULL;
    }
}

bool GameEvent::HitMonster(Warrior* _warrior, Monster* _monster)
{
    return _warrior->HitRectangle(_monster->GetX(), _monster->GetY(), _monster->GetX() + _monster->GetWidth(), _monster->GetY() - _monster->GetHeight());
}

void GameEvent::WarriorAttack_event(Warrior* _warrior, Monster** target)
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

void GameEvent::MonsterAttack_event(Monster* _monster, Warrior** target)
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
    for (int i = 0; i < roomSize; i++)
    {
        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            Monster* _monster = gameRoom[i]->GetLiveMonster(k);
            int x1 = _monster->GetX();
            int x2 = x1 + _monster->GetWidth();
            int y1 = _monster->GetY();
            int y2 = y1 + _monster->GetHeight();
            bool obsDirection = false; //true 為在左

            if (_monster->GetIsOnBattle() && mapObstacle.isOverlapping(x1, x2, y1, y2, &obsDirection))
            {
                if (obsDirection)
                {
                    _monster->SetPoint(x1 + 1, y1);
                }
                else _monster->SetPoint(x1 - 1, y1);

                //return;
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (warrior[i] != NULL)
        {
            Warrior* _warrior = warrior[i];
            int x1 = _warrior->GetX();
            int x2 = x1 + _warrior->GetWidth();
            int y1 = _warrior->GetY();
            int y2 = y1 + _warrior->GetHeight();
            bool obsDirection = false; //true 為在左

            if ( mapObstacle.isOverlapping(x1, x2, y1, y2, &obsDirection))
            {
                if (obsDirection)
                {
                    _warrior->SetPoint(x1 + 1, y1);
                }
                else _warrior->SetPoint(x1 - 1, y1);

                return;
            }
        }
    }
}

Monster* GameEvent::findMonsterTarget(Warrior* _warrior)
{
    Monster* result = NULL;
    int minX = 9999;
	int dx = 0;

    for (int i = 0; i < roomSize; i++)
    {
        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            if (gameRoom[i]->GetLiveMonster(k)->GetIsOnBattle())  //判斷怪物是否正在戰鬥
            {
                dx = abs(_warrior->GetX() - (gameRoom[i]->GetLiveMonster(k))->GetX());          //距離差

                if (gameRoom[i]->GetLiveMonster(k)->GetFloor() != _warrior->GetFloor())
                {
                    int dFloor = abs(gameRoom[i]->GetLiveMonster(k)->GetFloor() - _warrior->GetFloor());   //樓層差
                    dx += dFloor * 1000;
                }

                if (dx < minX)
                {
                    minX = dx;
                    result = (gameRoom[i]->GetLiveMonster(k));
                }
            }
        }
    }

	dx = abs(_warrior->GetX() - DevilRoom_x);                  //魔王房屋距離判斷
	if (DevilRoom_floor != _warrior->GetFloor())
	{
		int dFloor = abs(DevilRoom_floor - _warrior->GetFloor());   //樓層差
		dx += dFloor * 1000;
	}

	if (dx < minX)
	{
		return NULL;
	}

    return result;
}

Warrior* GameEvent::findWarriorTarget(Monster* _monster)
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
                dx += dFloor * 1000;
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


void GameEvent::BattleFinish()
{
    switch (myTaskBoard.GetNowTask())
    {
        case FirstTask:
            riseMoney = 0;
            addMoney = 100;
            myTaskBoard.SetNowTask(TaskList::nothing);
			myTaskBoard.SetTaskShow(FirstTask, false);
			myTaskBoard.SetTaskShow(eggComing, true);
            myTaskBoard.SetTaskShow(Boss, true);
            break;

		case eggComing:
			riseMoney = 0;
			addMoney = 500;
			myTaskBoard.SetNowTask(TaskList::nothing);
			break;

        case Boss:
            riseMoney = 0;
            addMoney = 1500;
            myTaskBoard.SetNowTask(TaskList::nothing);
            myTaskBoard.SetTaskShow(Boss, false);
			GameOverFlag = true;
            break;

        default:
            break;
    }
}

void GameEvent::SeleteTaskBattle()
{
    if (!isOnBattle)
    {
        switch (myTaskBoard.GetNowTask())
        {
            case TaskList::nothing:
                if (battleCount > 5000)
                {
                    isIntoBattle = true;
                    CreateWarrior_event(&warrior[0], villager);

                    for (int i = 0; warrior[i] != NULL; i++)
                    {
                        warrior[i]->SetPoint(-100 - (60 * i), 540);
                    }

                    battleCount = 0;
                }

                break;

            case TaskList::FirstTask:
                if (battleCount > 3000)
                {
                    isIntoBattle = true;
                    CreateWarrior_event(&warrior[0], villager);
                    CreateWarrior_event(&warrior[1], firemagic);

                    warrior[0]->SetPoint(-100, 540);
					warrior[1]->SetPoint(-160, 540);

                    battleCount = 0;
                }

                break;
			case TaskList::eggComing:
				if (battleCount > 3000)
				{
					isIntoBattle = true;
					CreateWarrior_event(&warrior[0], egg);
					CreateWarrior_event(&warrior[1], egg);

					warrior[0]->SetPoint(-100, 530);
					warrior[1]->SetPoint(-160, 530);

					battleCount = 0;
				}
				break;
            case TaskList::Boss:
                if (battleCount > 3000 )
                {
                    isIntoBattle = true;
                    CreateWarrior_event(&warrior[0], boss);

                    for (int i = 0; warrior[i] != NULL; i++)
                    {
                        warrior[i]->SetPoint(-200 - (60 * i), 490);
                    }

                    battleCount = 0;
                }

            default:
                break;
        }

        battleCount += TimeLevel;
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
    for (int i = 0; i < roomSize; i++)
    {
        for (int k = 0; k < gameRoom[i]->GetLiveMonsterSize(); k++)
        {
            if (gameRoom[i]->GetLiveMonsterSize() == 1 && (comingMonster)->GetMonsterType() == gameRoom[i]->GetLiveMonster(k)->GetMonsterType() && (gameRoom[i]->GetLiveMonster(k)->GetMonsterGender() != (comingMonster)->GetMonsterGender()))
            {
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
    for (int i = 0; i < roomSize; i++)
    {
        int randValue = rand() % 1000;
		

        if (randValue < 2 && gameRoom[i]->GetLiveMonsterSize() == 2 && gameRoom[i]->GetIsMonsterIn(0) && gameRoom[i]->GetIsMonsterIn(1) )
        {
			Monster *_monster1 = gameRoom[i]->GetLiveMonster(0);
			Monster *_monster2 = gameRoom[i]->GetLiveMonster(1);
			if ((_monster1->GetMonsterGender() != _monster2->GetMonsterGender()) && !_monster1->GetIsKid() && !_monster2->GetIsKid())
			{
				_monster1->SetMonsterState(fallInLove);
				_monster1->SetHeadImgcount(0);
				int childRandvalue = rand() % 1000;

				if (childRandvalue < 200)MonsterBorn(i);  //怪物出生
			}
        }
    }
}

void GameEvent::MonsterBorn(int roomNum)
{
    Monster* newMonster;
    newMonster = new Monster((gameRoom[roomNum])->GetLiveMonster(0)->GetMonsterType());
    newMonster->SetIsChild(true);
    newMonster->LoadBitmap(newMonster->GetMonsterType());
    newMonster->SetIsOnShow(false);                             //設定在家
    newMonster->SetMonsterState(nothing);
    (gameRoom[roomNum])->SetMonsterlivingRoom(&newMonster);
    (gameRoom[roomNum])->GetLiveMonster(2)->SetPoint((gameRoom[roomNum])->GetX(), (gameRoom[roomNum])->GetLiveMonster(0)->GetY() + 20); //高度修正
    (gameRoom[roomNum])->GetLiveMonster(2)->SetIsGoOutside(false);
    (gameRoom[roomNum])->GetLiveMonster(2)->SetIsOnShow(false);
    (gameRoom[roomNum])->GetLiveMonster(2)->InheritAbility(gameRoom[roomNum]->GetLiveMonster(0), gameRoom[roomNum]->GetLiveMonster(1));
    (gameRoom[roomNum])->SetIsMonsterIn(true, 2);
}

}