#pragma once
#pragma once

#include "IGameState.h"

class Application;

class PauseState : public IGameState
{
public:
	PauseState(Application* app);
	virtual ~PauseState();

	virtual void Load();
	virtual void UnLoad();

	virtual void Update(float dt);
	virtual void Draw();
protected:
private:

	Application* m_app;
};
