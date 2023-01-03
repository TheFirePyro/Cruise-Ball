#pragma once
#include "surface.h"
#include "template.h"
#include "Ball.h"
#include <random>
namespace Tmpl8 {
	class Map
	{
	public:
		void Init(float in_x, float in_y, float in_width, float in_height);		//Sets the wall position
		void Spawn(Surface* gameScreen, Ball* ball, const int direction);		//Combines all functions and set position parameters
		void UpdateX(const Ball* ball);											//Updates the position of the wall relative to the ball
		void DrawWall(Surface* gameScreen);										//Draw function
		void TestCollision(Ball* ball);											//Tests collision on the ball and wall
		vec2 pos0;//Position vector of point one
		vec2 pos1;//Position vector of point two
		bool initialized = false;
	private:
		
	};
}