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

void GameStateManager::SetState(const char* name, IGameState* state) 
{
	m_commands.push_back([=]() {
		if(m_states[name] != nullptr)
		{
			m_states[name]->UnLoad();
			delete m_states[name];
		}

		m_states[name] = state;

		if (m_states[name] != nullptr)
		{
			m_states[name]->Load();
			
		}
	});
}
void GameStateManager::PushState(const char* name) 
{
	m_commands.push_back([=]() {
		m_stack.push_back(m_states[name]);
		});
}
void GameStateManager::PopState() 
{
	m_commands.push_back([=]() {
		m_stack.pop_back();
		});
}