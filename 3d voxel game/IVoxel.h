#pragma once
#include "Color.h"
//namespace voxel
//{
	class IVoxel
	{
	public:
		 virtual float GetRoundness()=0;
		 virtual float GetDensity()=0;
		 virtual Color GetColor()=0;
		 virtual float GetOpacity()=0;
	//CLIENT(
	//	 virtual GLfloat *Draw(/*...* /);)
	};
//}