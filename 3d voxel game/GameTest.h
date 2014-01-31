#pragma once
#include "GL.h"

#include "Game.h"

class GameTest : public Game
{

public:
	GameTest();
	~GameTest();
	virtual void Initialize();

	virtual void Update();
	virtual void Draw();

	virtual void Error(const char *source, const char *description);

#pragma region GL Events
#ifdef CLIENT
	virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
#endif
#pragma endregion

};