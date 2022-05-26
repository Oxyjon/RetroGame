#pragma once

#include "IGameState.h"
#include "Config.h"
#include "vector"
#include "Player.h"
#include "Ball.h"

class Application;
class Button;
class Player;
class Ball;
class Brick;


class PlayState : public IGameState
{
public:

public:
	PlayState(Application* app);
	virtual ~PlayState();

	virtual void Load();
	virtual void UnLoad();

	virtual void Update(float dt);
	virtual void Draw();

	void ResetGame();
	void ReturnToMenu();
	void UpdateButtonSelect();

	void DrawShield();


	void UpdateShield();


	void HandleBallWallCollision();
	void HandlePlayerWallCollision();
	void HandleBallBrickCollision();
	void HandleBallPlayerCollision();
	void HandleBrickPlayerCollision();
	void HandleBallShieldCollision();

	bool CheckWin();

protected:
private:

	Application* m_app;
	Player player;
	Ball ball;
	Brick* bricks[Config::Game::NUM_ROWS][Config::Game::NUM_COLS];
	Rectangle shield;

	float reflectDistance = 7.0f;

	std::vector<Button> buttons;
	const int NUM_OF_BUTTONS = 2;
	int btnIndex = 0;

	int deathCounter = 0;

};
