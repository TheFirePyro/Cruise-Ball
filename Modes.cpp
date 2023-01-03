#include "Modes.h"
#include <Windows.h>
namespace Tmpl8
{

	void Modes::DarkMode(Surface* gameScreen, const Ball* ball, const Menu* menu)
	{
		if (menu->clicked)
		{
			darkmodeY = -362 + ball->pos.y;
			Sprite darkmode(new Surface("assets/UI/DarkMode.png"), 1);
			darkmode.Draw(gameScreen, -5, (int)darkmodeY);
		}
	}

	void Modes::Rockets(Surface* gameScreen, const Ball* ball, const Menu* menu, const float dt)
	{
		if (menu->clicked)
		{
			RocketTime += dt * 0.01f;
			if (RocketTime > 100)
			{
				RocketPos.x -= (ball->vel.x + 10);
				Sprite rocket(new Surface("assets/UI/Rocket.png"), 1);
				rocket.Draw(gameScreen, (int)RocketPos.x, (int)RocketPos.y);
				if (RocketPos.x < ball->pos.x - 550)
				{
					RocketTime = 0;
				}
			}
			else if (RocketTime > 75)
			{
				Sprite warning(new Surface("assets/UI/Rocket-warning.png"), 1);
				warning.Draw(gameScreen, 800 - 112, (int)RocketPos.y);
			}
			else if (RocketTime > 50)
			{
				RocketPos.y = ball->pos.y;
				if ((int)RocketTime % 4 != 0)
				{
					Sprite warning(new Surface("assets/UI/Rocket-warning.png"), 1);
					warning.Draw(gameScreen, 800 - 112, (int)RocketPos.y);
				}
			}
			else
			{
				RocketPos.x = ball->pos.x + 550;
			}
			const float ballright = ball->pos.x + (float)ball->width;
			const float ballbottom = ball->pos.y + (float)ball->height;
			const float platformright = RocketPos.x + (float)rocketwidth;
			const float platformbottom = RocketPos.y + (float)rocketheight;
			if (ballright >= RocketPos.x &&
				ball->pos.x <= platformright &&
				ballbottom >= RocketPos.y - 8 &&
				ball->pos.y <= platformbottom)
			{
				lose = true;
				RocketTime = 0;
			}
		}
	}

	void Modes::TheFloorIsLava(const Ball* ball, const Menu* menu, PlatformJump* platj)
	{
		if (menu->clicked)
		{
			if (!InitLavaPlat)
			{
				platj->Update(310, 350);
				InitLavaPlat = true;
			}
			if (ball->pos.y > (432 - ball->height))
			{
				lose = true;
			}
		}
	}

	void Modes::Enemies(Surface* gameScreen, Ball* ball, const Menu* menu, const float dt)
	{
		if (menu->clicked)
		{
			EnemiesTime += dt * 0.01f;
			if (EnemiesTime > 150)
			{
				if (!InitRandom)
				{
					std::random_device rd;
					std::mt19937 rng(rd());
					std::uniform_int_distribution<int> typeDist(0, 1);
					Etype = EnemyTypes(typeDist(rng));
					InitRandom = true;
				}
				switch (Etype)
				{
				case Modes::EnemyTypes::ball_bouncer:
				{
				Sprite ball_bouncer(new Surface("assets/UI/follower.png"), 1);
				ball_bouncer.Draw(gameScreen, (int)EnemiesPos.x, (int)EnemiesPos.y);
				Sprite Beachball0(new Surface("assets/UI/beachball.png"), 1);
				Beachball0.Draw(gameScreen, (int)BeachballPos[0].x, (int)BeachballPos[0].y);
				Sprite Beachball1(new Surface("assets/UI/beachball.png"), 1);
				Beachball1.Draw(gameScreen, (int)BeachballPos[1].x, (int)BeachballPos[1].y);
				if (BeachballCollision(ball, EnemiesPos.x, EnemiesPos.y)) lose = true, EnemiesTime = 0;
				BeachballBehaviour(ball, dt);
				}
				break;
				case Modes::EnemyTypes::follower:
				{
				Sprite follower(new Surface("assets/UI/follower.png"), 1);
				follower.Draw(gameScreen, (int)EnemiesPos.x, (int)EnemiesPos.y);
				if (BeachballCollision(ball, EnemiesPos.x, EnemiesPos.y)) lose = true, EnemiesTime = 0;
				if (EnemiesTime > 10 * Moves)
				{
					Moves++;
					if (ball->pos.y > EnemiesPos.y)
						EnemiesPos.y += 5;
					else
						EnemiesPos.y -= 5;
				}
				}
				break;
				}
				EnemiesPos.x -= (ball->vel.x + 1);
				BeachballPos[0].x -= (ball->vel.x + 1);
				BeachballPos[1].x -= (ball->vel.x + 1);
				if (EnemiesPos.x < ball->pos.x - 550)
				{
					Moves = 1;
					EnemiesTime = 0;
					InitRandom = false;
				}
			}
			else
			{
				EnemiesPos.x = ball->pos.x + 550;
				BeachballPos[0].x = ball->pos.x + 550;
				BeachballPos[1].x = ball->pos.x + 550;
				EnemiesPos.y = 250;
				BeachballPos[1].y = 300;
				EnemiesVelY = 0;
				BeachballVelY = 0;
			}
		}
	}

	bool Modes::BeachballCollision(const Ball* ball, float x, float y)//Sphere-Sphere Collision
	{
		float xdist = x - ball->pos.x;
		float ydist = y - ball->pos.y;
		float sqrRadius = (radius + ball->radius) * (radius + ball->radius);
		float sqrdistance = (xdist * xdist) + (ydist * ydist);
		if (sqrdistance <= sqrRadius)
		{
			return true;
		}
		return false;
	}

	void Modes::BeachballBehaviour(Ball* ball, const float dt)
	{
		BeachballPos[0].y = 442 - height;
		if (BeachballCollision(ball, BeachballPos[0].x, BeachballPos[0].y))
		{
			float xdist = BeachballPos[0].x - ball->pos.x;
			float ydist = BeachballPos[0].y - ball->pos.y;
			float distance = sqrtf(xdist * xdist + ydist * ydist);
			float fix = (ball->height + height) - distance;
			float fraction = fix / distance;
			ball->vel.x -= fraction * xdist * 0.3f;
			ball->vel.y -= fraction * ydist * 0.3f;
		}
		if (BeachballCollision(ball, BeachballPos[1].x, BeachballPos[1].y))
		{
			float xdist = BeachballPos[1].x - ball->pos.x;
			float ydist = BeachballPos[1].y - ball->pos.y;
			float distance = sqrtf(xdist * xdist + ydist * ydist);
			float fix = (ball->height + height) - distance;
			float fraction = fix / distance;
			ball->vel.x -= fraction * xdist * 0.3f;
			ball->vel.y -= fraction * ydist * 0.3f;
		}
		if (BeachballVelY > 20)
		{
			BeachballVelY = 10;
		}
		if (EnemiesVelY > 20)
		{
			EnemiesVelY = 10;
		}
		if (BeachballPos[1].y > BeachballPos[0].y - height)
		{
			BeachballPos[1].y = BeachballPos[0].y - height;
			BeachballVelY = -BeachballVelY;
		}
		else if (EnemiesPos.y > BeachballPos[1].y - height)
		{
			EnemiesPos.y = BeachballPos[1].y - height;
			EnemiesVelY = -EnemiesVelY;
		}
		else
		{
			EnemiesPos.y += EnemiesVelY * (dt * 0.03f);
			EnemiesVelY += (dt * 0.03f);
			BeachballPos[1].y += BeachballVelY * (dt * 0.03f);
			BeachballVelY += (dt * 0.03f);
		}
	}

	void Modes::Chase(Surface* gameScreen, const Ball* ball, const Menu* menu)
	{
		if (menu->clicked)
		{
			if (ball->vel.x > 0)
			{
				ChasingWallX -= ball->vel.x - 7;
			}
			else
			{
				ChasingWallX -= (ball->vel.x - 2);
			}
			Sprite ChasingWall(new Surface("assets/UI/ChasingWall.png"), 1);
			ChasingWall.Draw(gameScreen, (int)ChasingWallX, 0);
			if (ball->pos.x <= ChasingWallX + 96)
			{
				lose = true;
			}
		}
	}


}