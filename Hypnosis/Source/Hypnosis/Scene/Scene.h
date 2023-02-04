#pragma once

#include "Hypnosis/Core/TimeStep.h"

#include <entt.hpp>

namespace Hypnosis {

	class Entity;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void OnUpdate(TimeStep ts);

		Entity CreateEntity(const std::string& name = std::string());

	private:
		entt::registry registry;

		friend class Entity;
	};

}