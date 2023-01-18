#include <Hypnosis/Core/EntryPoint.h>

//#include "Sandbox2D.h"
//#include "ExampleLayer.h"

class Sandbox : public Hypnosis::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hypnosis::Application* Hypnosis::CreateApplication()
{
	return new Sandbox();
}