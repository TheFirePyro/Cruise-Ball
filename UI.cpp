#include "UI.h"
namespace Tmpl8
{
	
	void UI::DrawBase(Surface* gameScreen, Ball* ball, Menu* menu)		//Draw function for sky and ground
	{
		if (menu->clicked)
		{
			Sprite FloorIsLava(new Surface("assets/UI/FloorIsLava.png"), 1);
			if (BasePos > basex * position)
			{
				position++;
			}
			if (BasePos < basex * (position - 1))
			{
				position--;
			}
			BasePos += ball->vel.x;
			FloorIsLava.Draw(gameScreen, basex * (position - 2) - (int)BasePos, 0);
			FloorIsLava.Draw(gameScreen, basex * (position - 1) - (int)BasePos, 0);
			FloorIsLava.Draw(gameScreen, basex * position - (int)BasePos, 0);
		}
		else
		{
			Sprite Base(new Surface("assets/UI/Base.png"), 1);
			if (BasePos > basex * position)
			{
				position++;
			}
			if (BasePos < basex * (position - 1))
			{
				position--;
			}
			BasePos += ball->vel.x;
			Base.Draw(gameScreen, basex * (position - 2) - (int)BasePos, 0);
			Base.Draw(gameScreen, basex * (position - 1) - (int)BasePos, 0);
			Base.Draw(gameScreen, basex * position - (int)BasePos, 0);
		}
	}

	void UI::DrawBackground(Surface* gameScreen, Menu* menu)		//Draw function for the background
	{
		if (menu->clicked)
		{
			Sprite background(new Surface("assets/UI/background-darkmode.png"), 1);
			background.Draw(gameScreen, 0, 0);
		}
		else
		{
			Sprite background(new Surface("assets/UI/background.png"), 1);
			background.Draw(gameScreen, 0, 0);
		}
	}

	void UI::StartWall(Surface* gameScreen, Ball* ball)		//Draw function for the starting wall
	{
		if (setPos == false)
		{ 
			start = 0;
		}
		start -= ball->vel.x;
		Sprite startwall(new Surface("assets/UI/Start-EndWall.png"), 1);
		startwall.Draw(gameScreen, (int)start, 0);
		if (ball->pos.x <= start + 50)
		{
			ball->pos.x = start + 100;
			ball->vel = -ball->vel;
		}
	}

	void UI::EndWall(Surface* gameScreen, Ball* ball, float endgoal)		//Draw function for the ending wall
	{
		if (!(ball->pos.x == 300))
		{
			end -= (ball->pos.x - 300);
		}
		if (setPos == false)
		{
			end = endgoal;
		}
		end -= ball->vel.x;
		Sprite endwall(new Surface("assets/UI/Start-EndWall.png"), 1);
		endwall.Draw(gameScreen, (int)end, 0);
		if (ball->pos.x >= end)
		{
			win = true;
		}
	}

}