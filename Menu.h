#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <SDL.h>
namespace Tmpl8 {
	class Menu
	{
	public:

		enum class ButtonTypes		//different types of buttons
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

		void Init(const vec2& in_pos, const int in_type);	//Sets the position of the buttons
		void Button(Surface* gameScreen);					//All buttons draw function and functionality of the buttons
		void DrawCheckBox(Surface* gameScreen);				//Draw function
		void TestClick();									//Tests if the checkbox is clicked
		bool TestClickBigButton();							//Tests if the big buttons is clicked
		void GoalSliderMark(Surface* gameScreen);			//Sets the end wall position by draging the slider
		
		vec2 pos;	//Position vector of the button
		float EndGoal;//Marks the end
		bool clicked = false;//if the button is clicked
		bool initialized = false;//if the button is set
	private:
		bool GoalSliderHold = false;//when is the slider hold
		int box_x;//X position of checkbox
		int type;//the button type
		float GoalSliderMarkPos = pos.x + 300;//the mark position
		static constexpr int text_width = 163;//big button width
		static constexpr int box_width = 40;//The width and height of the checkbox
		static constexpr int box_height = 40;


	};
}