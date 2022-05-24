#include "PauseState.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
PauseState::PauseState(Application* app) : m_app(app)
{

}
PauseState::~PauseState()
{

}

void PauseState::Load()
{

}
void PauseState::UnLoad()
{

}

void PauseState::Update(float dt)
{
	if (IsKeyPressed(KEY_P))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Play");
	}
}
void PauseState::Draw()
{
	DrawText("Pause", 10, 10, 20, LIGHTGRAY);
}
