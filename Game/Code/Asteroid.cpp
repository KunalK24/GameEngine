#include "Game.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "Engine/Core/Engine.hpp"

//-------------------------------------------------------------------------------------------------
Asteroid::Asteroid()
	: GameObject()
{
}

//-------------------------------------------------------------------------------------------------
Asteroid::Asteroid(const Vector2f& position, float rotation, const Vector2f& velocity, float acceleration, const std::vector<Vector2f>& asteroidOutline, AsteroidType asteroidType)
	: GameObject(position, rotation, velocity, acceleration, asteroidOutline[0].x, asteroid)
	, m_asteroidOutline(asteroidOutline)
	, m_asteroidType(asteroidType)
{
}

//-------------------------------------------------------------------------------------------------
void Asteroid::Update()
{
	GameObject::Update();
}

//-------------------------------------------------------------------------------------------------
void Asteroid::Render() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->RenderShape(m_asteroidOutline, m_position, m_rotation);

	GameObject::Render();
}

//-------------------------------------------------------------------------------------------------
void Asteroid::OutOfBonds()
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
void Asteroid::BreakApart()
{
	Asteroid* smallAsteroidA = (Asteroid*)g_game->Spawn(smallAsteroid, Vector2f(m_position.x, m_position.y));
	smallAsteroidA->m_velocity = m_velocity * -1;

	Asteroid* smallAsteroidB = (Asteroid*)g_game->Spawn(smallAsteroid, Vector2f(m_position.x, m_position.y));
	smallAsteroidB->m_velocity = m_velocity;
}

//-------------------------------------------------------------------------------------------------
void Asteroid::OnCollision(GameObject* obj)
{
	Bullet* bullet = dynamic_cast<Bullet*>(obj);
	if (bullet != nullptr)
	{
		bullet->m_markedForDeletion = true;
		m_markedForDeletion = true;
		if (m_asteroidType == large)
		{
			BreakApart();
		}
	}
	Player* player = dynamic_cast<Player*>(obj);
	if (player != nullptr)
	{
		player->m_markedForDeletion = true;
		m_markedForDeletion = true;
	}
}
