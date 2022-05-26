#include "raylib.h"
#include <iostream>
#include "Application.h"
#include "GameStateManager.h"
#include "MenuState.h"
#include "Button.h"
#include "Config.h"
MenuState::MenuState(Application* app) : m_app(app)
{

}
MenuState::~MenuState()
{

}

void MenuState::Load()
{
	//Play Button
	Button playButton = Button({ ((float)config.game.screenWidth / 2) - 10, (float)config.game.screenHeight / 2 + 35  }, 25, (char*)"Play");
	buttons.push_back(playButton);
	Button exitButton = Button({ ((float)config.game.screenWidth / 2) - 10, ((float)config.game.screenHeight / 2 ) + 65}, 25, (char*)"Exit");
	buttons.push_back(exitButton);
	
}
void MenuState::UnLoad()
{
    
}

void MenuState::Update(float dt)
{
    UpdateButtonSelect();
}
void MenuState::Draw()
{
    //Game Title
    DrawText("BrickBreakr", ((float)config.game.screenWidth / 2) - 200 , ((float)config.game.screenHeight / 2) - 90, 72, WHITE);
    //Draw Buttons
	for (int i = 0; i < NUM_OF_BUTTONS; i++)
	{
		if (i == btnIndex)
		{
			DrawRectangle(buttons[i].pos.x - 20, buttons[i].pos.y + 5, 10, 10, WHITE);
		}
		buttons[i].Draw();
	}

    //Botyom Made By
	DrawText("c 2022 - Made By: John Pelkman", ((float)config.game.screenWidth / 2) - 150, (float)config.game.screenHeight - 50, 20, WHITE);
}

void MenuState::UpdateButtonSelect()
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
        //increment record
        btnIndex++;
        //if record exceeds max count go back to 0
        if (btnIndex >= NUM_OF_BUTTONS)
        {
            btnIndex = 0;
        }

    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (btnIndex == 0)
        {
            m_app->GetGameStateManager()->PopState();
            m_app->GetGameStateManager()->PushState("Loading");
        }
        else if (btnIndex == 1)
        {
            config.game.exitWindow = true;
        }
    }
	
}
