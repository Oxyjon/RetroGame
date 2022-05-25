#include "Game.h"
#include "raylib.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Load()
{

}

void Game::UnLoad()
{

}

void Game::Update()
{

}

void Game::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first Pong Game!", 190, 200, 20, LIGHTGRAY);

	EndDrawing();
}

