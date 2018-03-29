#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameEvent.h"
namespace game_framework {
	void ChoseEvent(GameEvent_number event)
	{
		switch (event)
		{
		case game_framework::MonsterGohome_eventNumber:
			//MonsterGohome_event(Room *_room);
			break;
		default:
			break;
		}
	}
	void MonsterGohome_event(Room *_room)
	{

	}
}