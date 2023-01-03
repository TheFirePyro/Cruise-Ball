#include "Ball.h"
namespace Tmpl8 {



	void Ball::Init(const vec2& in_pos, const vec2& in_vel)	//Sets the ball position
	{
		assert(initialized == false);
		pos = in_pos;
		ClampX = in_pos.x;
		vel = in_vel;
		initialized = true;
	}

	void Ball::DrawBall(Surface* gameScreen) //Draw function
	{
		assert(initialized == true);
		Sprite Ball(new Surface("assets/UI/kiwi.png"), 1);
		Ball.Draw(gameScreen, (int)pos.x, (int)pos.y);
	}

	void Ball::BallBehaviour(const float dt)
	{
		assert(initialized == true);
		UpAndDownBoundaries();
		XvelSlowDown();
		MaxVelocity();

		meter += vel.x;

		if (HitTop == false && HitBottom == false)
		{
			pos.y += vel.y * (dt * 0.03f);
			vel.y += (dt * 0.03f);
		}
		if (!(pos.x == ClampX))
		{
			pos.x = ClampX;
		}
	}

	void Ball::UpAndDownBoundaries()
	{
		if (pos.y < 70)
		{
			pos.y = 75;
			vel.y = -vel.y;
			HitTop = true;
		}
		else if (pos.y > (437 - height))
		{
			pos.y = 432  - height;
			vel.y = -vel.y;
			HitBottom = true;
		}
		else
		{
			HitTop = false;
			HitBottom = false;
		}
	}

	void Ball::XvelSlowDown()
	{
		if (vel.x > 0)
		{
			vel.x -= 0.02f;
		}
		else if (vel.x < 0)
		{
			vel.x += 0.02f;
		}
	}

	void Ball::MaxVelocity()
	{
		if (vel.y > 15)
		{
			vel.y = 15;
		}
		if (vel.x > 10)
		{
			vel.x = 10;
		}
	}

	void Ball::Trajectory(Surface* gameScreen, const float dt) //A simple trajectory of the ball
	{
		assert(initialized == true);
		for (int i = 0; i < 50; i++)
		{
			float x = pos.x + width / 2;
			float y = pos.y + height / 2;
			float vx = vel.x;
			float vy = vel.y;
			if ((int)vx > 0)
			{
				vx -= 0.02f * i;
			}
			else if ((int)vx < 0)
			{
				vx += 0.02f * i;
			}
			vy += (dt * 0.03f) * i;
			y += vy * (dt * 0.03f) * i;
			x += (vx * 1.5f) * i;
			gameScreen->Line(x, y, x, y, 0x00000);
		}
	}

}