#pragma once

#include "IGameState.h"
#include <vector>
class Application;
class Button;
class MenuState : public IGameState
{
public:
	MenuState(Application* app);
	virtual ~MenuState();

	virtual void Load();
	virtual void UnLoad();

	virtual void Update(float dt);
	virtual void Draw();

	void UpdateButtonSelect();
protected:
private:

	Application* m_app;
	std::vector<Button> buttons;
	const int NUM_OF_BUTTONS = 2;
	int btnIndex = 0;
	
};
