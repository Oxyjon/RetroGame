#include "SplashState.h"
#include "raylib.h"
#include "Config.h"
#include "Application.h"
#include "GameStateManager.h"
SplashState::SplashState(Application* app) : m_app(app)
{

}
SplashState::~SplashState()
{

}

void SplashState::Load()
{

}
void SplashState::UnLoad()
{

}

void SplashState::Update(float dt)
{	
	m_timer += dt;
	if (m_timer > 3.0f)
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");

	}
}
void SplashState::Draw()
{
	DrawText("BrickBreakr", ((float)config.game.screenWidth / 2) - 200, ((float)config.game.screenHeight / 2) - 90, 72, WHITE);
}
