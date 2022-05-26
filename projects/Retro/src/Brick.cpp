#include "Brick.h"
#include "Assets.h"
#include <iostream>

Brick::Brick()
{
    
}

Brick::Brick(Vector2 pos)
{
    SetPos(pos);
}

Brick::~Brick()
{

}


void Brick::Update(float deltaTime)
{

}
void Brick::Draw()
{
    DrawTexture(Assets::brickImg, m_pos.x, m_pos.y, WHITE);
}
