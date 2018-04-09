#pragma once
#include "Monster.h"
namespace game_framework
{
	enum AUDIO_ID {				// 定義各種音效的編號
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
		void OnShow(bool flag);//true 為讓門顯示 false試讓怪物顯示
        void OnMove();
        Monster* GetLiveMonster();
		bool GetIsMonsterLiving();
		bool GetIsMonsterIn();
		bool GetIsMonsterFight();
		void LetMonsterGohome();
		bool IsMouseOn(CPoint point); //檢查滑鼠是否在上面
		void SetMonsterFight(bool flag);
        void SetMonsterlivingRoom(Monster **_monster); //讓怪物住進房子，回傳NULL指標將原本的怪物抹去
    private:
        int _x, _y; //座標
		int counter;
        Monster liveMonster;	//居住怪物
        CAnimation animation;  //動畫
		void SetMonsterIntohome(); //怪物進門的動作
		bool MonsterGoHome(); //若還沒到達家裡得坐標，回傳 true ，到達了回傳false
		bool isMonsterLiving; //是否居住怪物
        bool isMonsterIn;		//居住的怪物是否在裡面
        bool isDoorOpen;		//門有沒有開
		bool isMonsterGoHome;	//怪物是否正在移動進屋
		bool isMonsterFight;    //怪物是否戰鬥
};
}


