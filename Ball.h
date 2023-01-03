#pragma once
#include "surface.h"
#include "template.h"
#include <Windows.h>
#include <assert.h>
namespace Tmpl8 {
	class Ball
	{
	public:

		void Init(const vec2& in_pos, const vec2& in_vel);			//Sets the ball position
		void DrawBall(Surface* gameScreen);							//Draw function
		void BallBehaviour(const float dt);
		void Trajectory(Surface* gameScreen, const float dt);		//A simple trajectory of the ball
		vec2 pos;//Position vector of the ball
		vec2 vel;//Velocity vector of the ball
		float meter;//How many meters you have passed
		static constexpr int width = 25;//The width and height of the ball
		static constexpr int height = 25;
		static constexpr int radius = 12;//Ball radius used in Modes.cpp
		bool initialized = false;//Is the ball initialized
	private:
		void UpAndDownBoundaries();
		void XvelSlowDown();
		void MaxVelocity();
		float ClampX;//Locks the ball on 300 X position
		bool HitTop = false;//if the sky is hit
		bool HitBottom = false;//if the ground in hit

	};
}
