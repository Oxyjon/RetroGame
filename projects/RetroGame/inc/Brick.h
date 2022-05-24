#pragma once

#include "IGameObject.h"
#include "raylib.h"
class Brick : public IGameObject
{
public:
	Brick();
	Brick(Vector2 pos);
	virtual ~Brick();
	virtual void Draw();
	virtual void Update(float deltaTime);

	bool isAlive;
	Vector2 GetSize() { return size; };
protected:
	Vector2 size = { 30, 10 };
private:
	
};