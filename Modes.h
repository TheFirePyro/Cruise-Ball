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

		enum class EnemyTypes		//different types of Enemies
		{
			ball_bouncer = 0,
			follower = 1
		};

		void DarkMode(Surface* gameScreen, const Ball* ball, const Menu* menu);
		void Rockets(Surface* gameScreen, const Ball* ball, const Menu* menu, const float dt);
		void TheFloorIsLava(const Ball* ball, const Menu* menu, PlatformJump* platj);
		void Enemies(Surface* gameScreen, Ball* ball, const Menu* menu, const float dt);
		bool BeachballCollision(const Ball* ball, float x, float y);//Tests collision on ball and beachball
		void BeachballBehaviour(Ball* ball, const float dt);
		void Chase(Surface* gameScreen, const Ball* ball, const Menu* menu);
		//Endless is in game.cpp

		bool lose = false;	//if you get hit you lose

		//rocket
		vec2 RocketPos;	//Position vector of rockets

		//TheFloorIsLava
		bool InitLavaPlat = false;	//Puts a jump platform so you not die

		//Chase
		float ChasingWallX;	//X position for the chasing wall

		//enemies
		vec2 EnemiesPos;		//Position vector of the enemies
		vec2 BeachballPos[2];	//Position vector of the beachballs
		EnemyTypes Etype;		//The type of the enemy
	private:
		//darkmode
		float darkmodeY;//Y position for dark mode

		//rocket
		float RocketTime;		//The time period between rockets
		static constexpr int rocketwidth = 106;	//The width and height of the rockets
		static constexpr int rocketheight = 42;

		//enemies
		bool InitRandom = false;		//The enemy randomizer
		float EnemiesVelY;		//Y position for the enemies
		float BeachballVelY;	//Y position for the beachballs
		float EnemiesTime;		//The time period between enemies
		float Moves = 1;		//The number times that the follower(enemy type) moves
		static constexpr int height = 25;//The width and height of the enemies
		static constexpr int radius = 12;


	};
}