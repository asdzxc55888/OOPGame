#pragma once
namespace game_framework {
	class RoomDataBoard
	{
	public:
		RoomDataBoard(int liveMonsterSize , string monsterType[3],int monsterGender[3] ,string monsterName[3],bool monsterIsKid[3], int number);
		~RoomDataBoard();
		void Initialize(int liveMonsterSize, string monsterType[3],int monsterGender[3], string monsterName[3], bool monsterIsKid[3], int number);
		void OnShow();
		void ShowName();
		void ShowRoomNumber();
	private:
		int x, y;                  //®y¼Ð
		int MonsterImgSize;
		int RoomNumber;
		string monsterName[3];
		CMovingBitmap bmp;
		CMovingBitmap MonsterImg[3];
	};

}