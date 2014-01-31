#pragma once
class RawVoxel;

template<class VOXEL> class RawMatrix
{
	int width;
	int height;
	int height;
	VOXEL *voxels;
};

typedef RawMatrix<RawVoxel> RawVoxelMatrix;