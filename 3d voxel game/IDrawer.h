class WorldMatrix;

namespace graphics
{
	class IDrawer
	{
	public:
		virtual void Draw(WorldMatrix *worldMatrix)=0;
	};
}