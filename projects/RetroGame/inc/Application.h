#pragma once
#include <string>


//Predeclate classes
//---------------------------------------------------
class GameStateManager;

class Application
{
public:
	Application();
	~Application();

	void Run();
	void Draw();
	void Update(float deltaTime);

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}
protected:
private:
	GameStateManager* m_gameStateManager = nullptr;
};