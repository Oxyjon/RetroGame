#include "Application.h"
#include <iostream>
#include "raylib.h"
#include "GameStateManager.h"
#include "IGameState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "LoadState.h"
#include "Config.h"
#include "Assets.h"


#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

struct EmscriptenGameLoopFunc
{
    static void Execute() { app->GameLoop(); }
    static Application* app;
};
Application* EmscriptenGameLoopFunc::app = nullptr;

#endif


Application::Application()
{
    std::cout << "Constructor Online" << std::endl;
}

Application::~Application()
{
    std::cout << "Destructor Online" << std::endl;
}


void Application::Run()
{
    InitWindow(config.game.screenWidth, config.game.screenHeight, config.game.windowTitle);
    SetTargetFPS(60);

    Assets::LoadAssets();
    m_gameStateManager = new GameStateManager();
    m_gameStateManager->SetState("Splash", new SplashState(this));
    m_gameStateManager->SetState("Menu", new MenuState(this));
    m_gameStateManager->SetState("Loading", new LoadState(this));
    m_gameStateManager->SetState("Play", new PlayState(this));
    m_gameStateManager->PushState("Splash");



    // Main game loop

    while (!config.game.exitWindow)
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) config.game.exitWindow = true;
        
        float dt = GetFrameTime();
        Update(dt);
        Draw();
        
    }

    delete m_gameStateManager;

    Assets::UnloadAssets();
    CloseWindow();
}
void Application::Update(float deltaTime)
{
    //Update Logic Goes Here
    m_gameStateManager->Update(deltaTime);
}
void Application::Draw()
{
    //Draw Logic Goes Here
    BeginDrawing();

    ClearBackground(BLACK);
    //DrawTexture(Assets::backgroundImg, 0, 0, WHITE);
    m_gameStateManager->Draw();

    EndDrawing();
}

void Application::GameLoop(float deltaTime)
{
    //m_game->shouldQuit = m_game->shouldQuit || WindowShouldClose();

    Update(deltaTime);
    Draw();

}