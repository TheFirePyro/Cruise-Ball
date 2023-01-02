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
		void Update(const int x, const int y);
		void UpdateX(const Ball* ball);
		void DrawPlatform(Surface* gameScreen);
		vec2 pos;
		static constexpr int width = 80;
		static constexpr int height = 34;
	private:

	};
	class PlatformPortal2
	{
	public:
		void Update(const int x, const int y);
		void UpdateX(Ball* ball, PlatformPortal1* P1);
		void DrawPlatform(Surface* gameScreen);
		void Teleport(Ball* ball, PlatformPortal1* P1);
		bool TestCollision(PlatformPortal1* P1);
		bool TestWallCollision(Map* map);
		vec2 pos;
	private:
		static constexpr int width = 80;
		static constexpr int height = 34;
	};
}
