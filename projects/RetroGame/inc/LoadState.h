#pragma once

#include "IGameState.h"

class Application;

class LoadState : public IGameState
{
public:
	LoadState(Application* app);
	virtual ~LoadState();

	virtual void Load();
	virtual void UnLoad();

	virtual void Update(float dt);
	virtual void Draw();
protected:
private:
	float m_timer = 0.0f;
	Application* m_app;
};
