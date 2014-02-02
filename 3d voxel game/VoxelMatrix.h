#pragma once
#include "MatrixTerminal.h"

class IVoxel;

class VoxelMatrix : public MatrixTerminal
{
public:
	int m_width;
	int m_height;
	int m_depth;
	IVoxel **m_voxels;
public:
	VoxelMatrix(const int width, const int height, const int depth);
	VoxelMatrix(const int width, const int height, const int depth, IVoxel **voxels);
	int getWidth();
	int getHeight();
	IVoxel *getVoxel(int x, int y, int z);
	void setVoxel(int x, int y, int z, IVoxel *voxel);
};