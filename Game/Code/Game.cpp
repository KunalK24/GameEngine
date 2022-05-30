#include "Game.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "GameGlobals.hpp"
#include "Engine/Core/EngineGlobals.hpp"
#include "Engine/Core/GameObject.hpp"

#include <iostream>
#include <random>

Game* g_game = nullptr;


Game* Game::getSingleton()
{
	if (!g_game)
	{
		g_game = new Game();
	}
	return g_game;
}

void Game::Update()
{
	SpawnManager();
	ClearObjects();
	UpdateObjects();
	CheckCollisions();
	DeleteObjects();
}

void Game::Render() const
{
	for (GameObject* obj : m_objects)
	{
		obj->Render();
	}
}

GameObject* Game::Spawn(GameObjectTypes objectType, const Vector2f& position)
{
	GameObject* newObject = nullptr;
	switch (objectType)
	{
	case player:
		newObject = new Player(position, 0.0f, Vector2f(0.0f, 0.0f), 0.0f, GameModels::shipOutline);
		break;
	case asteroid:
		newObject = new Asteroid(position, 0.0f, Vector2f(0.0f, 0.0f), 0.0f, GameModels::asteroidOutline, large);
		break;
	case smallAsteroid:
		newObject = new Asteroid(position, 0.0f, Vector2f(0.0f, 0.0f), 0.0f, GameModels::smallAsteroidOutline, small);
		break;
	case bullet:
		newObject = new Bullet(position, 0.0f, Vector2f(0.0f, 0.0f), 0.0f, GameModels::bulletOutline);
		break;
	}
	m_pendingObjects.push_back(newObject);
	return newObject;
}

void Game::SpawnManager()
{
	Vector2f spawnPoint = GenerateRandomPoint();
	
	if (spawnPoint.x != 0.0f)
	{
		GameObject* newObject = new Asteroid(spawnPoint, 0.0f, Vector2f(0.0f, 0.0f), 10.0f, GameModels::asteroidOutline, large);
		m_pendingObjects.push_back(newObject);
	}
}

void Game::ClearObjects()
{
	for (GameObject* obj : m_pendingObjects)
	{
		m_objects.push_back(obj);
	}
	m_pendingObjects.clear();
}

void Game::UpdateObjects()
{
	//Update Objects
	for (GameObject* obj : m_objects)
	{
		obj->Update();
	}
}

void Game::CheckCollisions()
{
	//Check Collisions
	for (GameObject* obj : m_objects)
	{
		for (GameObject* other : m_objects)
		{
			if (obj != other)
			{
				if (obj->CheckCollision(other))
				{
					obj->OnCollision(other);
					other->OnCollision(obj);
				}
			}
		}
	}
}

void Game::DeleteObjects()
{
	for (auto obj_iter = m_objects.begin(); obj_iter != m_objects.end();)
	{
		GameObject* obj = *obj_iter;
		if (obj->m_markedForDeletion)
		{
			obj_iter = m_objects.erase(obj_iter);
		}
		else
		{
			++obj_iter;
		}
	}
}

Vector2f Game::GenerateRandomPoint()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> distX(-1649, 1649);
	std::uniform_real_distribution<float> distY(-949, 949);

	float randX = distX(rng);
	float randY = distY(rng);

	if ((randX > 1600 || randX < -1600) || (randY > 900 || randY < -900))
	{
		return Vector2f(randX, randY);
	}
	
	return Vector2f();
}


Game::Game()
{
	Spawn(player, Vector2f(0.0f, 0.0f));
}
