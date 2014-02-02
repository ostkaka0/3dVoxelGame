#pragma once

#ifdef CLIENT
class GLFWwindow;
#endif
class IRenderer;
class State;
class EventHandler;

class Game
{
protected:
	State *state;
	EventHandler *eventHandler;
#ifdef CLIENT
	IRenderer *renderer;
	int width;
	int height;

	GLFWwindow *window;
#endif

public:
	~Game();
	static Game *&getGame();

	virtual void Initialize()=0;

	virtual void Update()=0;
#ifdef CLIENT
	virtual void Draw()=0;
#endif
	virtual void Error(const char *source, const char *description);

#pragma region GL Events
#ifdef CLIENT
#pragma region input Events
	virtual void MouseButtonCallback(int button, int action, int mods);
	virtual void CursorPosCallback(int x, int y);
	virtual void CursorEnterCallback(int entered);
	virtual void ScrollCallback(int xOffset, int yOffset);
	virtual void KeyCallback(int key, int scancode, int action, int mods);
	virtual void CharCallback(unsigned int character);
#pragma endregion
#endif
#pragma endregion
	void Start();
	void Exit();
	void Restart();
};