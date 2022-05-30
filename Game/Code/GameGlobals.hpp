#pragma once

#include <vector>
#include "Engine/Core/Utilities.h"

class Engine;

extern Engine* g_engine;

extern float windowBoundaryHeight;

extern float windowBoundaryWidth;

namespace GameModels
{
	extern std::vector<Vector2f> shipOutline;
	extern std::vector<Vector2f> asteroidOutline;
	extern std::vector<Vector2f> smallAsteroidOutline;
	extern std::vector<Vector2f> bulletOutline;
};

namespace GameConstants
{
	extern float bulletMaxSpeed;
}

enum GameObjectTypes : int
{
	player,
	asteroid,
	smallAsteroid,
	bullet
};

enum AsteroidType : int
{
	large,
	small
};

