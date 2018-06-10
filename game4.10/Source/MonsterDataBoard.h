#pragma once
namespace game_framework
{
class MonsterDataBoard
{
    public:
        MonsterDataBoard(int MaxHp, int ApD, int AdD, int dps, string MonsterType, int gneder, bool flag, string name);
        MonsterDataBoard();
        ~MonsterDataBoard();
        void Initialize(int MaxHp, int ApD, int AdD, int dps, string MonsterType, int gneder, bool flag, string name);
        void ShowHpBar(int percent);
        void ShowName();
        void SetData(int hp, int maxHp, int ApD, int AdD, int dps);
        void SetPoint(int _x, int _y);
        void OnShow();
    private:
        int GetDigit(int x);
        int x, y;
        string name;
        CMovingBitmap Board, Picture;
        CInteger* Hp, *MaxHp;
        CInteger* AttackPower;
        CInteger* AdDefense;
        CInteger* ApDefense;
        bool isLoadBitmaps;
};
}

