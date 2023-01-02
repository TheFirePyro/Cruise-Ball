#include "PlatformSpeed.h"
namespace Tmpl8 {

	void PlatformSpeed::Update(const int x, const int y)
	{
		pos.x = (float)x - 31;
		pos.y = (float)y - 10;
	}

	void PlatformSpeed::UpdateX(const Ball* ball)
	{
		pos.x -= ball->vel.x;
	}

	void PlatformSpeed::DrawPlatform(Surface* gameScreen)
	{
		Sprite SpeedPlatform(new Surface("assets/UI/Platforms/SpeedPlatform.png"), 1);
		SpeedPlatform.Draw(gameScreen, (int)pos.x, (int)pos.y);
	}

	void PlatformSpeed::TestCollision(Ball* ball)
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
				ball->vel.y = -ball->vel.y * 0.1f;
				ball->vel.x += 10;
				ball->vel.x = +ball->vel.x;
			}
			else if (ball->vel.y < 0)
			{
				ball->pos.y = pos.y + (float)height;;
				ball->vel.y = -ball->vel.y * 0.1f;
				ball->vel.x += 10;
				ball->vel.x = +ball->vel.x;
			}
		}
	}

}