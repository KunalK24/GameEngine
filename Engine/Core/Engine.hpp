#pragma once

// Needed to setup a window
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class InputManager;
class RenderManager;

class Engine
{
public:
	InputManager* inputManager;
	RenderManager* renderManager;

	float m_gameDuration;
	float m_deltaTime;

	Engine();

	static Engine* getSingleton();

	void Startup(HINSTANCE applicationInstanceHandle);
	void Shutdown();

	void Update();
	void PreRender() const;
	void PostRender() const;

	InputManager* GetInputManager();
	RenderManager* GetRenderManager();
};

extern Engine* g_engine;