#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Room.h"
#include "RoomDataBoard.h"

namespace game_framework {
	RoomDataBoard::RoomDataBoard(Room thisRoom)
	{
		
	}
	RoomDataBoard::~RoomDataBoard()
	{
	}
	void RoomDataBoard::Initial()
	{
		x = 50;
		y = 50;
		bmp->LoadBitmap("Bitmaps\\gameRun\\RoomBoard.bmp", RGB(255, 255, 255));
		bmp->SetTopLeft(x, y);
	}
	void RoomDataBoard::OnShow()
	{
		bmp->ShowBitmap();
	}
}
