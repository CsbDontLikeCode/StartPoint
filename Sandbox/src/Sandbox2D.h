#pragma once
#include <StartPoint.h>

#include <glm/gtc/matrix_transform.hpp>

#include "ParticleSystem.h"


class Sandbox2D : public StartPoint::Layer 
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(StartPoint::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(StartPoint::Event& event) override;
private:
	StartPoint::OrthegraphicCameraController m_CameraController;

	StartPoint::Ref<StartPoint::VertexArray> m_SquareVA;
	StartPoint::Ref<StartPoint::Shader> m_Shader;

	StartPoint::Ref<StartPoint::Texture2D> m_Texture;
	StartPoint::Ref<StartPoint::Texture2D> m_TextureAzi;

	glm::vec4 m_SquareColor = glm::vec4(0.3f, 0.6f, 0.9f, 1.0f);

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};