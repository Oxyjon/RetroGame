#pragma once
#include "raylib.h"

struct Config
{
	struct Game
	{
		int screenWidth = 810;
		int screenHeight = 450;
		const char* windowTitle = "BrickBreakr";

		static const int NUM_ROWS = 27;
		static const int NUM_COLS = 45;

		Vector2 playerStartingPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

		bool exitWindow = false;

		bool isGameOver = false;
	};

	Game game;

	struct Input
	{
		int upKey		= KEY_UP;
		int downKey		= KEY_DOWN;
		int leftKey		= KEY_LEFT;
		int rightKey	= KEY_RIGHT;
	};

	Input input;

};

extern Config config;