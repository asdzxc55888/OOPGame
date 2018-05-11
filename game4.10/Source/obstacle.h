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
		bool isHit(int _x1, int _x2, int _y1 , int _y2); //�O�_�I���ê��
		bool isHit(int _x1, int _x2, int _y1, int _y2,bool *direction); //�O�_�I���ê��
		bool isOverlapping(int _x1, int _x2, int _y1, int _y2, bool *direction); //�O�_���|
	private:
		int x1[Obstacle_maxSize], y1[Obstacle_maxSize],x2[Obstacle_maxSize],y2[Obstacle_maxSize]; //��ê���y��
		int size;  //��ê���ƶq
	};
}