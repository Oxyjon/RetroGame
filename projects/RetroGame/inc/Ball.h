#pragma once

#include "IGameObject.h"

class Ball : public IGameObject
{
public:
	Ball(Vector2 pos, Vector2 dir);
	virtual ~Ball();
	virtual void Draw();
	virtual void Update(float deltaTime);

	Vector2 GetDir() { return dir; };
	void SetDir(Vector2 dir) { this->dir = dir; };
	int radius = 5;
	float speed = 7.0f;
protected:
	Vector2 dir;
private:
	
	
};