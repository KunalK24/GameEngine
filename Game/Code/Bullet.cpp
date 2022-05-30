#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "GameGlobals.hpp"
#include "Engine/Core/Utilities.h"
#include "Engine/Core/Engine.hpp"

const float bulletMaxSpeed = 500.0f;
const double maxBulletLifeTime = 100.0;

Bullet::Bullet()
	: GameObject()
{
}

Bullet::Bullet(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, const std::vector<Vector2f>& bulletOutline)
	: m_bulletOutline(bulletOutline)
	, m_bulletLifeTime(GetCurrentTimeSeconds())
	, GameObject(position, rotation, velocity, acceleration, bulletOutline[0].x, bullet)
{
}

void Bullet::Update()
{
	if (GetCurrentTimeSeconds() - m_bulletLifeTime > maxBulletLifeTime)
	{
		m_markedForDeletion = true;
	}
	if (m_velocity.magnitude() > bulletMaxSpeed)
	{
		m_acceleration = 0;
		m_velocity = m_velocity.normal() * bulletMaxSpeed;
	}
	OutOfBounds();
	GameObject::Update();
}

void Bullet::Render() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->RenderShape(m_bulletOutline, m_position, m_rotation);

	GameObject::Render();
}

void Bullet::OutOfBounds()
{
	//Fix this shit
	if (m_position.y > windowBoundaryHeight || m_position.y < -windowBoundaryHeight)
	{
		m_position.y = -m_position.y;
	}
	if (m_position.x > windowBoundaryWidth || m_position.x < -windowBoundaryWidth)
	{
		m_position.x = -m_position.x;
	}
}

void Bullet::OnCollision(GameObject* obj)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(obj);
	if (asteroid != nullptr)
	{
		asteroid->m_markedForDeletion = true;
		m_markedForDeletion = true;
		if (asteroid->m_asteroidType)
		{
			asteroid->BreakApart();
		}
	}
}
