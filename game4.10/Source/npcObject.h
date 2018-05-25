#pragma once
#include <string.h>
#include "MagicAttack.h"
#include "MonsterDataBoard.h"
using namespace std;
namespace game_framework
{
enum Attack_Type{ Ad,	 Ap};
enum MovingAnimation_Type   //移動狀態
{
    Forward,       //向前
    Back,			//向後
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
        void OnMove();			// 移動
        void OnShow();			// 將圖形貼到畫面
        void SetPoint(int _x, int _y);
        void SetMovingType(MovingAnimation_Type _MovingType);
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetIntoHouse(bool flag);
        void SetIsGoOutside(bool flag); //是否外出
        void SetIsAlive(bool flag);     //是否活著
        void SetIsOnBattle(bool flag);  //是否在戰鬥
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
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
        bool MagicAttack_event(int _x1, int _x2, string type);
        bool PhysicalAttack_event(int tar_x1, int tar_x2);
        bool GetIsOnBattle();
        bool GetIsAlive();
        bool IsMouseOn(CPoint point);
        Attack_Type GetAttackType();
		MovingAnimation_Type GetMovingType();
    protected:
        int _x, _y;				//座標
        int movingSpeed;     //移動速度
        int floor;            //所在的樓層
        int MaxHp;
        int Hp;					//血量
        int ApDefense;			//魔法防禦
        int AdDefense;			//物理防禦
        int AttackPower;        //攻擊力
		int timeLevel;           //設定時間快慢
		int AttackCount;        //攻擊判定時間
		int timecount;
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
        bool isIntoHouse;
        bool isGoOutside;
        bool isAlive;                //是否存活
        bool isFirstShot;
        bool isOnBattle;
        bool isMusicEffectOn;
        bool isMouseOn;
		bool isKid;                 //是否為小孩(怪物)
        bool BattleTemp;
        Attack_Type AttackType; //攻擊模式
        MovingAnimation_Type nowMovingType;
        CAnimation* animation[7];
        MagicAttack* magicAttack[3];
        time_t nowTime, setTime;
    private:
};
}
