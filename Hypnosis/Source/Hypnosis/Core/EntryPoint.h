#pragma once

#include "Application.h"

extern Hypnosis::Application* Hypnosis::CreateApplication();

int main()
{
	Hypnosis::Application* app = Hypnosis::CreateApplication();
	app->Run();
	delete app;	
}