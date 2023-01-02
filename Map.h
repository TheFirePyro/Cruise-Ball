#pragma once
#include "surface.h"
#include "template.h"
#include "Ball.h"
#include <random>
namespace Tmpl8 {
	class Map
	{
	public:
		void Init(float in_x, float in_y, float in_width, float in_height);
		void Spawn(Surface* gameScreen, Ball* ball, const int direction);
		void UpdateX(const Ball* ball);
		void DrawWall(Surface* gameScreen);
		void TestCollision(Ball* ball);
		vec2 pos0;
		vec2 pos1;
		bool initialized = false;
	private:
		
	};
}