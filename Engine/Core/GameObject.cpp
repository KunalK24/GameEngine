#include "GameObject.hpp"
#include "Engine/Core/Engine.hpp"

GameObject::GameObject()
	: m_position(Vector2f(0.0f, 0.0f))
	, m_rotation(0.0f)
	, m_velocity(Vector2f(0.0f, 0.0f))
	, m_acceleration(Vector2f(0.0f, 0.0f))
	, m_radius(0.0f)
{
}

GameObject::GameObject(const Vector2f& transform, float rotation, const Vector2f& velocity, float acceleration, const float radius, GameObjectTypes type)
	: m_position(transform)
	, m_rotation(rotation)
	, m_velocity(velocity)
	, m_acceleration(acceleration)
	, m_radius(radius)
	, m_markedForDeletion(false)
	, m_type(type)
{
}

void GameObject::Update()
{
	m_velocity += m_acceleration * g_engine->m_deltaTime;
	m_position += m_velocity * g_engine->m_deltaTime;
}

void GameObject::Render() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->RenderPoint(m_position, m_rotation);
}

bool GameObject::CheckCollision(GameObject* obj)
{
	float sumOfRadius = this->m_radius + obj->m_radius;
	return  DistanceFormula(this->m_position, obj->m_position) < sumOfRadius;
}



