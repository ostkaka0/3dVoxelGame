#include "VoxelMatrix.h"

VoxelMatrix::VoxelMatrix(const int width, const int height, const int depth)
	: m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_voxels(new IVoxel*[width*height*depth])
{
	for (int z = 0; z < depth; z++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				setVoxel(x, y, z, nullptr);
			}
		}
	}
}

VoxelMatrix::VoxelMatrix(const int width, const int height, const int depth, IVoxel **voxels)
	: m_width(width)
	, m_height(height)
	, m_depth(depth)
	, m_voxels(voxels)
{
}

ShaderType VoxelMatrix::getShaderType() const
{
	return SHADER_DEFAULT;
}

int VoxelMatrix::getWidth()
{
	return m_width;
}

int VoxelMatrix::getHeight()
{
	return m_height;
}

IVoxel *VoxelMatrix::getVoxel(int x, int y, int z)
{
	return m_voxels[x%m_width + y%m_height*m_width + z%m_depth*m_height*m_width];
}

void VoxelMatrix::setVoxel(int x, int y, int z, IVoxel *voxel)
{
	m_voxels[x%m_width + y%m_height*m_width + z%m_depth*m_height*m_width] = voxel;
}
