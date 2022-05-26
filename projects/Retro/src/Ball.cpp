#include "Ball.h"
#include "Assets.h"
#include <iostream>

Ball::Ball(Vector2 pos, Vector2 dir)
{
    SetPos(pos);
    SetDir(dir);
}

Ball::Ball()
{

}

Ball::~Ball()
{

}


void Ball::Update(float deltaTime)
{
    m_pos.x += dir.x * speed;
    m_pos.y += dir.y * speed;
}
void Ball::Draw()
{
    DrawTexture(Assets::ballImg, m_pos.x, m_pos.y, WHITE);
    //DrawCircle(m_pos.x, m_pos.y, radius, WHITE);
}
