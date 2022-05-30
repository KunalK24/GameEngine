#pragma once

#include "Asteroid.hpp"
#include "GameGlobals.hpp"
#include "Engine/Core/Utilities.h"
#include "Engine/Core/GameObject.hpp"

class Spawner
{
public:
	Spawner();
	
	void Update();
	void Render() const;

	void SpawnAsteroid();
};