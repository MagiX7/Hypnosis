#pragma once

#include "Scene.h"
#include "Hypnosis/Core/Log.h"

#include <entt.hpp>

namespace Hypnosis {

	class Entity
	{
	public:
		Entity() {};
		Entity(entt::entity entityHandle, Scene* context);
		Entity(const Entity& other) = default;

		template<typename T>
		bool HasComponent() const
		{
			return scene->registry.any_of<T>(handle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (!HasComponent<T>())
			{
				//ZN_CORE_FATAL("Entity already has component");
				//return NULL;
			}
			// std::forward is like a flag to not unpack the arguments here and forward them to entt
			return scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>())
			{
				//ZN_CORE_FATAL("Entity already has component");
				//return NULL;
			}
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				ZN_CORE_FATAL("Entity does not have component");
				return;
			}
			scene->registry.remove<T>(handle);
		}

		operator bool() const { return handle != entt::null; }

	private:
		entt::entity handle = entt::null;
		Scene* scene = nullptr;
	};

}