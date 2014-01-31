#pragma once

#ifdef CLIENT
class GLFWwindow;
#endif
class IRenderer;
class State;

class Game
{
protected:
	State *state;
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
	virtual void Error(const char *source, const char *description)=0;

#pragma region GL Events
#ifdef CLIENT
	virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)=0;
#endif
#pragma endregion

	void Start();
	void Exit();
	void Restart();
};