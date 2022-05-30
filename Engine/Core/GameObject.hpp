#pragma once

#include "Utilities.h"
#include "Engine/Core/RenderManager.hpp"

enum GameObjectTypes : int;

class GameObject
{
public:
	Vector2f m_position;
	float m_rotation;

	Vector2f m_velocity;

	Vector2f m_acceleration;

	float m_radius;

	bool m_markedForDeletion;

	GameObjectTypes m_type;

	GameObject();
	GameObject(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, const float radius, GameObjectTypes type);

	virtual void Update();
	virtual void Render() const;

	bool CheckCollision(GameObject* obj);

	virtual void OnCollision(GameObject* obj) = 0;
};