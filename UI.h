#pragma once
#include "surface.h"
#include "template.h"
#include "Ball.h"
#include "Menu.h"
namespace Tmpl8 {
	class UI
	{
	public:

		void DrawBase(Surface* gameScreen,Ball* ball, Menu* menu);
		void DrawBackground(Surface* gameScreen, Menu* menu);
		void StartWall(Surface* gameScreen, Ball* ball);
		void EndWall(Surface* gameScreen, Ball* ball, float endgoal);
		//Base= 70 , 432 , between 372 , long 1670
		
		bool win = false;
		bool setPos = false;
		float BaseVel;
		float start;
		float end;
	private:
		static constexpr int basex = 1670;
		int position = 1;
	};
}