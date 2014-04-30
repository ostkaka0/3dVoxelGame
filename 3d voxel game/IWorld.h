#include "IRenderable.h"

class IVoxel;

namespace world
{
	class IWorld : public virtual IRenderable
	{
		virtual ~IWorld() {}

		virtual void SetVoxel(unsigned char x, unsigned char y, unsigned char z, IVoxel *voxel)=0;
		virtual IVoxel *getVoxel(unsigned char x, unsigned char y, unsigned char z)=0;
	};
}