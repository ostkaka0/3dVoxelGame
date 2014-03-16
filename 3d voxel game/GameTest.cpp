#include <iostream>

#include "GameTest.h"
#include "StateTest.h"
#include "OpenglRenderer.h"


#include <Windows.h>

GameTest::GameTest()
{

}

GameTest::~GameTest()
{
	
}

void GameTest::Initialize()
{
	state = new StateTest();
#ifdef CLIENT
	renderer = new OpenglRenderer(this, width, height);
#endif
}

void GameTest::Update()
{
	state->Update(this);
	Sleep(3000);
}

void GameTest::Draw()
{
}

void GameTest::Error(const char *source, const char *description)
{
	state = nullptr;

	std::cout << "Error from class " << source << ": " << description;
}

/*#pragma region GL Events
void GameTest::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	std::cout << key << std::endl;
}
#pragma endregion*/