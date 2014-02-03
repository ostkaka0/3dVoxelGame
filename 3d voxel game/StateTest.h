#pragma once
#include "State.h"

class VoxelMatrix;

class StateTest : public State
{
	VoxelMatrix *voxels;
public:
	virtual void Load(Game *game, EventHandler *eventHandler);
	virtual void Draw(Game *game, IRenderer *renderer);
	virtual void Update(Game *game);
};