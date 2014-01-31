/*#pragma once
#define _VET_INTE_ 8

namespace voxel { class Voxel; }

namespace world
{
	class Chunk
	{
		voxel::Voxel *voxels[16][16][16];

	public:
		struct Pos;
		voxel::Voxel *getVoxel(Pos pos);
		void setVoxel(Pos pos, voxel::Voxel voxel);

		struct Pos
		{
			unsigned int x : 4;
			unsigned int y : 4;
			unsigned int z : 4;
		};
	};
}*/