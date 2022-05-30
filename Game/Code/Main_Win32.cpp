#include "Engine/Core/EngineGlobals.hpp"
#include "Engine/Core/Utilities.h"
#include "Engine/Core/RenderManager.hpp"
#include "Engine/Core/Engine.hpp"
#include "Game.hpp"
#include "GameGlobals.hpp"


//-------------------------------------------------------------------------------------------------
void RunFrame()
{
	Game* game = Game::getSingleton();
	Engine* engine = Engine::getSingleton();
	engine->Update();
	game->Update();
	engine->PreRender();
	game->Render();
	engine->PostRender();
}


//-------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE applicationInstanceHandle, HINSTANCE, LPSTR, int)
{
	Engine* engine = Engine::getSingleton();
	engine->Startup(applicationInstanceHandle);

	while (!g_isQuitting)
	{
		RunFrame();
	}

	engine->Shutdown();
	return 0;
}