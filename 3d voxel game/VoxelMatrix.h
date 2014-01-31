#pragma once
#include "IMatrix.h"

class IVoxel;

class VoxelMatrix : IMatrix
{
	virtual void Render(IRenderer *renderer);
};