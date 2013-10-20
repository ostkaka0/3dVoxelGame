#include "Voxel.h"

class VoxelFreeColor : public virtual Voxel
{
	Color color;
	GLfloat opacity;
	float roundness;
	float density;
public:
	virtual float GetRoundness();
	virtual float GetDensity();
	virtual Color GetColor();
	virtual float GetOpacity();
};