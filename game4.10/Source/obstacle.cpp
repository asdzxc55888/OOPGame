#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "obstacle.h"
namespace game_framework
{
Obstacle::Obstacle()
{
    Initial();
}
void Obstacle::Initial()
{
    for (int i = 0; i < Obstacle_maxSize; i++)
    {
        x1[i] = 0;
        x2[i] = 0;
        y1[i] = 0;
        y2[i] = 0;
    }

    size = 0;
}
void Obstacle::SetXY(int _x1, int _x2, int _y1, int _y2)
{
    x1[size] = _x1;
    x2[size] = _x2;
    y1[size] = _y1;
    y2[size] = _y2;
    size += 1;
}
void Obstacle::SetSize(int _size)
{
    size = _size;
}
int Obstacle::GetSize()
{
    return size;
}
bool Obstacle::isHit(int _x1, int _x2, int _y1, int _y2)
{
    for (int i = 0; i < size; i++)
    {
    
        if (!(_x1 == x1[i] && _x2 == x2[i] && _y1 == y1[i] && _y2 == y2[i]) && (_x2-12 >= x1[i] && _x1+12 < x2[i] && _y1 <= y2[i] && _y2 > y1[i]))
        {
            return true;
        }
    }

    return false;
}
}