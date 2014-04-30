#pragma once

#include <deque>

#include "IWorld.h"
#include "deque2.h"

//#define DEQUE(...) std::deque<std::pair<__VA_ARGS__, long>>

class Chunk;

namespace world
{
	class World : public virtual IWorld
	{
	protected:
		Deque2<Deque2<Deque2<Chunk>>> chunkMatrix;//DEQUE(DEQUE(DEQUE(Chunk*))) chunkMatrix;
	public:
		World(void);
		virtual ~World(void);

		// IRenderer
		virtual void Render(IRenderer *renderer, glm::mat4 MVP) override;

		// IWorld
		virtual void SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel) override;
		virtual IVoxel *getVoxel(unsigned char x, unsigned char y, unsigned char z) override;
	};
}