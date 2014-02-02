#pragma once

class IRenderer;

class IMatrix
{
public:
	virtual void Render(IRenderer *renderer)=0;
};