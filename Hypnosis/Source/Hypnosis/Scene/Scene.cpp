#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "Hypnosis/Renderer/Renderer.h"

namespace Hypnosis {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(TimeStep ts)
	{
		// View for getting 1 component, group for 1+ components

		Camera* primaryCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.isPrimary)
				{
					primaryCamera = &camera.camera;
					cameraTransform = &transform.transform;
					break;
				}
			}
		}

		if (primaryCamera)
		{
			//Renderer::BeginScene(primaryCamera->GetProjection(), *cameraTransform);

			auto group = registry.group<TransformComponent>(entt::get<MeshComponent>);
			for (auto entity : group)
			{
				auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

				Renderer::Submit(mesh.mesh->GetVertexArray());
			}

			//Renderer::EndScene();
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

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		viewportWidth = width;
		viewportHeight = height;

		auto view = registry.view<CameraComponent>();

		for (auto entity : view)
		{
			auto cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.fixedAspectRatio)
			{
				cameraComponent.camera.SetViewportSize(width, height);
			}
		}

	}

}