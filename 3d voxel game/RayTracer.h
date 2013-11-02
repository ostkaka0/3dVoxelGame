#include "IDrawer.h"

namespace graphics
{
	class RayTracer : public IDrawer
	{
	public:
		virtual void Draw(WorldMatrix *worldMatrix);
	};
}