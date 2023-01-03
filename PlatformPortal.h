#pragma once
#include "template.h"
#include "surface.h"
#include "Ball.h"
#include <SDL.h>
#include "Map.h"
namespace Tmpl8 {
	class PlatformPortal1
	{
	public:
		void Update(const int x, const int y);				//Updates the position of portal1
		void UpdateX(const Ball* ball);						//Updates the position of portal2 relative to the ball
		void DrawPlatform(Surface* gameScreen);				//Draw function
		vec2 pos;	//Position vector of portal1
		static constexpr int width = 80;	//the width and height of portal1
		static constexpr int height = 34;
	private:

	};
	class PlatformPortal2
	{
	public:
		void Update(const int x, const int y);				//Updates the position of portal2
		void UpdateX(Ball* ball);							//Updates the position of portal2 relative to the ball
		void DrawPlatform(Surface* gameScreen);				//Draw function
		void Teleport(Ball* ball, PlatformPortal1* P1);		//Teleports the ball to portal2 if the ball is in portal1
		bool TestPortal1Collision(const PlatformPortal1* P1) const;		//Testing collision on portal1 and portal2 so that they are not on top of each other
		vec2 pos;	//Position vector of portal2
	private:
		static constexpr int width = 80;	//The width and height of portal2
		static constexpr int height = 34;
	};
}
