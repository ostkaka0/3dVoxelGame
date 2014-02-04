#include "StateTest.h"

#include "Game.h"
#include "IRenderer.h"
#include "VoxelMatrix.h"

void StateTest::Load(Game *game, EventHandler *eventHandler)
{
	voxels = new VoxelMatrix(16, 16, 16);

	voxels->setVoxel(3, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(4, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(5, 3, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(5, 4, 3, reinterpret_cast<IVoxel*>(1));
	voxels->setVoxel(3, 3, 5, reinterpret_cast<IVoxel*>(1));
}

void StateTest::Draw(Game *game, IRenderer *renderer)
{
	glMatrixMode(GL_PROJECTION);
	renderer->PushMatrix();
	renderer->Translate(0,0, -10);
	renderer->RenderMatrix(voxels);
	renderer->PopMatrix();
}

void StateTest::Update(Game *game)
{

}