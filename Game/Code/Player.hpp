#pragma once

#include "Engine/Core/Utilities.h"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Core/RenderManager.hpp"

#include <vector>

extern const float maxSpeed;
extern const float speedConstant;
extern const float rotationConstant;
extern const double shootingCooldown;

class Player : public GameObject
{
public:
	std::vector<Vector2f> m_shipOutline;
	double m_bulletShotTime;

	Player();
	Player(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, std::vector<Vector2f> shipOutline);
	void Update() override;
	void Render() const override;
	void OutOfBonds();
	virtual void OnCollision(GameObject* obj);
};

