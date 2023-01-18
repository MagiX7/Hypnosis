#pragma once

#include "Hypnosis.h"

class SandboxLayer : public Hypnosis::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(const Hypnosis::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hypnosis::Event& e) override;

private:


};