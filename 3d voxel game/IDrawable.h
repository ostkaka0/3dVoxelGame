class IRenderer;

class IDrawable
{
public:
	virtual void RenderMatrix(IRenderer *renderer)=0;
};