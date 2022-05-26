#include "PlayState.h"
#include "raylib.h"
#include <iostream>

#include "Application.h"
#include "GameStateManager.h"
#include "Config.h"
#include "Assets.h"

#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Button.h"


//TODO:
//Correct Player and Brick Collision

PlayState::PlayState(Application* app) : m_app(app)
{

}
PlayState::~PlayState()
{

}

void PlayState::Load()
{
	//Load initial objects in game
	//Player
	player.SetPos(config.game.playerStartingPosition);

	//Ball
	ball.SetPos({ 300,250 });
	ball.SetDir({ 0.707f, 0.707f });
	//Brick
	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			float xPos = i * 30;
			float yPos = j * 10;
			if (xPos > 240 && xPos < 540 && yPos > 140 && yPos < 320)
			{
				bricks[i][j] = new Brick({ xPos, yPos });
				bricks[i][j]->isAlive = false;
			}
			else {
				bricks[i][j] = new Brick({ xPos, yPos });
				bricks[i][j]->isAlive = true;
			}

		}
	}
	//Buttons
	
	Button yesButton = Button({ ((float)config.game.screenWidth / 2) - 10, (float)config.game.screenHeight / 2 + 35 }, 25, (char*)"Yes");
	buttons.push_back(yesButton);
	Button noButton = Button({ ((float)config.game.screenWidth / 2) - 10, ((float)config.game.screenHeight / 2) + 65 }, 25, (char*)"No");
	buttons.push_back(noButton);
	//Shield config
	shield.width = 60;
	shield.height = 60;

}

void PlayState::UnLoad()
{
	std::cout << "UNLOADING" << std::endl;
	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			if (bricks[i][j] != nullptr) delete bricks[i][j];
		}
	}	
}

void PlayState::Update(float dt)
{
	if (IsKeyPressed(KEY_Q))
	{
		ReturnToMenu();
		ResetGame();
	}

	if (IsKeyPressed(KEY_E))
	{
		config.game.isGameOver = false;
	}

	//GamePlayLoop
	if (!config.game.isGameOver)
	{
		//Game Updates and collisions	
		player.Update(dt);
		UpdateShield();
		HandleBallWallCollision();
		HandleBallBrickCollision();
		ball.Update(dt);
		HandleBallPlayerCollision();
		HandleBallShieldCollision();
		HandleBrickPlayerCollision();
		HandlePlayerWallCollision();
		//Check Win
		if (CheckWin())
		{			
			config.game.isGameOver = true;
		}
	}
	else
	{
		UpdateButtonSelect();
	}
}

void PlayState::Draw()
{
	//Drawing Game
	if (!config.game.isGameOver)
	{
		DrawText(FormatText("Deaths:  %i", deathCounter), config.game.screenWidth / 2 - 72, config.game.screenHeight / 2, 24, RAYWHITE);
		for (int i = 0; i < config.game.NUM_ROWS; i++)
		{
			for (int j = 0; j < config.game.NUM_COLS; j++)
			{
				if (bricks[i][j]->isAlive)
				{
					bricks[i][j]->Draw();
				}
			}
		}
		player.Draw();
		ball.Draw();
		DrawShield();
	}
	else
	{
		if (CheckWin()) DrawText("You Win!", ((float)config.game.screenWidth / 2) - 175, ((float)config.game.screenHeight / 2) - 150, 72, WHITE);
		else  DrawText("Game Over!", ((float)config.game.screenWidth / 2) - 175, ((float)config.game.screenHeight / 2) - 150, 72, WHITE);
		 
		DrawText("Play Again?", ((float)config.game.screenWidth / 2) - 100, ((float)config.game.screenHeight / 2) - 60, 48, WHITE);
		//Draw Buttons
		for (int i = 0; i < NUM_OF_BUTTONS; i++)
		{
			if (i == btnIndex)
			{
				DrawRectangle(buttons[i].pos.x - 20, buttons[i].pos.y + 5, 10, 10, WHITE);
			}
			buttons[i].Draw();
		}
	}

}

void PlayState::HandleBallWallCollision()
{
	//Ball to Wall Collision
	Vector2 ballPos = ball.m_pos;
	Vector2 ballDir = ball.GetDir();

	//Left
	if (ballPos.x < 0) ball.SetDir({ -ballDir.x, ballDir.y });
	//Right
	if (ballPos.x > config.game.screenWidth) ball.SetDir({ -ballDir.x, ballDir.y });
	//Top
	if (ballPos.y < 0)  ball.SetDir({ ballDir.x, -ballDir.y });
	//Bottom
	if (ballPos.y > config.game.screenHeight) ball.SetDir({ ballDir.x, -ballDir.y });
}

void PlayState::HandlePlayerWallCollision()
{
	//Player To Wall Collision
	Vector2 playerPos = player.m_pos;
	//Left Wall
	if (playerPos.x < 0) player.SetPos({ 0, playerPos.y });
	//Right Wall
	if (playerPos.x > config.game.screenWidth - player.size.x) player.SetPos({ config.game.screenWidth - player.size.x, playerPos.y });
	//Top Wall
	if (playerPos.y < 0) player.SetPos({ playerPos.x, 0 });
	//Bottom Wall
	if (playerPos.y > config.game.screenHeight - player.size.y) player.SetPos({ playerPos.x, config.game.screenHeight - player.size.y });
}

void PlayState::HandleBallBrickCollision()
{
	//Ball to Brick Collision
	Vector2 ballPos = ball.m_pos;
	Vector2 ballDir = ball.GetDir();

	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			if (bricks[i][j]->isAlive)
			{
				//Edges of the brick
				Vector2 brickPos = bricks[i][j]->m_pos;
				Vector2 brickSize = bricks[i][j]->GetSize();

				float xPos = brickPos.x;
				float yPos = brickPos.y;
				float xPos2 = xPos + brickSize.x;
				float yPos2 = yPos + brickSize.y;
				
				//Edges of the ball
				float ballX = ballPos.x;
				float ballY = ballPos.y;
				float ballX2 = ballX + ball.radius;
				float ballY2 = ballY + ball.radius;
				
				//Ball to Brick Collision
				if (ballX > xPos && ballX < xPos2 && ballY > yPos && ballY < yPos2)
				{
					ball.SetDir({ -ballDir.x, ballDir.y });
					bricks[i][j]->isAlive = false;
				}

				if (ballX2 > xPos && ballX2 < xPos2 && ballY > yPos && ballY < yPos2)
				{
					ball.SetDir({ -ballDir.x, ballDir.y });
					bricks[i][j]->isAlive = false;
				}

				if (ballY > yPos && ballY < yPos2 && ballX > xPos && ballX < xPos2)
				{
					ball.SetDir({ ballDir.x, -ballDir.y });
					bricks[i][j]->isAlive = false;
				}

				if (ballY2 > yPos && ballY2 < yPos2 && ballX > xPos && ballX < xPos2)
				{
					ball.SetDir({ ballDir.x, -ballDir.y });
					bricks[i][j]->isAlive = false;
				}
			}
		}
	}
}

void PlayState::ReturnToMenu()
{
	m_app->GetGameStateManager()->PopState();
	m_app->GetGameStateManager()->PushState("Menu");
	deathCounter = 0;
}

void PlayState::UpdateButtonSelect()
{

	//Cycle Through Buttons
	if (IsKeyPressed(KEY_UP))
	{
		//If 0. stay at 0
		btnIndex--;
		if (btnIndex < 0)
		{
			btnIndex = 0;
		}

	}

	if (IsKeyPressed(KEY_DOWN))
	{
		btnIndex++;
		if (btnIndex >= NUM_OF_BUTTONS)
		{
			btnIndex = 0;
		}

	}

	if (IsKeyPressed(KEY_ENTER))
	{
		config.game.isGameOver = false;
		if (btnIndex == 0)
		{
			ResetGame();
		}
		else if (btnIndex == 1)
		{	
			ReturnToMenu();
			ResetGame();	
		}	
	}

}

void PlayState::ResetGame()
{

	//Reset Existing Game Objects
	player.SetPos(config.game.playerStartingPosition);
	ball.SetPos({ 300,250 });
	ball.SetDir({ 0.707f, 0.707f });

	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			float xPos = i * 30;
			float yPos = j * 10;
			if (xPos > 240 && xPos < 540 && yPos > 140 && yPos < 320)
			{
				bricks[i][j]->SetPos({ xPos, yPos });
				bricks[i][j]->isAlive = false;
			}
			else {
				bricks[i][j]->SetPos({ xPos, yPos });
				bricks[i][j]->isAlive = true;
			}

		}
	}

	shield.width = 60;
	shield.height = 60;

	config.game.isGameOver = false;

}

void PlayState::HandleBallPlayerCollision()
{
	//Ball to Player Collision
	Vector2 ballPos = ball.m_pos;
	Vector2 playerPos = player.m_pos;

	if (ballPos.x > playerPos.x && ballPos.x < playerPos.x + player.size.x && ballPos.y > playerPos.y && ballPos.y < playerPos.y + player.size.y)
	{
		config.game.isGameOver = true;
		deathCounter++;
	}

}

void PlayState::HandleBallShieldCollision()
{
	//Ball to Shield Collision
	Vector2 ballPos = ball.m_pos;
	Vector2 ballDir = ball.GetDir();

	//Top
	if (IsKeyPressed(KEY_UP))
	{
		if (ballPos.x > shield.x && ballPos.x < (shield.x + shield.width) && ballPos.y >(shield.y - shield.height - reflectDistance) && ballPos.y < shield.y)
		{
			ball.SetDir({ ballDir.x, -ballDir.y });
		}
	}
	//Right
	else if (IsKeyPressed(KEY_RIGHT))
	{
		if (ballPos.x > shield.x && ballPos.x < (shield.x + (shield.width * 2 )+ reflectDistance) && ballPos.y > shield.y && ballPos.y < (shield.y + shield.height))
		{
			ball.SetDir({ -ballDir.x, ballDir.y });
		}
	}
	//Down
	else if (IsKeyPressed(KEY_DOWN))
	{
		if (ballPos.x > shield.x && ballPos.x < (shield.x + shield.width) && ballPos.y > shield.y && ballPos.y < (shield.y + (shield.height * 2) + reflectDistance))
		{
			ball.SetDir({ ballDir.x, -ballDir.y });
		}

	}
	//Left
	else if (IsKeyPressed(KEY_LEFT))
	{
		if (ballPos.x > shield.x - shield.width - reflectDistance && ballPos.x < shield.x && ballPos.y > shield.y && ballPos.y < (shield.y + shield.height))
		{
			ball.SetDir({ -ballDir.x, ballDir.y });
		}
	}
	
}


void PlayState::HandleBrickPlayerCollision()
{
	//This needs to be corrected
	////////////////////////////////////////////////////////////////////////
	//Brick to Player Collision
	Vector2 playerPos = player.m_pos;

	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			Vector2 brickPos = bricks[i][j]->m_pos;
			Vector2 brickSize = bricks[i][j]->GetSize();

			if(bricks[i][j]->isAlive)
			{
				if (playerPos.x > brickPos.x && playerPos.x < brickPos.x + brickSize.x && playerPos.y > brickPos.y && playerPos.y < brickPos.y + brickSize.y)
				{
					config.game.isGameOver = true;
					deathCounter++;
				}
			}
		}
	}
}

void PlayState::UpdateShield()
{
	//Update shield collision
	shield.x = player.m_pos.x - player.size.x;
	shield.y = player.m_pos.y - player.size.y;
}

void PlayState::DrawShield()
{
	if (IsKeyPressed(KEY_UP))
	{
		DrawTexture(Assets::shieldHorizImg, shield.x, shield.y, WHITE);
	}
	//Right
	else if (IsKeyPressed(KEY_RIGHT))
	{
		DrawTexture(Assets::shieldVertImg, shield.x + shield.width, shield.y, WHITE);
	}
	//Down
	else if (IsKeyPressed(KEY_DOWN))
	{
		DrawTexture(Assets::shieldHorizImg, shield.x, shield.y + shield.height, WHITE);
	}
	//Left
	else if (IsKeyPressed(KEY_LEFT))
	{
		DrawTexture(Assets::shieldVertImg, shield.x, shield.y, WHITE);
	}
}

bool PlayState::CheckWin()
{
	for (int i = 0; i < config.game.NUM_ROWS; i++)
	{
		for (int j = 0; j < config.game.NUM_COLS; j++)
		{
			if (bricks[i][j]->isAlive)
			{
				return false;
			}
		}
	}
	return true;
}

