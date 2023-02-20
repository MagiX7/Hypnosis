#include "SceneHierarchyPanel.h"

#include "Hypnosis/Scene/Components.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hypnosis {

	static void DrawVec3Control(const std::string& label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			value.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &value.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			value.y = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &value.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			value.z = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &value.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}


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


		// Right click on the panel
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}


		ImGui::End();


		ImGui::Begin("Inspector");
		if (selectedEntity)
		{
			DrawComponents(selectedEntity);

			ImGui::Dummy({ 0, 10 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 3 });

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("Add");

			// TODO: Think of moving it into a templated function
			if (ImGui::BeginPopup("Add"))
			{
				if (ImGui::MenuItem("Mesh"))
				{
					selectedEntity.AddComponent<MeshComponent>();
					ImGui::CloseCurrentPopup();
				}
				/*if (ImGui::MenuItem("Material"))
				{
					selectedEntity.AddComponent<MaterialComponent>();
					ImGui::CloseCurrentPopup();
				}*/
				if (ImGui::MenuItem("Light"))
				{
					selectedEntity.AddComponent<LightComponent>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Camera"))
				{
					selectedEntity.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
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

		bool wantToDeleteEntity = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				wantToDeleteEntity = true;

			ImGui::EndPopup();
		}

		// TODO: Call DrawNode recursively for childrens
		if (opened)
		{
			ImGui::TreePop();
		}

		if (wantToDeleteEntity)
		{
			context->DestroyEntity(entity);
			if (selectedEntity == entity)
				selectedEntity = {};
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

		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;



		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::CollapsingHeader("Transform", flags))
			{
				auto& transComp = entity.GetComponent<TransformComponent>();
				DrawVec3Control("Position", transComp.position);
				DrawVec3Control("Rotation", transComp.rotation);
				DrawVec3Control("Scale", transComp.scale);
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			ImGui::Dummy({ 0, 5 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 5 });

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4,4 });

			bool opened = ImGui::CollapsingHeader("Camera", flags);
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);

			if (ImGui::Button("+", { 20,25 }))
			{
				ImGui::OpenPopup("ComponentOptions");
			}

			ImGui::PopStyleVar();

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentOptions"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (opened)
			{
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.camera;

				const char* types[] = { "Perspective", "Ortographic" };
				const char* currentTypeString = types[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection Type", currentTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentTypeString == types[i];
						if (ImGui::Selectable(types[i], isSelected))
						{
							currentTypeString = types[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}
						
						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::PERSPECTIVE)
				{
					float verticalFov = camera.GetVerticalFov();
					if (ImGui::DragFloat("Vertical FOV", &verticalFov))
						camera.SetVerticalFov(verticalFov);
					
					float near = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &near))
						camera.SetPerspectiveNearClip(near);

					float far = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &far))
						camera.SetPerspectiveFarClip(far);
				}
				else if(camera.GetProjectionType() == SceneCamera::ProjectionType::ORTHOGRAPHIC)
				{
					float size = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Orthographic Size", &size))
						camera.SetOrthographicSize(size);

					float near = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &near))
						camera.SetOrthographicNearClip(near);

					float far = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &far))
						camera.SetOrthographicFarClip(far);

					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.fixedAspectRatio);
				}
			}

			if (removeComponent)
			{
				entity.RemoveComponent<CameraComponent>();
			}
		}


		if (entity.HasComponent<LightComponent>())
		{
			ImGui::Dummy({ 0, 5 });
			ImGui::Separator();
			ImGui::Dummy({ 0, 5 });
			if (ImGui::CollapsingHeader("Light", flags))
			{
				auto& light = entity.GetComponent<LightComponent>();
				ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), 0.1f);
				ImGui::DragFloat("Intensity", &light.intensity, 0.1f);
				ImGui::ColorPicker3("Color", glm::value_ptr(light.color), 0.1f);
			}
		}

		// TODO: Camera Component UI


	}

}