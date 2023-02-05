#pragma once

#include "Hypnosis/Scene/Scene.h"
#include "Hypnosis/Core/Core.h"
#include "Hypnosis/Scene/Entity.h"

namespace Hypnosis {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

	private:
		void DrawNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> context;
		Entity selectedEntity;
	};

}