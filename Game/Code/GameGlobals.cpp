#include "GameGlobals.hpp"

float windowBoundaryHeight = 950.0f;

float windowBoundaryWidth = 1650.0f;

std::vector<Vector2f> GameModels::shipOutline = { Vector2f(50.0f, 0.0f) , Vector2f(-25.0f, 25.0f) , Vector2f(0.0f, 0.0f) , Vector2f(-25.0f, -25.0f) };
std::vector<Vector2f> GameModels::asteroidOutline = { Vector2f(20.0f, 0.0f), Vector2f(0.0f, 20.0f), Vector2f(-20.0f, 0.0f), Vector2f(0.0f, -20.0f) };
std::vector<Vector2f> GameModels::smallAsteroidOutline = { Vector2f(10.0f, 0.0f), Vector2f(0.0f, 10.0f), Vector2f(-10.0f, 0.0f), Vector2f(0.0f, -10.0f) };
std::vector<Vector2f> GameModels::bulletOutline = { Vector2f(10.0f, 0.0f), Vector2f(0.0f, 10.0f), Vector2f(-10.0f, 0.0f), Vector2f(0.0f, -10.0f) };

float bulletMaxSpeed = 100.0f;