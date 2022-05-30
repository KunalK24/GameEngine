#include "Game.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "GameGlobals.hpp"
#include "Engine/Core/Engine.hpp"
#include "Engine/Core/InputManager.hpp"

#include <iostream>
#include <string>

const float maxSpeed = 500.0f;
const float speedConstant = 100.0f;
const float rotationConstant = 150.0f;
const double shootingCooldown = 1.0;

//-------------------------------------------------------------------------------------------------
Player::Player()
	: GameObject()
{
}

//-------------------------------------------------------------------------------------------------
Player::Player(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, std::vector<Vector2f> shipOutline)
	: m_shipOutline(shipOutline)
	, m_bulletShotTime(0.0)
	, GameObject(position, rotation, velocity, acceleration, shipOutline[0].x, player)
{
}

//-------------------------------------------------------------------------------------------------
void Player::Update()
{
	InputManager* input = g_engine->GetInputManager();
	Vector2f shipDirection(cos(DegreesToRadians(m_rotation)), sin(DegreesToRadians(m_rotation)));
	if (input->IsKeyDown(W_KEY))
	{
		m_acceleration = shipDirection * speedConstant;
	}
	else if (input->IsKeyDown(S_KEY))
	{
		m_acceleration = shipDirection * -speedConstant;
	}
	else
	{
		m_acceleration = 0.0f;
	}
	if (input->IsKeyDown(A_KEY))
	{
		m_rotation += rotationConstant * g_engine->m_deltaTime;
	}
	if (input->IsKeyDown(D_KEY))
	{
		m_rotation -= rotationConstant * g_engine->m_deltaTime;
	}
 	if (input->IsKeyDownThisFrame(SPACE_KEY))
	{
		m_bulletShotTime = GetCurrentTimeSeconds();
		Vector2f front(m_position.x, m_position.y);
		Bullet* newBullet = (Bullet*)g_game->Spawn(bullet, front);
		newBullet->m_velocity = m_velocity + m_velocity.normal() * 10.0f;
		newBullet->m_acceleration = shipDirection * speedConstant;
	}
	if (m_velocity.magnitude() > maxSpeed)
	{
		m_acceleration = 0;
		m_velocity = m_velocity.normal() * maxSpeed;
	}
	OutOfBonds();
	GameObject::Update();
}

//-------------------------------------------------------------------------------------------------
void Player::Render() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->RenderShape(m_shipOutline, m_position, m_rotation);

	GameObject::Render();
}

//-------------------------------------------------------------------------------------------------
void Player::OutOfBonds()
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

//-------------------------------------------------------------------------------------------------
void Player::OnCollision(GameObject* obj)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(obj);
	if (asteroid != nullptr)
	{
		asteroid->m_markedForDeletion = true;
		m_markedForDeletion = true;
	}
}



