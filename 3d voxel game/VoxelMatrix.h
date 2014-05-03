#pragma once
#include "RenderableTerminal.h"

class IVoxel;

class VoxelMatrix : public RenderableTerminal
{
public:
	int m_width;
	int m_height;
	int m_depth;
	IVoxel **m_voxels;
public:
	VoxelMatrix(const int width, const int height, const int depth);
	VoxelMatrix(const int width, const int height, const int depth, IVoxel **voxels);

	virtual bool Render(IRenderer *renderer, glm::mat4 MVP, ShaderType shaderType) override;
	virtual ShaderType getShaderType() const;

	int getWidth();
	int getHeight();
	IVoxel *getVoxel(int x, int y, int z);
	void setVoxel(int x, int y, int z, IVoxel *voxel);
};