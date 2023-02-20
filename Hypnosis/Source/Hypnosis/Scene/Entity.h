#pragma once

#include "Scene.h"
#include "Hypnosis/Core/Core.h"

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
			bool result = scene->registry.has<T>(handle);
			return result;
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			HS_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
			// std::forward is like a flag to not unpack the arguments here and forward them to entt
			T& comp = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			scene->OnComponentAdded<T>(*this, comp);
			return comp;
		}

		template<typename T>
		T& GetComponent()
		{
			HS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
			scene->registry.remove<T>(handle);
		}

		operator bool() const { return handle != entt::null; }
		operator uint32_t () const { return (uint32_t)handle; }
		operator entt::entity() const { return handle; }
		bool operator==(const Entity& other) const
		{
			return handle == other.handle && scene == other.scene;
		}
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity handle = entt::null;
		Scene* scene = nullptr;
	};

}