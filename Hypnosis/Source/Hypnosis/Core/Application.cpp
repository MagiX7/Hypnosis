#include "Application.h"
#include "Window.h"
#include "Input.h"
#include "Hypnosis/Renderer/Renderer.h"

#include "Log.h"

#include "Hypnosis/Events/Event.h"
#include "Hypnosis/Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <iostream>

namespace Hypnosis {

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		
		Log::Init();
		HS_CORE_INFO("[INFO] Logging system initialized");
		
		window = std::make_unique<Window>(1720, 920);
		window->SetEventCallback(HS_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);

		isRunning = true;
		minimized = false;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (isRunning)
		{
			RenderCommand::Clear({ 0.2f,0.2f,0.2f,1.0f });

			float t = glfwGetTime();
			timestep = t - lastFrameTime;
			lastFrameTime = t;

			if (!minimized)
				for (auto& l : layerStack)
					l->OnUpdate(timestep);

			imguiLayer->Begin();
			for (auto& l : layerStack)
				l->OnImGuiRender();
			imguiLayer->End();
			
			Input::GetInstance()->ResetScrollStats();

			window->SwapBuffers();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack.PushOverlay(overlay);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		layerStack.PopOverlay(overlay);
	}

	float Application::GetTotalExecutionTime()
	{
		return glfwGetTime();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HS_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HS_BIND_EVENT_FN(Application::OnWindowResize));
		Input::GetInstance()->OnEvent(e);
		
		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			// --it here and not in the loop because if the event has been handled we dont want to propagate it to the under layers
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}
		
		RenderCommand::OnResize(e.GetWidth(), e.GetHeight());
		
		minimized = false;
	}
}