#include <iostream>

#include "GameTest.h"
#include "StateTest.h"
#include "OpenglRenderer.h"


#include <Windows.h>

#include "GL.h"

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
	renderer->LoadShaders("vertexshader.glsl", "fragmenshader.glsl", "geometryshader.glsl");
	glEnable(GL_DEPTH_TEST);
	//glFrustum(-0.1,0.1,-0.1,0.1,0.1,1024);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable( GL_BLEND );
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
#endif
}

void GameTest::Update()
{
	state->Update(this);
	Sleep(300);
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