#pragma once

#include "Engine/Core/Utilities.h"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Core/RenderManager.hpp"

extern const float bulletMaxSpeed;
extern const double maxBulletLifeTime;

class Bullet : public GameObject
{
public:
	std::vector<Vector2f> m_bulletOutline;
	double m_bulletLifeTime;

	Bullet();
	Bullet(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, const std::vector<Vector2f>& bulletOutline);

	void Update();
	void Render() const;
	void OutOfBounds();

	virtual void OnCollision(GameObject* obj);
};