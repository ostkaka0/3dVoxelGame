#pragma once

#include "IRenderable.h"

class Game;
class State;
class IWorld;

namespace entity
{
	class IEntity : public virtual IRenderable
	{
		public:
		virtual ~IEntity() override;
		virtual void Render(IRenderer *renderer, glm::mat4 MVP) override;

		virtual void Update(Game *game, State *state, IWorld *world);

	};
}