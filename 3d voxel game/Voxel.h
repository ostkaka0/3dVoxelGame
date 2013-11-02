#include "GLUtilty.h"
#include "Macros.h"

namespace voxel
{
	class Voxel
	{
	public:
		 virtual float GetRoundness()=0;
		 virtual float GetDensity()=0;
		 virtual Color GetColor()=0;
		 virtual float GetOpacity()=0;
	CLIENT(
		 virtual GLfloat *Draw(/*...*/);)
	};
}