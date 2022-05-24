#pragma once
#include "raylib.h"

class Button
{
public:
	Button(Vector2 pos, int fontSize, char* text);
	virtual ~Button();
	void Draw();
	void Update(float deltaTime);

	Vector2 pos;
	int fontSize;
	char* text;
protected:

private:
	

};