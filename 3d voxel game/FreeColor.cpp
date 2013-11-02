#include "FreeColor.h"

namespace voxel
{
	float FreeColor::GetRoundness()
	{
		return roundness;
	}

	float FreeColor::GetDensity()
	{
		return density;
	}

	Color FreeColor::GetColor()
	{
		return color;
	}

	float FreeColor::GetOpacity()
	{
		return opacity;
	}
}