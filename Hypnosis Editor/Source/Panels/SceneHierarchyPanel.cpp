#include "SceneHierarchyPanel.h"

#include "Hypnosis/Scene/Components.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hypnosis {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		this->context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		context->registry.each([&](auto entityId)
		{
			Entity entity{ entityId, context.get() };
			DrawNode(entity);			
		});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectedEntity = {};

		ImGui::End();


		ImGui::Begin("Inspector");
		if (selectedEntity)
		{
			DrawComponents(selectedEntity);
		}

		ImGui::End();

	}

	void SceneHierarchyPanel::DrawNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;
		
		ImGuiTreeNodeFlags flags = ((selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

		// 32 bits from uint32_t gets converted into 64 because void* weights 64 bits, if this isnt done, it can lead to errors
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			selectedEntity = entity;
		}

		// TODO: Call DrawNode recursively for childrens
		if (opened)
		{
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			// Wide chars support?
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				auto& transform = entity.GetComponent<TransformComponent>().transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
			}
		}

		if (entity.HasComponent<LightComponent>())
		{
			if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
			{
				auto& light = entity.GetComponent<LightComponent>();
				ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), 0.1f);
				ImGui::DragFloat("Intensity", &light.intensity, 0.1f);
				ImGui::ColorPicker3("Color", glm::value_ptr(light.color), 0.1f);
			}
		}


	}

}