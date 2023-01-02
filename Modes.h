#pragma once
#include "surface.h"
#include "template.h"
#include "Menu.h"
#include "Ball.h"
#include "PlatformJump.h"
#include <random>
namespace Tmpl8 {
	class Modes
	{
	public:

		enum class EnemyTypes
		{
			ball_bouncer = 0,
			follower = 1
		};

		void DarkMode(Surface* gameScreen, const Ball* ball, const Menu* menu);
		void Rockets(Surface* gameScreen, const Ball* ball, const Menu* menu, const float dt);
		void TheFloorIsLava(const Ball* ball, const Menu* menu, PlatformJump* platj);
		void Enemies(Surface* gameScreen, Ball* ball, const Menu* menu, const float dt);
		bool BeachballCollision(const Ball* ball, float x, float y);
		void BeachballBehaviour(Ball* ball, const float dt);
		void Chase(Surface* gameScreen, const Ball* ball, const Menu* menu);
		//Endless is in game.cpp

		bool lose = false;

		//rocket
		vec2 RocketPos;
		//TheFloorIsLava
		bool InitLavaPlat = false;
		//Chase
		float ChasingWallX;
		//enemies
		vec2 EnemiesPos;
		vec2 BeachballPos[2];
		EnemyTypes Etype;
	private:
		//darkmode
		float darkmodeY;
		//rocket
		float RocketTime;
		static constexpr int rocketwidth = 106;
		static constexpr int rocketheight = 42;
		//enemies
		bool InitRandom = false;
		float EnemiesVelY;
		float BeachballVelY;
		float EnemiesTime;
		float Moves = 1;
		static constexpr int height = 25;
		static constexpr int radius = 12;


	};
}