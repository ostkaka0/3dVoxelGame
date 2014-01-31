#include "IRenderer.h"
#include "Game.h"
#include "State.h"

Game::~Game()
{
	if (window)
		glfwDestroyWindow(window);
    glfwTerminate();
}

Game *&Game::getGame()
{
	static Game *game;
	return game;
}

#pragma region GL Events
#ifdef CLIENT
#pragma region input Events
void Game::MouseButtonCallback(int button, int action, int mods)
{
	//eventHandler->MouseButtonCallback(button, action, mods);
}

void Game::CursorPosCallback(int x, int y)
{

}

void Game::CursorEnterCallback(int entered)
{

}

void Game::ScrollCallback(int xOffset, int yOffset)
{

}

void Game::KeyCallback(int key, int scancode, int action, int mods)
{

}

void Game::CharCallback(unsigned int character)
{

}
#pragma endregion
#endif
#pragma endregion

void Game::Start()
{
#ifdef CLIENT
	if (!glfwInit())
		Error("Game", "glfwInit failed!");

	/*glfwSetErrorCallback([](int error, const char *description)->void
	{
		//game->Error(typeid(*this).name, description);
	});*/

	window = glfwCreateWindow(800, 600, "Voxel Engine", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	

	glfwMakeContextCurrent(window);

	//glfwSetErrorCallback([](int error, char *description)
	//{static_cast<GameTest*>(Game::getGame())->Error("GameTest", description);});

#pragma region callback events
#pragma region input callbacks

	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
		{ Game::getGame()->MouseButtonCallback(button, action, mods); });
	
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
		{ Game::getGame()->CursorPosCallback(x, y); });
	
	glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered)
		{ Game::getGame()->CursorEnterCallback(entered); });
	
	glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
		{ Game::getGame()->ScrollCallback(xoffset, yoffset); });

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{ Game::getGame()->KeyCallback(key, scancode, action, mods); });

	glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int character)
		{ Game::getGame()->CharCallback(character); });
#pragma endregion

#pragma region window callbacks
	/*
	glfwSetWindowPosCallback(window, [](GLFWwindow *window, int x, int y)
		{ Game::getGame()->WindowPosCallback(x, y); });
 
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
		{ Game::getGame()->WindowSizeCallback(width, height); });
 
	glfwSetWindowCloseCallback (window, [](GLFWwindow *window)
		{ Game::getGame()->WindowCloseCallback(); });
 
	glfwSetWindowRefreshCallback (window, [](GLFWwindow *window)
		{ Game::getGame()->WindowRefreshCallback(); });
 
	glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int mod)
		{ Game::getGame()->WindowFocusCallback(mod); });
 
	glfwSetWindowIconifyCallback(window, [](GLFWwindow *window, int mod)
		{ Game::getGame()->WindowIconifyCallback(mod); });
 
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
		{ Game::getGame()->FrameBufferSizeCallback(width, height); });

	glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int mod)
		{ Game::getGame()->CursorEnterCallback(mod); });
		*/
#pragma endregion
#pragma endregion

	glfwGetFramebufferSize(window, &width, &height);
#endif

	Initialize();

	while (state
#ifdef CLIENT
		&& !glfwWindowShouldClose(window)
#endif
		)
	{
		state->Update(this);

#ifdef CLIENT
		renderer->Clear();
		state->Draw(this, renderer);
		Draw();
		renderer->Render(window);
#endif
	}
}

void Game::Exit()
{
	if (state)
	{
		delete state;
		state = nullptr;
	}

	if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
}

void Game::Restart()
{
	Exit();
	Initialize();
}