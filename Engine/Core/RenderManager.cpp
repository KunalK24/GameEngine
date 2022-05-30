#include "RenderManager.hpp"

RenderManager* g_renderManager = nullptr;

//-------------------------------------------------------------------------------------------------
RenderManager::RenderManager()
{
}


//-------------------------------------------------------------------------------------------------
RenderManager* RenderManager::getSingleton()
{
	if (!g_renderManager)
	{
		g_renderManager = new RenderManager();
	}
	return g_renderManager;
}

/*
//-------------------------------------------------------------------------------------------------
void RenderManager::RenderShape(Vector2f center, float radius, int numOfSides)
{
	glBegin(GL_LINE_LOOP);

	float degressPerSide = 2.0f * pi / static_cast<float>(numOfSides);
	for (int side = 0; side < numOfSides; ++side)
	{
		float xOffset = static_cast<float>(cos(degressPerSide * static_cast<float>(side)));
		float yOffset = static_cast<float>(sin(degressPerSide * static_cast<float>(side)));

		xOffset *= radius;
		yOffset *= radius;

		glVertex2f(xOffset + center.x, yOffset + center.y);
	}
	glEnd();
}
*/

//-------------------------------------------------------------------------------------------------
void RenderManager::RenderShape(std::vector<Vector2f> points, const Vector2f& center, float rotation)
{
	glPushMatrix();
	glTranslatef(center.x, center.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);

	for (unsigned int point = 0; point < points.size(); ++point)
	{
		glVertex2f(points[point].x, points[point].y);
	}
	glEnd();
	glPopMatrix();
}

//-------------------------------------------------------------------------------------------------
void RenderManager::RenderPoint(const Vector2f& center, float rotation)
{
	glPushMatrix();
	glTranslatef(center.x, center.y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);
	glVertex2f(10.0f, 0.0f);
	glVertex2f(-10.0f, 0.0f);

	glVertex2f(0.0f, 10.0f);
	glVertex2f(0.0f, -10.0f);
	glEnd();

	glPopMatrix();
}

//-------------------------------------------------------------------------------------------------
void RenderManager::RenderCircle(const Vector2f& center)
{
}

//-------------------------------------------------------------------------------------------------
void RenderManager::RenderLine(const Vector2f& center, float rotation)
{
}

//-------------------------------------------------------------------------------------------------
void RenderManager::clearRenderer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}


//-------------------------------------------------------------------------------------------------
void RenderManager::setupMatrix()
{
	// Setup View Matrix
	glLoadIdentity();
	glScalef(1.0f / 1600.0f, 1.0f / 900.0f, 1.0f);
}


//-------------------------------------------------------------------------------------------------
void RenderManager::swapBuffer()
{
	// Double Buffer, also known as FlipAndPresent
	SwapBuffers(displayDeviceContext);
}

