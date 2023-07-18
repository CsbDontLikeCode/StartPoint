#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
	m_Texture = StartPoint::Texture2D::Create("assets/textures/Yin.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(StartPoint::Timestep timestep)
{
	 // Update
	 m_CameraController.OnUpdate(timestep);

	// Render preparation.
	{
		 SP_PROFILE_SCOPE("Render Prep");
		 StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		 StartPoint::RenderCommand::Clear();
	}
	

	// Unlike the camera move, transform matrix moves the specific object in the scene.
	// glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));

	// Render
	{
		SP_PROFILE_SCOPE("Render");
		StartPoint::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// Position,Size and Color
		StartPoint::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.15f, 1.0f });
		StartPoint::Renderer2D::DrawQuad({ 1.0f, 0.5f }, { 0.5f, 0.5f }, { 0.1f, 0.1f, 0.85f, 1.0f });
		StartPoint::Renderer2D::DrawQuad({ -0.5f, 0.5f, -0.5f }, { 5.0f, 5.0f }, m_Texture);
		StartPoint::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Squares' color except blue ones", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
