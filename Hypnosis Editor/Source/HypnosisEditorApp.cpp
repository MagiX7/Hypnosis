#include "Hypnosis/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Hypnosis {

	class HypnosisEditorApp : public Application
	{
	public:
		HypnosisEditorApp()
		{
			PushLayer(new EditorLayer());
		}

		~HypnosisEditorApp()
		{

		}

	};

	Application* CreateApplication()
	{
		return new HypnosisEditorApp();
	}
}