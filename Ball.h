#pragma once
#include "surface.h"
#include "template.h"
#include <Windows.h>
#include <assert.h>
namespace Tmpl8 {
	class Ball
	{
	public:

		void Init(const vec2& in_pos, const vec2& in_vel);
		void DrawBall(Surface* gameScreen);
		void BallBehaviour(const float dt);
		void UpAndDownBoundaries();
		void XvelSlowDown();
		void MaxVelocity();
		void Trajectory(Surface* gameScreen, const float dt);
		vec2 pos;
		vec2 vel;
		float meter;
		static constexpr int width = 25;
		static constexpr int height = 25;
		static constexpr int radius = 12;
		bool initialized = false;
	private:
		float ClampX;
		bool HitTop = false;
		bool HitBottom = false;

	};
}
