#pragma once
namespace game_framework {
	class RoomDataBoard
	{
	public:
		RoomDataBoard();
		~RoomDataBoard();
		void Initial();
	private:
		int x, y;                  //�y��
		CMovingBitmap bmp;
		
	};

}