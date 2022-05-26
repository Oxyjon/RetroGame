#include "Player.h"
#include "Assets.h"
#include <iostream>

Player::Player(Vector2 pos)
{
    SetPos(pos);  
}

Player::~Player()
{
    std::cout << "Player unload" << std::endl;
}


void Player::Update(float deltaTime)
{
    if (IsKeyDown(KEY_W))
    {
        m_pos.y -= speed;
    }
    if (IsKeyDown(KEY_D))
    {
        m_pos.x += speed;
    }
    if (IsKeyDown(KEY_S))
    {
        m_pos.y += speed;
    }
    if (IsKeyDown(KEY_A))
    {
        m_pos.x -= speed;
    }
}
void Player::Draw()
{
    DrawTexture(Assets::playerImg, m_pos.x, m_pos.y, WHITE);
    //DrawRectangle(m_pos.x, m_pos.y, size.x, size.y, WHITE);
}