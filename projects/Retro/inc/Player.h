#pragma once

#include "IGameObject.h"

class Player : public IGameObject
{
public:
	Player(Vector2 pos);
	virtual ~Player();
	virtual void Draw();
	virtual void Update(float deltaTime);

	Vector2 size = { 20, 20 };

	float speed = 5.0f;
protected:
private:
};