#include <iostream>

#include "World.h"
#include "Chunk.h"

namespace world
{
	World::World()
		: m_chunkMatrix()
	{
		m_chunkMatrix.ExpandTo(16, [](){ return new Deque2<Deque2<world::Chunk>>(); });
		m_chunkMatrix.ExpandTo(-16, [](){ return new Deque2<Deque2<world::Chunk>>(); });

		for (int x = -16; x < 16; x++)
		{
			(*m_chunkMatrix[x])->ExpandTo(16, [](){ return new Deque2<world::Chunk>(); });
			(*m_chunkMatrix[x])->ExpandTo(-16, [](){ return new Deque2<world::Chunk>(); });

			for (int y = -16; y < 16; y++)
			{
				(*(**m_chunkMatrix[x])[y])->ExpandTo(16, []()->world::Chunk*{ return nullptr; });
				(*(**m_chunkMatrix[x])[y])->ExpandTo(-16, []()->world::Chunk*{ return nullptr; });

				for (int z = -16; z < 16; z++)
				{
					Chunk **chunk = (**(**m_chunkMatrix[x])[y])[z];

					Chunk (**neighbors)[6] = nullptr;

					*chunk = new Chunk(nullptr, neighbors);
				}
				//(*(**m_chunkMatrix[x])[y])->Clean();
			}
			//(*m_chunkMatrix[x])->Clean();
		}
		//m_chunkMatrix.Clean();
		
	}


	World::~World()
	{

	}

	// IRenderer
	bool World::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
	{
		int cX = 0;//(int)(float)MVP[1][0];
		int cY = 0;//(int)(float)MVP[1][1];
		int cZ = 0;//(int)(float)MVP[1][2];

		const int range = 6;

		for (int x = cX-range; x < cX+range; x++)
		{
			if (m_chunkMatrix[x] == nullptr)
				continue;

			for (int y = cY-range; y < cY+range; y++)
			{
				if ((**m_chunkMatrix[x])[y] == nullptr)
				continue;

				for (int z = cZ-range; z < cZ+range; z++)
				{
					Chunk **chunk = (**(**m_chunkMatrix[x])[y])[z];

					if (chunk == nullptr)
						continue;

					glm::mat4 MVP2 = MVP;
					MVP2 = glm::translate(MVP2, glm::vec3(x*16.f, y*16.f, z*16.f));

					(*chunk)->Render(renderer, MVP2, SHADER_DEFAULT);
				}
			}
		}

		return true;
		/*				glm::mat4 ModelMatrix2 = glm::mat4(1.0);
				ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3((float)x*voxels->getWidth(), (float)y*voxels->getHeight(), (float)z*voxels->getWidth()));
				glm::mat4 MVP2 = Projection * View * ModelMatrix2;
				renderer->RenderMatrix(voxels, MVP2, SHADER_DEFAULT);*/
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