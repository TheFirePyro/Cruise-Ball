#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <SDL.h>
namespace Tmpl8 {
	class Menu
	{
	public:

		enum class ButtonTypes
		{
			dark_mode = 0,
			rockets = 1,
			floor_is_lava  = 2,
			enemies = 3,
			chase = 4,
			endless = 5,
			start = 6,
			retry = 7,
			menu = 8,
			exit = 9,
			resume = 10,
			goal_slider = 11
		};

		void Init(const vec2& in_pos, const int in_type);
		void Button(Surface* gameScreen);
		void DrawCheckBox(Surface* gameScreen);
		void TestClick();
		bool TestClickBigButton();
		void GoalSliderMark(Surface* gameScreen);
		
		vec2 pos;
		float EndGoal;
		bool clicked = false;
		bool initialized = false;
	private:
		bool GoalSliderHold = false;
		int box_x;
		int type;
		float GoalSliderMarkPos = pos.x + 300;
		static constexpr int text_width = 163;
		static constexpr int box_width = 40;
		static constexpr int box_height = 40;


	};
}