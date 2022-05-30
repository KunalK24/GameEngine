#include "Engine.hpp"

#include <thread>
// Needed for OpenGL
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment( lib, "opengl32" )
#pragma comment( lib, "Glu32" )

#include "Utilities.h"
#include "EngineGlobals.hpp"
#include "RenderManager.hpp"
#include "InputManager.hpp"


Engine* g_engine = nullptr;
HGLRC openGLRenderingContext = nullptr;
HDC displayDeviceContext = nullptr;

//-------------------------------------------------------------------------------------------------
LRESULT CALLBACK WindowsMessageHandlingProcedure(HWND windowHandle, UINT wmMessageCode, WPARAM wParam, LPARAM lParam)
{
	InputManager* input = g_engine->inputManager;
	switch (wmMessageCode)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		g_isQuitting = true;
		break;

	case WM_KEYDOWN:
		if (wParam == ESC_KEY)
		{
			g_isQuitting = true;
			break;
		}
		input->setKeyStateDown((int)wParam);
		break;

	case WM_KEYUP:
		input->setKeyStateUp((int)wParam);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MBUTTONDOWN:
		break;

	case WM_MBUTTONUP:
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_RBUTTONUP:
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_CHAR:
		break;
	}

	return DefWindowProc(windowHandle, wmMessageCode, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
void RunMessagePump()
{
	MSG queuedMessage;
	for (;;)
	{
		const BOOL wasMessagePresent = PeekMessage(&queuedMessage, NULL, 0, 0, PM_REMOVE);
		if (!wasMessagePresent)
		{
			break;
		}

		TranslateMessage(&queuedMessage);
		DispatchMessage(&queuedMessage);
	}
}

//-------------------------------------------------------------------------------------------------
void Engine::Startup(HINSTANCE applicationInstanceHandle)
{
	// Give us correct pixels on screen
	SetProcessDPIAware();

	// Define a Window class
	WNDCLASSEX windowClassDescription;
	memset(&windowClassDescription, 0, sizeof(windowClassDescription));
	windowClassDescription.cbSize = sizeof(windowClassDescription);
	// Redraw on move, request own display context
	windowClassDescription.style = CS_OWNDC;
	// Assign a win32 message-handling function
	windowClassDescription.lpfnWndProc = static_cast<WNDPROC>(WindowsMessageHandlingProcedure);
	windowClassDescription.hInstance = GetModuleHandle(NULL);
	windowClassDescription.hIcon = NULL;
	windowClassDescription.hCursor = NULL;
	windowClassDescription.lpszClassName = TEXT("Simple Window Class");
	RegisterClassEx(&windowClassDescription);

	DWORD windowStyleFlags;
	DWORD windowStyleExFlags;

	// Set to windowed mode
	windowStyleFlags = WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_SYSMENU | WS_OVERLAPPED;
	windowStyleExFlags = WS_EX_APPWINDOW;

	RECT desktopRect;
	HWND desktopWindowHandle = GetDesktopWindow();
	GetClientRect(desktopWindowHandle, &desktopRect);

	// Window dimensions
	RECT windowRect =
	{
		50,
		50,
		50 + 1600,
		50 + 900
	};
	AdjustWindowRectEx(&windowRect, windowStyleFlags, FALSE, windowStyleExFlags);

	// Create Window
	WCHAR windowTitle[1024];
	MultiByteToWideChar(GetACP(), 0, "GameEngine", -1, windowTitle, sizeof(windowTitle) / sizeof(windowTitle[0]));
	HWND windowHandle = CreateWindowEx(
		windowStyleExFlags,
		windowClassDescription.lpszClassName,
		windowTitle,
		windowStyleFlags,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		applicationInstanceHandle,
		NULL);

	// Focus the Window
	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);

	// Setup Cursor
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(cursor);

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	memset(&pixelFormatDescriptor, 0, sizeof(pixelFormatDescriptor));
	pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 24;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cAccumBits = 0;
	pixelFormatDescriptor.cStencilBits = 8;

	// Setup OpenGL context
	displayDeviceContext = GetDC(windowHandle);
	int pixelFormatCode = ChoosePixelFormat(displayDeviceContext, &pixelFormatDescriptor);
	SetPixelFormat(displayDeviceContext, pixelFormatCode, &pixelFormatDescriptor);
	openGLRenderingContext = wglCreateContext(displayDeviceContext);
	wglMakeCurrent(displayDeviceContext, openGLRenderingContext);
}

//-------------------------------------------------------------------------------------------------
void Engine::Shutdown()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(openGLRenderingContext);
}

//-------------------------------------------------------------------------------------------------
void Engine::Update()
{
	float tempTime = (float)GetCurrentTimeSeconds();
	m_deltaTime = tempTime - m_gameDuration;
	m_gameDuration = tempTime;
	//Limiting FPS
	//std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(10));
	inputManager->Update();
	RunMessagePump();
}

//-------------------------------------------------------------------------------------------------
void Engine::PreRender() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->clearRenderer();
	renderer->setupMatrix();
}

//-------------------------------------------------------------------------------------------------
void Engine::PostRender() const
{
	RenderManager* renderer = g_engine->renderManager;
	renderer->swapBuffer();
}

//-------------------------------------------------------------------------------------------------
InputManager* Engine::GetInputManager()
{
	if (!inputManager)
	{
		inputManager = g_inputManager;
	}
	return inputManager;
}

//-------------------------------------------------------------------------------------------------
RenderManager* Engine::GetRenderManager()
{
	if (!renderManager)
	{
		renderManager = g_renderManager;
	}
	return renderManager;
}

//-------------------------------------------------------------------------------------------------
Engine::Engine()
{
	inputManager = InputManager::getSingleton();
	renderManager = RenderManager::getSingleton();
}

//-------------------------------------------------------------------------------------------------
Engine* Engine::getSingleton()
{
	if (!g_engine)
	{
		g_engine = new Engine();
	}
	return g_engine;
}