#pragma once
#include "template.h"
#include "surface.h"
#include "Ball.h"
namespace Tmpl8 {
	class PlatformJump
	{
	public:
		void Update(const int x, const int y);			//Updates the position of the jump platform
		void UpdateX(const Ball* ball);					//Updates the position of the jump platform relative to the ball
		void DrawPlatform(Surface* gameScreen);			//Draw function
		void TestCollision(Ball* ball);					//Tests collision on the ball and jump platform
		vec2 pos;		//Position vector of jump platform
	private:
		static constexpr int width = 62;		//The width and height of the jump platform
		static constexpr int height = 20;
	};
}
