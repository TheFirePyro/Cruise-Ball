#pragma once
#include "Ball.h"
#include "PlatformJump.h"
#include "PlatformSpeed.h"
#include "PlatformPortal.h"
#include "Menu.h"
#include "Map.h"
#include "Modes.h"
#include "UI.h"
#include <random>
#include <vector>
namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime, int* exitapp );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	//////////////////////////////////////////////
	/// <Classes>
	Surface* screen;
	Ball ball;
	Modes modes;
	UI ui;

	Map map;
	std::vector< Map > walls;

	static constexpr unsigned __int8 nMenuButtonsMax = 13;
	Menu MenuButtons[nMenuButtonsMax];

	static constexpr unsigned __int8 njumpMax = 7;
	PlatformJump PlatJ[njumpMax];

	static constexpr unsigned __int8 nspeedMax = 7;
	PlatformSpeed PlatS[nspeedMax];

	PlatformPortal1 PlatP1;
	PlatformPortal2 PlatP2;
	//////////////////////////////////////////////
	/// <Functions>
	void Cursor();
	void SwapPlatform();
	void Reset();
	void goToTitleScreen(const float deltaTime);
	void goToOptionScreen(const float deltaTime, int* exitapp);
	void goToPauseScreen(const float deltaTime, int* exitapp);
	void goToWinScreen(int* exitapp);
	void goToLoseScreen(int* exitapp);
	/////////////////////////////////////////////
	/// <Variables>
	bool QisPress = true;
	bool WisPress = false;
	bool EisPress = false;
	bool canplace = true;
	bool title_screen = true;
	bool option_menu = true;
	bool pause_menu = false;
	bool PlatAreSet = false;
	bool Portal1Placed = false;
	bool &win = ui.win;
	bool &lose = modes.lose;
	bool music = false;
	bool WallsAreInitialized = false;

	vec2 SaveBallVel;

	int mousex;
	int mousey;
	int WallPosition =	 1;
		int rocketX =	 900;
		int njump =		 0;
		int nspeed =	 0;
		int nportal =	 0;
	////////////////////////////////////////////




};

}; // namespace Tmpl8