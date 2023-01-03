#pragma once
#include "template.h"
#include "surface.h"
#include "Ball.h"
namespace Tmpl8 {
	class PlatformSpeed
	{
	public:
		void Update(const int x, const int y);			//Updates the position of the speed platform
		void UpdateX(const Ball* ball);					//Updates the position of the speed platform relative to the ball
		void DrawPlatform(Surface* gameScreen);			//Draw function
		void TestCollision(Ball* ball);					//Tests collision on the ball and speed platform
		vec2 pos;		//Position vector of speed platform
	private:
		static constexpr int width = 62;		//The width and height of the speed platform
		static constexpr int height = 20;
	};
}