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

		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry registry;

		uint32_t viewportWidth = 0;
		uint32_t viewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}