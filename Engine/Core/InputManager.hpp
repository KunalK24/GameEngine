#pragma once

#include <vector>

enum Keys
{
	ESC_KEY = 27,
	W_KEY = 87,
	S_KEY = 83,
	A_KEY = 65,
	D_KEY = 68,
	SPACE_KEY = 32,

};

class InputManager
{
public:
	std::vector<bool> inputBuffer;
	std::vector<bool> currBuffer;

	InputManager();

	void Update();

	static InputManager* getSingleton();

	bool IsKeyDown(Keys key);
	bool IsKeyUp(Keys key);

	void setKeyStateDown(int keyValue);
	void setKeyStateUp(int keyValue);

	bool IsKeyDownThisFrame(Keys key);
	bool IsKeyUpThisFrame(Keys key);
};

extern InputManager* g_inputManager;