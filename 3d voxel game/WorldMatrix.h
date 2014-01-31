/*#include <deque>

#define Deque(...) std::pair<std::deque<__VA_ARGS__>, long>

namespace voxel { class Voxel; }

namespace world
{
	class Chunk;

	class WorldMatrix
	{
	public:
		typedef Deque(Deque(Deque(Chunk*))) ChunkMatrixType;
	private:
		ChunkMatrixType chunkMatrix;

	public:
		Chunk *GetChunk(long x, long y, long z);
		voxel::Voxel *GetBlock(long x, long y, long z);
		void SetVoxel(long x, long y, long z, voxel::Voxel *voxel);

	};
}*/