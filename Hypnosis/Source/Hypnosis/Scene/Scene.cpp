#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "Hypnosis/Renderer/Renderer.h"

namespace Hypnosis {

	Scene::Scene()
	{
		entt::entity entity = registry.create();

	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

			Renderer::Submit(mesh.mesh->GetVertexArray());
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity {registry.create(), this};
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;
		return entity;
	}

}