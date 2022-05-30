#pragma once

#include <vector>
#include "Engine/Core/Utilities.h"

enum GameObjectTypes : int;

class GameObject;

class Game 
{
private:
public:
	std::vector<GameObject* > m_objects;
	std::vector<GameObject* > m_pendingObjects;

	Game();

	static Game* getSingleton();
	void Update();
	void Render() const;

	GameObject* Spawn(GameObjectTypes objectType, const Vector2f& position);
	void SpawnManager();
	void ClearObjects();
	void UpdateObjects();
	void CheckCollisions();
	void DeleteObjects();

	Vector2f GenerateRandomPoint();
};

extern Game* g_game;