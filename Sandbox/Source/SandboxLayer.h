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
	/*Hypnosis::Model* model;
	Hypnosis::Ref<Hypnosis::Shader> shader;

	Hypnosis::Ref<Hypnosis::Texture2D> diffuse;
	Hypnosis::Ref<Hypnosis::Texture2D> normals;
	Hypnosis::Ref<Hypnosis::Texture2D> roughness;
	Hypnosis::Ref<Hypnosis::Texture2D> metallic;*/

};