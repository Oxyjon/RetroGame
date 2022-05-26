#pragma once

#include <string>
#include <map>
#include <list>
#include <functional>

class IGameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(float deltaTime);
	void Draw();

	void SetState(std::string name, IGameState* state);
	void PushState(std::string name);
	void PopState();
protected:

	std::map<std::string, IGameState*> m_states;
	std::list<IGameState*> m_stack;
	std::list<std::function<void()>> m_commands;

private:
};
