#pragma once
#include "GameGlobals.hpp"
#include "Engine/Core/Utilities.h"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Core/RenderManager.hpp"
class Asteroid : public GameObject
{
public:
	std::vector<Vector2f> m_asteroidOutline;
	AsteroidType m_asteroidType;

	Asteroid();
	Asteroid(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, const std::vector<Vector2f>& asteroidOutline, AsteroidType asteroidType);


	void Update();
	void Render() const;
	void OutOfBonds();
	void BreakApart();
	virtual void OnCollision(GameObject* obj);
};