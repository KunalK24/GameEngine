#pragma once

// Needed to setup a window
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Needed for OpenGL
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment( lib, "opengl32" )
#pragma comment( lib, "Glu32" )

#include <math.h>
#include <vector>

#include "Utilities.h"

extern HDC displayDeviceContext;

class RenderManager
{
public:
	RenderManager();

	static RenderManager* getSingleton();

	//void RenderShape(Vector2f center, float radius, int numOfSides);
	void RenderShape(std::vector<Vector2f> points, const Vector2f& center, float rotation);

	void RenderPoint(const Vector2f& center, float rotation);

	void RenderCircle(const Vector2f& center);

	void RenderLine(const Vector2f& center, float rotation);

	void clearRenderer();
	void setupMatrix();
	void swapBuffer();

};

extern RenderManager* g_renderManager;