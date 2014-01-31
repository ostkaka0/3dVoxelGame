#pragma once
#include "IVoxel.h"
#include "Color.h"

//namespace voxel
//{
	class FreeColor : public virtual IVoxel
	{
		Color color;
		//GLfloat opacity;
		float roundness;
		float density;
	public:
		virtual float GetRoundness();
		virtual float GetDensity();
		virtual Color GetColor();
		//virtual float GetOpacity();
	};
//}