#pragma once

class IRenderer;

class IMatrix
{
	virtual void Render(IRenderer *renderer)=0;
};