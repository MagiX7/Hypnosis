#include "Entity.h"

namespace Hypnosis {

	Entity::Entity(entt::entity entityHandle, Scene* context)
		: handle(entityHandle), scene(context)
	{
	}

}
