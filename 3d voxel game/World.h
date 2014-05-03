#pragma once

#include <deque>

#include "IWorld.h"
#include "deque2.h"
#include "Chunk.h"

//#define DEQUE(...) std::deque<std::pair<__VA_ARGS__, long>>



namespace world
{
	class Chunk;

	class World : public virtual IWorld
	{
	protected:
		Deque2<Deque2<Deque2<world::Chunk>>> m_chunkMatrix;//DEQUE(DEQUE(DEQUE(Chunk*))) chunkMatrix;
		//std::vector<WorldChild*>
	public:
		World();
		virtual ~World() override;

		// IRenderer
		virtual bool Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType) override;

		// IWorld
		virtual void SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel) override;
		virtual IVoxel *getVoxel(unsigned char x, unsigned char y, unsigned char z) override;
	};
}