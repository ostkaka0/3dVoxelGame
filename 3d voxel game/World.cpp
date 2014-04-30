#include "World.h"

namespace world
{
	World::World(void)
	{

	}


	World::~World(void)
	{

	}

	// IRenderer
	void World::Render(IRenderer *renderer, glm::mat4 MVP)
	{

	}

	// IWorld
	void World::SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel)
	{

	}

	IVoxel *World::getVoxel(unsigned char x, unsigned char y, unsigned char z)
	{
		return nullptr;
	}
}