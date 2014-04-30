#pragma once

#include <vector>
#include <memory>

#include "IRenderable.h"

class VoxelMatrix;
class IVoxel;
class IGenerator;
class IEntity;
// class ICreature; ?

namespace world
{
	class Chunk : public virtual IRenderable
	{
	protected:
		VoxelMatrix *voxelMatrix;
		Chunk **Neighbors[6];

		///////////////////////////////////////////////////////////////////////////////////////////
		// (Unimplemented system):
		// unique<Creature>		  - Real but hidden owner, "soul" (IController)
		// unique<weak<Creature>> - Illusion of physical owner (Chunk, Vehicle)
		// weak<weak<Creature>>	  - No ownership, requires a physical existence (GUI, anything)
		// weak<Creature>         - No ownership (GUI, anything)
		// code:
		// std::vector<std::weak_ptr<std::unique_ptr<Creature>> creatures;
		///////////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::unique_ptr<IEntity>> entityVector;

	public:
		Chunk(IGenerator *Generator, Chunk **Neighbors[6]);
		virtual ~Chunk() override;
		
		void SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel);
		IVoxel *getVoxel(unsigned char x, unsigned char y, unsigned char z);

		virtual void Render(IRenderer *renderer, glm::mat4 MVP) override;
	};
}





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