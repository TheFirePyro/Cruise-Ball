#pragma once
#include "surface.h"
#include "template.h"
#include "Ball.h"
#include "Menu.h"
namespace Tmpl8 {
	class UI
	{
	public:

		void DrawBase(Surface* gameScreen,Ball* ball, Menu* menu);		//Draw function for sky and ground
		void DrawBackground(Surface* gameScreen, Menu* menu);			//Draw function for the background
		void StartWall(Surface* gameScreen, Ball* ball);				//Draw function for the starting wall
		void EndWall(Surface* gameScreen, Ball* ball, float endgoal);	//Draw function for the ending wall
		//Base= sky 70, ground 432, between sky and ground 362, length 1670
		
		bool win = false;			//if you pass the endwall you win
		bool setPos = false;		//set position of starting wall when you win
		float BasePos;				//Updates the position of the sky and ground relative to the ball
		float start;				//Starting wall position
		float end;					//Ending wall position
	private:
		static constexpr int basex = 1670;		//Length of the sky and ground
		int position = 1;						//Position multiplier for sky and ground
	};
}