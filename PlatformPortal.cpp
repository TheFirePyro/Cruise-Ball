#include "PlatformPortal.h"
namespace Tmpl8 {


	void PlatformPortal1::Update(const int x, const int y)		//Updates the position of portal1
	{															
		pos.x = (float)x - 38;									
		pos.y = (float)y - 38;
	}

	void PlatformPortal1::UpdateX(const Ball* ball)				//Updates the position of portal2 relative to the ball
	{
		pos.x -= ball->vel.x;
	}

	void PlatformPortal1::DrawPlatform(Surface* gameScreen)		//Draw function
	{
		Sprite PortalPlatform1(new Surface("assets/UI/Platforms/PortalPlatform1.png"), 1);
		PortalPlatform1.Draw(gameScreen, (int)pos.x, (int)pos.y);
	}

	void PlatformPortal2::Update(const int x, const int y)			//Updates the position of portal2
	{
		pos.x = (float)x - 38;
		pos.y = (float)y - 38;
	}

	void PlatformPortal2::UpdateX(Ball* ball)		//Updates the position of portal2 relative to the ball
	{
		pos.x -= ball->vel.x;
	}

	void PlatformPortal2::DrawPlatform(Surface* gameScreen)				//Draw function
	{
		Sprite PortalPlatform2(new Surface("assets/UI/Platforms/PortalPlatform2.png"), 1);
		PortalPlatform2.Draw(gameScreen, (int)pos.x, (int)pos.y);
	}

	void PlatformPortal2::Teleport(Ball* ball, PlatformPortal1* P1)		//Teleports the ball to portal2
	{
		const float ballright = ball->pos.x + (float)ball->width;
		const float ballbottom = ball->pos.y + (float)ball->height;
		const float portalright = P1->pos.x + (float)P1->width;
		const float portalbottom = (P1->pos.y + 22) + (float)P1->height;

		if (ballright >= P1->pos.x &&
			ball->pos.x <= portalright &&
			ballbottom >= P1->pos.y + 22 &&
			ball->pos.y <= portalbottom &&
			pos.y > 60)
		{
			ball->pos.x = pos.x + 38;
			ball->pos.y = pos.y + 38;
		}
	}

	bool PlatformPortal2::TestPortal1Collision(const PlatformPortal1* P1) const		//Testing collision on portal1 and portal2 so that they are not on top of each other
	{
		int mousex;
		int mousey;
		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		const float portal2right = mousex - 38 + (float)width;
		const float portal2bottom = (mousey - 38 + 22) + (float)height;
		const float portal1right = P1->pos.x + (float)P1->width;
		const float portal1bottom = (P1->pos.y + 22) + (float)P1->height;

		return portal2right >= P1->pos.x &&
			mousex - 38 <= portal1right &&
			portal2bottom >= P1->pos.y + 22 &&
			mousey - 38 + 22 <= portal1bottom;
	}

}