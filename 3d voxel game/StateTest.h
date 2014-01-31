#pragma once
#include "State.h"

class StateTest : public State
{
public:
	virtual void Draw(Game *game, IRenderer *renderer);
	virtual void Update(Game *game);
};