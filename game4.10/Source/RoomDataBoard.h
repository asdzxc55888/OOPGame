#pragma once
namespace game_framework {
	class RoomDataBoard
	{
	public:
		RoomDataBoard(Room thisRoom);
		~RoomDataBoard();
		void Initial();
		void OnShow();
	private:
		int x, y;                  //®y¼Ð
		CMovingBitmap *bmp;
		
	};

}