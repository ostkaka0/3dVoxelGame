#pragma once
class RawVoxel;

template<class VOXEL> class RawMatrix
{
	int width;
	int height;
	int depth;
	VOXEL *voxels;
};

typedef RawMatrix<RawVoxel> RawVoxelMatrix;