#include "GameStateManager.h"
#include "IGameState.h"

GameStateManager::GameStateManager() 
{

}
GameStateManager::~GameStateManager() 
{
	for (auto iter = m_states.begin(); iter != m_states.end(); iter++) 
	{
		if (iter->second != nullptr)
		{
			iter->second->UnLoad();
			delete iter->second;
		}
	}

	m_states.clear();
}

void GameStateManager::Update(float deltaTime) 
{
	//Invoke all Recorded Commands
	for (auto cmd : m_commands)
	{
		cmd();
	}
	m_commands.clear();
	for (auto state : m_stack)
	{
		state->Update(deltaTime);
	}
}
void GameStateManager::Draw() 
{
	for (auto state : m_stack)
	{
		state->Draw();
	}
}

void GameStateManager::SetState(std::string name, IGameState* state) 
{
	m_commands.push_back([=]() {


		if(m_states.find(name) != m_states.end() && m_states[name] != nullptr)
		{
			m_states[name]->UnLoad();
			delete m_states[name];
		}

		m_states[name] = state;

		if (m_states.find(name) != m_states.end() && m_states[name] != nullptr)
		{
			m_states[name]->Load();
			
		}
	});
}
void GameStateManager::PushState(std::string name) 
{
	m_commands.push_back([=]() {
		auto stateIter = m_states.find(name);
		if (stateIter != m_states.end())
		{
			m_stack.push_back(stateIter->second);
		}
		
	});
}
void GameStateManager::PopState() 
{
	m_commands.push_back([=]() {
		m_stack.pop_back();
	});
}