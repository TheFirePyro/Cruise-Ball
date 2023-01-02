#pragma once
#include "template.h"
#include "surface.h"
#include "Ball.h"
namespace Tmpl8 {
	class PlatformSpeed
	{
	public:
		void Update(const int x, const int y);
		void UpdateX(const Ball* ball);
		void DrawPlatform(Surface* gameScreen);
		void TestCollision(Ball* ball);
		vec2 pos;
	private:
		static constexpr int width = 62;
		static constexpr int height = 20;
	};
}