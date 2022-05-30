#include "InputManager.hpp"

InputManager* g_inputManager = nullptr;

InputManager::InputManager()
	: inputBuffer(1000, false)
	, currBuffer(1000, false)
{
}

void InputManager::Update()
{
	for (int current = 0; current < currBuffer.size(); ++current)
	{
		currBuffer[current] = false;
	}
}

InputManager* InputManager::getSingleton()
{
	if (!g_inputManager)
	{
		g_inputManager = new InputManager();
	}
	return g_inputManager;
}

bool InputManager::IsKeyUp(Keys key)
{
	return !inputBuffer[key];
}

bool InputManager::IsKeyDown(Keys key)
{
	return inputBuffer[key];
}

void InputManager::setKeyStateDown(int keyValue)
{
	if (!inputBuffer[keyValue])
	{
		inputBuffer[keyValue] = true;
		currBuffer[keyValue] = true;
	}
}

void InputManager::setKeyStateUp(int keyValue)
{
	if (inputBuffer[keyValue])
	{
		inputBuffer[keyValue] = false;
		currBuffer[keyValue] = true;
	}
}

bool InputManager::IsKeyDownThisFrame(Keys key)
{
	if (currBuffer[key]) 
	{
		return IsKeyDown(key);
	}
	return false;
}

bool InputManager::IsKeyUpThisFrame(Keys key)
{
	if (currBuffer[key])
	{
		return IsKeyUp(key);
	}
	return false;
}


