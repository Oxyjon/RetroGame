#include "Assets.h"

Texture2D Assets::brickImg;
Texture2D Assets::playerImg;
Texture2D Assets::ballImg;
Texture2D Assets::shieldVertImg;
Texture2D Assets::shieldHorizImg;
Texture2D Assets::backgroundImg;

void Assets::LoadAssets()
{
	brickImg = LoadTexture("./assets/BrownBrick2.png");
	playerImg = LoadTexture("./assets/Player.png");
	ballImg = LoadTexture("./assets/Ball.png");
	shieldVertImg = LoadTexture("./assets/ShieldVert.png");
	shieldHorizImg = LoadTexture("./assets/ShieldHoriz.png");
	backgroundImg = LoadTexture("./assets/Background.png");
}

void Assets::UnloadAssets()
{
	UnloadTexture(brickImg);
	UnloadTexture(playerImg);
	UnloadTexture(ballImg);
	UnloadTexture(shieldVertImg);
	UnloadTexture(shieldHorizImg);
	UnloadTexture(backgroundImg);
}