#include "Map.h"

namespace Tmpl8
{

	void Map::Init(float in_x0, float in_y0, float in_x1, float in_y1)
	{
		if (initialized == false)
		{
			pos0.x = in_x0;
			pos0.y = in_y0;
			pos1.x = in_x1;
			pos1.y = in_y1;
			initialized = true;
		}
	}

	void Map::Spawn(Surface* gameScreen, Ball* ball, const int direction)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		if (direction % 2 == 0) //up
		{
			std::uniform_int_distribution<int> xDist0(800, 850);
			std::uniform_int_distribution<int> yDist0(30, 31);
			std::uniform_int_distribution<int> xDist1(900, 950);
			std::uniform_int_distribution<int> yDist1(100, 150);
			Init((float)xDist0(rng), (float)yDist0(rng), (float)xDist1(rng), (float)yDist1(rng));
		}
		else //down
		{
			std::uniform_int_distribution<int> xDist0(800, 850);
			std::uniform_int_distribution<int> yDist0(300, 350);
			std::uniform_int_distribution<int> xDist1(900, 950);
			std::uniform_int_distribution<int> yDist1(442, 443);
			Init((float)xDist0(rng), (float)yDist0(rng), (float)xDist1(rng), (float)yDist1(rng));
		}
		UpdateX(ball);
		DrawWall(gameScreen);
		TestCollision(ball);
	}

	void Map::UpdateX(const Ball* ball)
	{
		pos0.x -= ball->vel.x;
		pos1.x -= ball->vel.x;
	}

	void Map::DrawWall(Surface* gameScreen)
	{
		for (int i = 0; i < 1; ++i)
		{
			gameScreen->Box((int)pos0.x + i, (int)pos0.y + i, (int)pos1.x - i, (int)pos1.y - i, 0xFFFFFF);
		}
	}

	void Map::TestCollision(Ball* ball)
	{
		const float ballright = ball->pos.x + (float)ball->width;
		const float ballbottom = ball->pos.y + (float)ball->height;
		const float distanceTOP = ballbottom - pos0.y;
		const float distanceBOTTOM = pos1.y - ball->pos.y;
		const float distanceLEFT = ballright - pos0.x;
		const float distanceRIGHT = pos1.x - ball->pos.x;


		if (ballright >= pos0.x &&
			ball->pos.x <= pos1.x &&
			ballbottom >= pos0.y &&
			ball->pos.y <= pos1.y)
		{
			if (distanceTOP < distanceBOTTOM &&
				distanceTOP < distanceLEFT &&
				distanceTOP < distanceRIGHT)
			{
				ball->pos.y = pos0.y - (float)ball->height;
				ball->vel.y = -ball->vel.y;
			}
			if (distanceBOTTOM < distanceTOP &&
				distanceBOTTOM < distanceLEFT &&
				distanceBOTTOM < distanceRIGHT)
			{
				ball->pos.y = pos1.y;
				ball->vel.y = -ball->vel.y;
			}
			if (distanceLEFT < distanceTOP &&
				distanceLEFT < distanceBOTTOM &&
				distanceLEFT < distanceRIGHT)
			{
				ball->pos.x = pos0.x - (float)ball->width;
				ball->vel.x = -ball->vel.x;
			}
			if (distanceRIGHT < distanceTOP &&
				distanceRIGHT < distanceBOTTOM &&
				distanceRIGHT < distanceRIGHT)
			{
				ball->pos.x = pos1.x;
				ball->vel.x = -ball->vel.x;
			}
		}
	}

}