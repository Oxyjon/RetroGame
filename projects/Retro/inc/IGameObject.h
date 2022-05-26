#pragma once

#include "raylib.h"
class IGameObject
{
public:
	IGameObject() {};
	virtual ~IGameObject() {};

	void Load() {};
	void UnLoad() {};

	void Update(float dt){};
	void Draw(){};

	Vector2 m_pos;

	//Vector2 GetPos() { return m_pos; };
	void SetPos(Vector2 pos) { m_pos = pos; };
protected:
	//Vector2 m_pos;
private:
	
};