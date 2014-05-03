#include "Chunk.h"
#include "VoxelMatrix.h"
#include "FreeColor.h"

namespace world
{
	Chunk::Chunk(IGenerator *generator, Chunk (**neighbors)[6])
	{
		m_neighbors = neighbors;
		m_voxelMatrix = new VoxelMatrix(16, 16, 16);
		m_voxelMatrix->setVoxel(1,1,1, new FreeColor());
	}

	Chunk::~Chunk()
	{
		delete m_voxelMatrix;
	}

		
	void Chunk::SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel)
	{
		m_voxelMatrix->setVoxel(x, y, z, voxel);
	}

	IVoxel *Chunk::getVoxel(unsigned char x, unsigned char y, unsigned char z)
	{
		return m_voxelMatrix->getVoxel(x, y, z);
	}

	bool Chunk::Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType)
	{
		return m_voxelMatrix->Render(renderer, MVP, SHADER_DEFAULT);
	}
}