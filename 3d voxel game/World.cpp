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
	bool World::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
	{
		return false;
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