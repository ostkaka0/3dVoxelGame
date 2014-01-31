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

	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{ Game::getGame()->keyCallback(window, key, scancode, action, mods); });

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