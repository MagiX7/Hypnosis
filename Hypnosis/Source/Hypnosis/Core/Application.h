#pragma once

#include "Hypnosis/Events/ApplicationEvent.h"
#include "Hypnosis/ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include <memory>

namespace Hypnosis {

	class Window;
	class Event;

	class Application
	{
	public:
		Application();
		virtual ~Application();	
		
		inline static Application& GetInstance() { return *instance; }

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		inline Window& GetWindow() { return *window; }
		inline float GetTimeStep() { return timestep; }
		float GetTotalExecutionTime();

	private:
		Application(const Application&);
		Application& operator=(Application&) {}
		
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		static Application* instance;
		bool isRunning;
		bool minimized;

		TimeStep timestep = 0;
		float lastFrameTime = 0;
		
		Scope<Window> window;

		LayerStack layerStack;
		ImGuiLayer* imguiLayer;

	};

	Application* CreateApplication();

}