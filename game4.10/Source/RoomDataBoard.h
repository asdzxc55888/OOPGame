#pragma once
namespace game_framework
{
class RoomDataBoard
{
#define RentBar_x 145
#define RentBar_y 293
    public:
        RoomDataBoard(int liveMonsterSize, string monsterType[3], int monsterGender[3], string monsterName[3], bool monsterIsKid[3], int number, int _rent);
        ~RoomDataBoard();
        void Initialize(int liveMonsterSize, string monsterType[3], int monsterGender[3], string monsterName[3], bool monsterIsKid[3], int number, int _rent);
        void OnShow();
        void ShowName();
        void ShowRoomNumber();
		void ShowRentBar();
    private:
        int x, y;                  //®y¼Ð
        int MonsterImgSize;
        int RoomNumber;
		int rent;
        string monsterName[3];
        CMovingBitmap bmp;
        CMovingBitmap MonsterImg[3];
		CInteger *rent_int;
};

}