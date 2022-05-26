#pragma once
#include "raylib.h"

namespace Assets
{
	void LoadAssets();
	void UnloadAssets();

	extern Texture2D brickImg;
	extern Texture2D playerImg;
	extern Texture2D ballImg;
	extern Texture2D shieldVertImg;
	extern Texture2D shieldHorizImg;
	extern Texture2D backgroundImg;
}