#include "Button.h"
#include <iostream>

Button::Button(Vector2 m_pos, int fontSize, char* m_text)
{
    this->pos = m_pos;
    this->fontSize = fontSize;
    this->text = m_text;
}

Button::~Button()
{
    
}


void Button::Update(float deltaTime)
{

}
void Button::Draw()
{
    DrawText(text, pos.x, pos.y, fontSize, RAYWHITE);
}
