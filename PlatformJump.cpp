#include "PlatformJump.h"
namespace Tmpl8 {

	void PlatformJump::Update(const int x, const int y)		//Updates the position of the jump platform
	{
		pos.x = (float)x - 31;
		pos.y = (float)y - 10;
	}

	void PlatformJump::UpdateX(const Ball* ball)		//Updates the position of the jump platform relative to the ball
	{
		pos.x -= ball->vel.x;
	}

	void PlatformJump::DrawPlatform(Surface* gameScreen)		//Draw function
	{
		Sprite JumpPlatform(new Surface("assets/UI/Platforms/JumpPlatform.png"), 1);
		JumpPlatform.Draw(gameScreen, (int)pos.x, (int)pos.y);
	}

	void PlatformJump::TestCollision(Ball* ball)		//Tests collision on ball and jump platform
	{
		const float ballright = ball->pos.x + (float)ball->width;
		const float ballbottom = ball->pos.y + (float)ball->height;
		const float platformright = pos.x + (float)width;
		const float platformbottom = pos.y + (float)height;

		if (ballright >= pos.x &&
			ball->pos.x <= platformright &&
			ballbottom >= pos.y &&
			ball->pos.y <= platformbottom)
		{
			if (ball->vel.y > 0)
			{
				ball->pos.y = pos.y - (float)ball->height;
				ball->vel.y += 1;
				ball->vel.y = -ball->vel.y;
			}
			else if (ball->vel.y < 0)
			{
				ball->pos.y = pos.y + (float)height;
				ball->vel.y = -ball->vel.y;
			}
		}
	}

}