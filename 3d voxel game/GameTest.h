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

};