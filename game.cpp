#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <SDL.h>
#include <SDL_render.h>
#include "template.h"
#include <Windows.h>

namespace Tmpl8
{



	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		int x[7] { 100, 100, 100, 500, 500, 500, 325 };
		int y[7] { 300, 350, 400, 300, 350, 400, 350 };
		int type[7] { 0, 1, 2, 3, 4, 5, 6 };
		for (const int n : type)                       //here we set the menu buttons
		{
				vec2 pos((float)x[n], (float)y[n]);
				MenuButtons[n].Init(pos, type[n]);
		}
			vec2 pos(50, 200);
			vec2 vel(0, 10);         //menu ball is set
			ball.Init(pos, vel);
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}




	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	
	void Game::Tick(float deltaTime, int* exitapp )
	{
		if (title_screen) //title screen
		{
			goToTitleScreen(deltaTime);
		}
		else if (option_menu) //option menu
		{
			goToOptionScreen(deltaTime, exitapp);
		}
		else if (pause_menu) //pause menu
		{
			goToPauseScreen(deltaTime, exitapp);
		}
		else if (win) //win menu
		{
			goToWinScreen(exitapp);
		}
		else if (lose) //game over menu
		{
			goToLoseScreen(exitapp);
		}
		else //The game starts
		{
			if (PlatAreSet == false) //Sets the platform out of bounds
			{
				for (int i = 0; i < njumpMax; i++)
				{
						PlatJ[i].Update(0, -100);
				}

				for (int i = 0; i < nspeedMax; i++)
				{
						PlatS[i].Update(0, -100);
				}

				PlatP1.Update(0, -100);
				PlatP2.Update(0, -100);
				PlatAreSet = true;
			}
			if (ball.initialized == false) //moves the ball to the start
			{
					vec2 pos(300, 250);
					vec2 vel(0, 10);
					ball.Init(pos, vel);
			}
			if (!WallsAreInitialized)
			{
					if (MenuButtons[5].clicked)
					{
							MenuButtons[11].nWallsInLevel = 300;
					}

					walls.reserve(MenuButtons[11].nWallsInLevel + 1);

					for (int i = 0; i <= MenuButtons[11].nWallsInLevel; i++)
					{
							walls.push_back(map);
					}

					WallsAreInitialized = true;
			}

			screen->Clear(0);
			ui.DrawBackground(screen, &MenuButtons[0]);
			

			if (!MenuButtons[2].clicked) //if floor is lava it is not pressed
			{
					for (int i = 0; i <= MenuButtons[11].nWallsInLevel; i++) //This spawns the walls
					{
							walls[i].Spawn(screen, &ball, WallPosition);
							WallPosition++;
					}
			}


			ui.StartWall(screen, &ball);
			if (!MenuButtons[5].clicked) //if endless mode is not pressed
			{
					ui.EndWall(screen, &ball, MenuButtons[11].EndGoal);
			}
			ui.setPos = true;

			modes.Enemies(screen, &ball, &MenuButtons[3], deltaTime);
			modes.TheFloorIsLava(&ball, &MenuButtons[2], &PlatJ[0]);
			modes.Chase(screen, &ball, &MenuButtons[4]);

			ball.BallBehaviour(deltaTime);
			ball.DrawBall(screen);
			ball.Trajectory(screen, deltaTime);

			SwapPlatform();

			Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);

			if (mousey < 70 + 10 && QisPress ||
				mousey > 442 - 10 && QisPress ||
				mousey < 70 + 10 && WisPress ||
				mousey > 442 - 10 && WisPress ||
				mousey < 70 + 10 && EisPress ||
				mousey > 442 - 25 && EisPress) //This checks if you can place platforms
			{
					canplace = false;
			}
			else
			{
					canplace = true;
			}

			if (GetAsyncKeyState(VK_LBUTTON) & 1 && GetAsyncKeyState(VK_LBUTTON) & 0x8000) //This places the platforms
			{
					if (QisPress && canplace)
					{
							if (njump == njumpMax - 1)
							{
									njump = 0;
							}
							else
							{
									njump++;
							}
							PlatJ[njump].Update(mousex, mousey);
					}

					if (WisPress && canplace)
					{
							if (nspeed == nspeedMax - 1)
							{
									nspeed = 0;
							}
							else
							{
									nspeed++;
							}
							PlatS[nspeed].Update(mousex, mousey);
					}

					if (EisPress && canplace)
					{
							if (Portal1Placed && !PlatP2.TestPortal1Collision(&PlatP1) && ui.start + 85 < mousex && modes.ChasingWallX + 96 < mousex)
							{
									PlatP2.Update(mousex, mousey);
									Portal1Placed = false;
							}
							else if (ui.start + 85 < mousex && modes.ChasingWallX + 96 < mousex)
							{
									PlatP1.Update(mousex, mousey);
									Portal1Placed = true;
									PlatP2.Update(-50, -50);
							}
					}
			}

			
			modes.DarkMode(screen, &ball, &MenuButtons[0]);
			modes.Rockets(screen, &ball, &MenuButtons[1], deltaTime);

			ui.DrawBase(screen, &ball, &MenuButtons[2]);
			

			for (int i = 0; i < njumpMax; i++) //This updates the jump platform
			{
					PlatJ[i].DrawPlatform(screen);
					PlatJ[i].TestCollision(&ball);
					PlatJ[i].UpdateX(&ball);
			}
			for (int i = 0; i < nspeedMax; i++) //This updates the speed platform
			{
					PlatS[i].DrawPlatform(screen);
					PlatS[i].TestCollision(&ball);
					PlatS[i].UpdateX(&ball);
			}
			PlatP2.DrawPlatform(screen);
			PlatP2.Teleport(&ball, &PlatP1);
			PlatP2.UpdateX(&ball);
			if (!(ball.pos.x == 300)) //This Teleports all of the surroundings
			{
					for (int i = 0; i <= MenuButtons[11].nWallsInLevel; i++)
					{
							walls[i].pos0.x -= (ball.pos.x - 300);
							walls[i].pos1.x -= (ball.pos.x - 300);
					}

					modes.RocketPos.x -= (ball.pos.x - 300);
					modes.ChasingWallX -= (ball.pos.x - 300);
					modes.EnemiesPos.x -= (ball.pos.x - 300);
					modes.BeachballPos[0].x -= (ball.pos.x - 300);
					modes.BeachballPos[1].x -= (ball.pos.x - 300);

					for (int i = 0; i < njumpMax; i++)
					{
							PlatJ[i].pos.x -= (ball.pos.x - 300);
					}

					for (int i = 0; i < nspeedMax; i++)
					{
							PlatS[i].pos.x -= (ball.pos.x - 300);
					}

					PlatP1.pos.x -= (ball.pos.x - 300);
					PlatP2.pos.x -= (ball.pos.x - 300);
					ui.BasePos += (ball.pos.x - 300);
					ui.start -= (ball.pos.x - 300);
					ui.end -= (ball.pos.x - 400);
			}
			PlatP1.DrawPlatform(screen);
			PlatP1.UpdateX(&ball);

			Cursor();

			if (GetAsyncKeyState(VK_ESCAPE) & 1 && GetAsyncKeyState(VK_ESCAPE) & 0x8000)//This pauses the game
			{
					pause_menu = true;
					SaveBallVel = ball.vel;
					ball.vel = 0;
			}
		}
	}

	void Game::Cursor()
	{
		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		if (QisPress)
		{
			Sprite JumpPlatform(new Surface("assets/UI/Platforms/JumpPlatform.png"), 1);
			JumpPlatform.Draw(screen, mousex - 31, mousey - 10);
		}
		else if (WisPress)
		{
			Sprite SpeedPlatform(new Surface("assets/UI/Platforms/SpeedPlatform.png"), 1);
			SpeedPlatform.Draw(screen, mousex - 31, mousey - 10);
		}
		else if (EisPress)
		{
			if (Portal1Placed)
			{
				Sprite PortalPlatform2(new Surface("assets/UI/Platforms/PortalPlatform2.png"), 1);
				PortalPlatform2.Draw(screen, mousex - 38, mousey - 38);
			}
			else
			{
				Sprite PortalPlatform1(new Surface("assets/UI/Platforms/PortalPlatform1.png"), 1);
				PortalPlatform1.Draw(screen, mousex - 38, mousey - 38);
			}
		}
		if (!canplace && EisPress)
		{
			Sprite CantPlacePortals(new Surface("assets/UI/CantPlacePortals.png"), 1);
			CantPlacePortals.Draw(screen, mousex - 38, mousey - 38);
		}
		if (!canplace && QisPress || !canplace && WisPress)
		{
			Sprite cantplace(new Surface("assets/UI/CantPlace.png"), 1);
			cantplace.Draw(screen, mousex - 21, mousey - 12);
		}
	}

	void Game::SwapPlatform()
	{
		if (GetAsyncKeyState('Q') & 1)
		{
			QisPress = true;
			WisPress = false;
			EisPress = false;
		}
		else if (GetAsyncKeyState('W') & 1)
		{
			WisPress = true;
			QisPress = false;
			EisPress = false;
		}
		else if (GetAsyncKeyState('E') & 1)
		{
			EisPress = true;
			WisPress = false;
			QisPress = false;
		}
	}

	void Game::Reset()
	{
		PlatAreSet = false;
		ball.meter = 0;
		ball.initialized = false;
		ui.setPos = false;
		modes.RocketTime = 0;
		modes.EnemiesPos.x = 750;
		modes.EnemiesPos.y = 150;
		modes.EnemiesTime = 0;
		modes.BeachballPos[0].x = 750;
		modes.BeachballPos[1].x = 750;
		modes.BeachballPos[1].y = 300;
		modes.InitLavaPlat = false;
		modes.ChasingWallX = 0;
		WallsAreInitialized = false;
		WallPosition = 1;
		walls.clear();
	}

	void Game::goToTitleScreen(const float deltaTime)
	{
		screen->Clear(0);

		ShowCursor(FALSE);

		Sprite background(new Surface("assets/UI/background.png"), 1);
		background.Draw(screen, 0, 0);

		ball.DrawBall(screen);
		ball.BallBehaviour(deltaTime);

		PlatJ[0].Update(60, 350);
		PlatJ[0].TestCollision(&ball);
		PlatJ[0].DrawPlatform(screen);

		ui.DrawBase(screen, &ball, &MenuButtons[2]);

		Sprite title(new Surface("assets/UI/Menu/title.png"), 1);
		title.Draw(screen, 200, 75);

		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite RocketMouse(new Surface("assets/UI/RocketMouse.png"), 1);
		RocketMouse.Draw(screen, mousex, mousey);

		if (GetKeyState(VK_SPACE))
		{
			title_screen = false;
		}
	}

	void Game::goToOptionScreen(const float deltaTime, int* exitapp)
	{
		screen->Clear(0);

		if (ball.initialized == false)
		{
				vec2 pos(50, 200);
				vec2 vel(0, 10);
				ball.Init(pos, vel);
		}

		ui.DrawBackground(screen, &MenuButtons[0]);

		if (MenuButtons[4].clicked) //chase button
		{
				Sprite ChasingWall(new Surface("assets/UI/ChasingWall.png"), 1);
				ChasingWall.Draw(screen, -58, 0);
		}

		if (MenuButtons[1].clicked) //rockets button
		{
				rocketX -= 10;
				Sprite rocket(new Surface("assets/UI/Rocket.png"), 1);
				rocket.Draw(screen, rocketX, 100);
				if (rocketX < -200)
				{
						rocketX = 1500;
				}
		}
		else
		{
				rocketX = 900;
		}

		if (MenuButtons[3].clicked) //enemies button
		{
				Sprite ball_bouncer(new Surface("assets/UI/follower.png"), 1);
				ball_bouncer.Draw(screen, (int)modes.EnemiesPos.x, (int)modes.EnemiesPos.y);

				Sprite Beachball0(new Surface("assets/UI/beachball.png"), 1);
				Beachball0.Draw(screen, (int)modes.BeachballPos[0].x, (int)modes.BeachballPos[0].y);

				Sprite Beachball1(new Surface("assets/UI/beachball.png"), 1);
				Beachball1.Draw(screen, (int)modes.BeachballPos[1].x, (int)modes.BeachballPos[1].y);

				modes.BeachballBehaviour(&ball, deltaTime);
		}
		else
		{
					modes.EnemiesPos.x =	 750;
					modes.EnemiesPos.y =	 150;
				modes.BeachballPos[0].x =	 750;
				modes.BeachballPos[1].x =	 750;
				modes.BeachballPos[1].y =	 300;
		}

		ball.DrawBall(screen);
		ball.BallBehaviour(deltaTime);

		PlatJ[0].Update(60, 350);
		PlatJ[0].TestCollision(&ball);
		PlatJ[0].DrawPlatform(screen);

		ui.DrawBase(screen, &ball, &MenuButtons[2]);

		for (int i = 0; i < 7; ++i)
		{
				MenuButtons[i].Button(screen);  //Draw buttons
		}

		vec2 musicPos(10, 468);
		MenuButtons[12].Init(musicPos, 12);
		MenuButtons[12].Button(screen);	 //music button
		if (MenuButtons[12].clicked && !music)	//if music button is on
		{
				PlaySound("assets//music.wav", NULL, SND_LOOP | SND_ASYNC);
				music = true;
		}
		else if (!MenuButtons[12].clicked && music)
		{
				PlaySound(NULL, NULL, 0);
				music = false;
		}

		vec2 goalsliderPos(100, 265);
		MenuButtons[11].Init(goalsliderPos, 11);
		MenuButtons[11].Button(screen);	 //goal slider
		if (MenuButtons[5].clicked) //endless button
		{
				Sprite GoalSliderBorderInfinity(new Surface("assets/UI/Menu/GoalSliderBorderInfinity-options.png"), 1);
				GoalSliderBorderInfinity.Draw(screen, (int)goalsliderPos.x + 145, (int)goalsliderPos.y - 31);
		}

		if (MenuButtons[6].TestClickBigButton()) //start button
		{
				option_menu = false;
				ball.initialized = false;
		}

		vec2 exitpos(325, 400);
		MenuButtons[9].initialized = false;
		MenuButtons[9].Init(exitpos, 9);
		MenuButtons[9].Button(screen);
		if (MenuButtons[9].TestClickBigButton()) //exit button
		{
				*exitapp = true;
		}

		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite RocketMouse(new Surface("assets/UI/RocketMouse.png"), 1);
		RocketMouse.Draw(screen, mousex, mousey);
	}

	void Game::goToPauseScreen(const float deltaTime, int* exitapp)
	{
		screen->Clear(0);
		//////////////////////////////////////////////////////////////////////////////////
		/// <Draw Background>
		ui.DrawBackground(screen, &MenuButtons[0]);

		for (int i = 0; i <= MenuButtons[11].nWallsInLevel; i++)
		{
				walls[i].DrawWall(screen);
		}

		ui.StartWall(screen, &ball);
		if (!MenuButtons[5].clicked)
		{
				ui.EndWall(screen, &ball, MenuButtons[11].EndGoal);
		}

		if (MenuButtons[3].clicked)
		{
				switch (modes.Etype)
				{
				case Modes::EnemyTypes::ball_bouncer:
				{
						Sprite ball_bouncer(new Surface("assets/UI/follower.png"), 1);
						ball_bouncer.Draw(screen, (int)modes.EnemiesPos.x, (int)modes.EnemiesPos.y);

						Sprite Beachball0(new Surface("assets/UI/beachball.png"), 1);
						Beachball0.Draw(screen, (int)modes.BeachballPos[0].x, (int)modes.BeachballPos[0].y);

						Sprite Beachball1(new Surface("assets/UI/beachball.png"), 1);
						Beachball1.Draw(screen, (int)modes.BeachballPos[1].x, (int)modes.BeachballPos[1].y); 
				}
				break;

				case Modes::EnemyTypes::follower:
				{
						Sprite follower(new Surface("assets/UI/follower.png"), 1);
						follower.Draw(screen, (int)modes.EnemiesPos.x, (int)modes.EnemiesPos.y); 
				}
				break;
				}
		}

		if (MenuButtons[1].clicked)
		{
				Sprite rocket(new Surface("assets/UI/Rocket.png"), 1);
				rocket.Draw(screen, (int)modes.RocketPos.x, (int)modes.RocketPos.y);
		}

		modes.TheFloorIsLava(&ball, &MenuButtons[2], &PlatJ[0]);

		if (MenuButtons[4].clicked)
		{
				Sprite ChasingWall(new Surface("assets/UI/ChasingWall.png"), 1);
				ChasingWall.Draw(screen, (int)modes.ChasingWallX, 0);
		}

		ball.DrawBall(screen);

		modes.DarkMode(screen, &ball, &MenuButtons[0]);

		ui.DrawBase(screen, &ball, &MenuButtons[2]);

		for (int i = 0; i < njumpMax; i++)
		{
				PlatJ[i].DrawPlatform(screen);
		}
		for (int i = 0; i < nspeedMax; i++)
		{
				PlatS[i].DrawPlatform(screen);
		}
		PlatP2.DrawPlatform(screen);
		PlatP1.DrawPlatform(screen);
		/////////////////////////////////////////////////////////////////////



		Sprite pausemenu(new Surface("assets/UI/Menu/pause-menu.png"), 1);
		pausemenu.Draw(screen, 0, 0);

		vec2 resumepos(10, 125);
		MenuButtons[10].Init(resumepos, 10);
		MenuButtons[10].Button(screen);
		if (MenuButtons[10].TestClickBigButton()) //resume button
		{
				pause_menu = false;
				ball.vel = SaveBallVel;
		}

		vec2 menupos(10, 225);
		MenuButtons[8].Init(menupos, 8);
		MenuButtons[8].Button(screen);
		if (MenuButtons[8].TestClickBigButton()) //menu button
		{
				option_menu = true;
				pause_menu = false;
				Reset();
		}

		vec2 exitpos(10, 325);
		MenuButtons[9].initialized = false;
		MenuButtons[9].Init(exitpos, 9);
		MenuButtons[9].Button(screen);
		if (MenuButtons[9].TestClickBigButton()) //exit button
		{
				*exitapp = true;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1 && GetAsyncKeyState(VK_ESCAPE) & 0x8000) //resume button
		{
				pause_menu = false;
				ball.vel = SaveBallVel;
		}

		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite RocketMouse(new Surface("assets/UI/RocketMouse.png"), 1);
		RocketMouse.Draw(screen, mousex, mousey);
	}

	void Game::goToWinScreen(int* exitapp)
	{
		screen->Clear(0);

		Sprite YouWin(new Surface("assets/UI/Menu/YouWin.png"), 1);
		YouWin.Draw(screen, 0, 0);

		vec2 retrypos(10, 125);
		MenuButtons[7].Init(retrypos, 7);
		MenuButtons[7].Button(screen);
		if (MenuButtons[7].TestClickBigButton()) //retry button
		{
				win = false;
				Reset();
		}

		vec2 menupos(10, 225);
		MenuButtons[8].Init(menupos, 8);
		MenuButtons[8].Button(screen);
		if (MenuButtons[8].TestClickBigButton()) //menu button
		{
				option_menu = true;
				win = false;
				Reset();
		}

		vec2 exitpos(10, 325);
		MenuButtons[9].initialized = false;
		MenuButtons[9].Init(exitpos, 9);
		MenuButtons[9].Button(screen);
		if (MenuButtons[9].TestClickBigButton()) //exit button
		{
				*exitapp = true;
		}

		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite RocketMouse(new Surface("assets/UI/RocketMouse.png"), 1);
		RocketMouse.Draw(screen, mousex, mousey);
	}

	void Game::goToLoseScreen(int* exitapp)
	{
		screen->Clear(0);

		Sprite GameOver(new Surface("assets/UI/Menu/GameOver.png"), 1);
		GameOver.Draw(screen, 0, 0);

		vec2 retrypos(10, 125);
		MenuButtons[7].Init(retrypos, 7);
		MenuButtons[7].Button(screen);
		if (MenuButtons[7].TestClickBigButton()) //retry button
		{
				lose = false;
				Reset();
		}

		vec2 menupos(10, 225);
		MenuButtons[8].Init(menupos, 8);
		MenuButtons[8].Button(screen);
		if (MenuButtons[8].TestClickBigButton()) //menu button
		{
				option_menu = true;
				lose = false;
				Reset();
		}

		vec2 exitpos(10, 325);
		MenuButtons[9].initialized = false;
		MenuButtons[9].Init(exitpos, 9);
		MenuButtons[9].Button(screen);
		if (MenuButtons[9].TestClickBigButton()) //exit button
		{
				*exitapp = true;
		}

		Uint32 mouse = SDL_GetMouseState(&mousex, &mousey);
		Sprite RocketMouse(new Surface("assets/UI/RocketMouse.png"), 1);
		RocketMouse.Draw(screen, mousex, mousey);
	}

}