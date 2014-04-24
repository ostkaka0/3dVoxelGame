class IRenderer;

//IRenderable is probably a better name
class IDrawable
{
public:
	virtual void RenderMatrix(IRenderer *renderer)=0;
};