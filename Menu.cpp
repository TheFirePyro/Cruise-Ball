#include "Menu.h"

namespace Tmpl8 
{
	void Menu::Init(const vec2& in_pos, const int in_type)
	{
		if (initialized == false)
		{
			pos = in_pos;
			type = in_type;
			box_x = (int)pos.x + text_width;
			initialized = true;
		}
	}

	void Menu::Button(Surface* gameScreen)
	{
		switch (ButtonTypes(type))
		{
		case Menu::ButtonTypes::dark_mode:
		{Sprite darkmode(new Surface("assets/UI/Menu/DarkMode-options.png"), 1);
		darkmode.Draw(gameScreen, (int)pos.x, (int)pos.y);
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::rockets:
		{Sprite rockets(new Surface("assets/UI/Menu/Rockets-options.png"), 1);
		rockets.Draw(gameScreen, (int)pos.x, (int)pos.y); 
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::floor_is_lava:
		{Sprite floorislava(new Surface("assets/UI/Menu/FloorIsLava-options.png"), 1);
		floorislava.Draw(gameScreen, (int)pos.x, (int)pos.y);
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::enemies:
		{Sprite enemies(new Surface("assets/UI/Menu/Enemies-options.png"), 1);
		enemies.Draw(gameScreen, (int)pos.x, (int)pos.y);
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::chase:
		{Sprite chase(new Surface("assets/UI/Menu/Chase-options.png"), 1);
		chase.Draw(gameScreen, (int)pos.x, (int)pos.y);
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::endless:
		{Sprite endless(new Surface("assets/UI/Menu/Endless-options.png"), 1);
		endless.Draw(gameScreen, (int)pos.x, (int)pos.y);
		TestClick();
		DrawCheckBox(gameScreen); }
		break;
		case Menu::ButtonTypes::start:
		{Sprite start(new Surface("assets/UI/Menu/Start-options.png"), 1);
		start.Draw(gameScreen, (int)pos.x, (int)pos.y); }
		break;
		case Menu::ButtonTypes::retry:
		{Sprite Retry(new Surface("assets/UI/Menu/Retry-options.png"), 1);
		Retry.Draw(gameScreen, (int)pos.x, (int)pos.y); }
		break;
		case Menu::ButtonTypes::menu:
		{Sprite Menu(new Surface("assets/UI/Menu/Menu-options.png"), 1);
		Menu.Draw(gameScreen, (int)pos.x, (int)pos.y); }
		break;
		case Menu::ButtonTypes::exit:
		{Sprite Exit(new Surface("assets/UI/Menu/Exit-options.png"), 1);
		Exit.Draw(gameScreen, (int)pos.x, (int)pos.y); }
		break;
		case Menu::ButtonTypes::resume:
		{Sprite Resume(new Surface("assets/UI/Menu/Resume-options.png"), 1);
		Resume.Draw(gameScreen, (int)pos.x, (int)pos.y); }
		break;
		case Menu::ButtonTypes::goal_slider:
		{Sprite Border(new Surface("assets/UI/Menu/GoalSliderBorder-options.png"), 1);
		Border.Draw(gameScreen, (int)pos.x - 5, (int)pos.y - 32);
		Sprite GoalSlider(new Surface("assets/UI/Menu/GoalSlider-options.png"), 1);
		GoalSlider.Draw(gameScreen, (int)pos.x, (int)pos.y);
		GoalSliderMark(gameScreen); }
		break;
		}
	}

	void Menu::DrawCheckBox(Surface* gameScreen)
	{
		Sprite CheckBoxtrue(new Surface("assets/UI/Menu/CheckBox-true.png"), 1);
		Sprite CheckBoxfalse(new Surface("assets/UI/Menu/CheckBox-false.png"), 1);
		if (clicked)
		{
			CheckBoxtrue.Draw(gameScreen, box_x, (int)pos.y);
		}
		else if (!clicked)
		{
			CheckBoxfalse.Draw(gameScreen, box_x, (int)pos.y);
		}
	}

	void Menu::TestClick()
	{
		int mousex;
		int mousey;
		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		const int right = box_x + box_width;
		const int bottom = (int)pos.y + box_height;
		
		if (mousex >= box_x &&
			mousex <= right &&
			mousey >= pos.y &&
			mousey <= bottom)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 1 && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (clicked)
				{
					clicked = false;
				}
				else if (!clicked)
				{
					clicked = true;
				}
			}
		}
	}

	bool Menu::TestClickBigButton()
	{
		int mousex;
		int mousey;
		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		const int right = (int)pos.x + text_width;
		const int bottom = (int)pos.y + box_height;

		if (mousex >= pos.x &&
			mousex <= right &&
			mousey >= pos.y &&
			mousey <= bottom)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 1 && GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				return true;
			}
		}
		return false;
	}

	void Menu::GoalSliderMark(Surface* gameScreen)
	{
		int mousex;
		int mousey;
		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite Mark(new Surface("assets/UI/Menu/GoalSliderMark-options.png"), 1);
		Mark.Draw(gameScreen, (int)GoalSliderMarkPos, (int)pos.y - 16);
		const int Slideright = (int)pos.x + 605;
		const int Slidebottom = (int)pos.y + 22;
		if (mousex >= pos.x - 5 &&
			mousex <= Slideright &&
			mousey >= pos.y - 12 &&
			mousey <= Slidebottom)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				GoalSliderHold = true;
			}
		}
		if (GoalSliderHold)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				GoalSliderMarkPos = (float)mousex;
				if (GoalSliderMarkPos <= pos.x)
				{
					GoalSliderMarkPos = pos.x;
				}
				else if (GoalSliderMarkPos >= pos.x + 600 - 22)
				{
					GoalSliderMarkPos = pos.x + 600 - 22;
				}
			}
			else
			{
				GoalSliderHold = false;
			}
		}
		EndGoal = GoalSliderMarkPos * 16;
	}


}