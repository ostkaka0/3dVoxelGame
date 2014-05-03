#include "IRenderer.h"
#include "Game.h"
#include "State.h"
#include "EventHandler.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>

Game::~Game()
{
#ifdef CLIENT
	if (!window)
		glfwDestroyWindow(window);
    glfwTerminate();
#endif
}

Game *&Game::getGame()
{
	static Game *game;
	return game;
}

#pragma region Events

void Game::Error(const char *source, const char *description)
{
	eventHandler->ErrorCallback(this, source, description);
}
#ifdef CLIENT
#pragma region input Events
void Game::MouseButtonCallback(int button, int action, int mods)
{
	eventHandler->MouseButtonCallback(this, window, button, action, mods);
}

void Game::CursorPosCallback(int x, int y)
{
	eventHandler->CursorPosCallback(this, window, x, y);
}

void Game::CursorEnterCallback(int entered)
{
	eventHandler->CursorEnterCallback(this, window, entered);
}

void Game::ScrollCallback(int xOffset, int yOffset)
{
	eventHandler->ScrollCallback(this, window, xOffset, yOffset);
}

void Game::KeyCallback(int key, int scancode, int action, int mods)
{
	//eventHandler->KeyCallback(this, window, key, scancode, action, mods);
}

void Game::CharCallback(unsigned int character)
{
	eventHandler->CharCallback(this, window, character);
}
#pragma endregion
#endif
#pragma endregion

void Game::Start()
{
	srand (time(NULL));
	eventHandler = new EventHandler();
#ifdef CLIENT
	if (!glfwInit())
		Error("Game", "glfwInit failed!");

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_FSAA_SAMPLES, 4);
	//glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1200, 900, "Voxel Engine", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback([](int error, const char *description)
		{ Game::getGame()->Error("GLFW", description); });



	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
	//glfwSetWindowTitle( "Tutorial 01" );

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
	state->Load(this, eventHandler);

	while (state
#ifdef CLIENT
		&& !glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
#endif
		)
	{
		state->Update(this);

#ifdef CLIENT
		renderer->Clear(window);
		state->Draw(this, renderer);
		Draw();
		renderer->Render(window);
#endif
	}
	this->Exit();
}

void Game::Exit()
{
	if (state)
	{
		delete state;
		state = nullptr;
	}
#ifdef CLIENT
	if (renderer)
	{
		delete renderer;
		renderer = nullptr;
	}
	glfwTerminate();
#endif
}

void Game::Restart()
{
	Exit();
	Initialize();
}