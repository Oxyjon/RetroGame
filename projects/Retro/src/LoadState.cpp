#include "LoadState.h"
#include "raylib.h"
#include "Config.h"
#include "Application.h"
#include "GameStateManager.h"
LoadState::LoadState(Application* app) : m_app(app)
{

}
LoadState::~LoadState()
{

}

void LoadState::Load()
{

}
void LoadState::UnLoad()
{

}

void LoadState::Update(float dt)
{
	m_timer += dt;
	if (m_timer > 3.0f)
	{
		DrawText("Press ENTER to continue", ((float)config.game.screenWidth / 2) - 200, (float)config.game.screenHeight - 60,32 , WHITE);
		if (IsKeyPressed(KEY_ENTER))
		{
			m_app->GetGameStateManager()->PopState();
			m_app->GetGameStateManager()->PushState("Play");
		}

	}
}
void LoadState::Draw()
{
	DrawText("Controls", ((float)config.game.screenWidth / 2) - 120, ((float)config.game.screenHeight / 2) - 150, 54, WHITE);
	//Movement
	DrawText("Movement", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) - 50, 18, WHITE);
	DrawText("W: Move Forward", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) - 30, 18, WHITE);
	DrawText("A: Move Left", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) - 10, 18, WHITE);
	DrawText("S: Move Down", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) + 10, 18, WHITE);
	DrawText("D: Move Right", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) + 30, 18, WHITE);
	//Shield
	DrawText("Shield", ((float)config.game.screenWidth / 2) + 90, ((float)config.game.screenHeight / 2) - 50, 18, WHITE);
	DrawText("Arrow UP: Shield Top", ((float)config.game.screenWidth / 2) + 90, ((float)config.game.screenHeight / 2) - 30, 18, WHITE);
	DrawText("Arrow LEFT: Shield Left", ((float)config.game.screenWidth / 2) + 90, ((float)config.game.screenHeight / 2) - 10, 18, WHITE);
	DrawText("Arrow DOWN: Shield Down", ((float)config.game.screenWidth / 2) + 90, ((float)config.game.screenHeight / 2) + 10, 18, WHITE);
	DrawText("Arrow RIGHT: Shield Right", ((float)config.game.screenWidth / 2) + 90, ((float)config.game.screenHeight / 2) + 30, 18, WHITE);

}
