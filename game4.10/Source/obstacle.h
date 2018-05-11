#pragma once
namespace game_framework {
#define Obstacle_maxSize 100
	class Obstacle {
	public:
		Obstacle();
		void Initial();
		void SetXY(int _x1, int _x2, int _y1, int _y2);
		void SetSize(int _size);
		int GetSize();
		bool isHit(int _x1, int _x2, int _y1 , int _y2); //是否碰到障礙物
		bool isHit(int _x1, int _x2, int _y1, int _y2,bool *direction); //是否碰到障礙物
		bool isOverlapping(int _x1, int _x2, int _y1, int _y2, bool *direction); //是否重疊
	private:
		int x1[Obstacle_maxSize], y1[Obstacle_maxSize],x2[Obstacle_maxSize],y2[Obstacle_maxSize]; //障礙物座標
		int size;  //障礙物數量
	};
}