#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
// Temporary
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(StartPoint::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	// Render
	StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	StartPoint::RenderCommand::Clear();

	// Unlike the camera move, transform matrix moves the specific object in the scene.
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));

	StartPoint::Renderer2D::BeginScene(m_CameraController.GetCamera());
	StartPoint::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.8f, 0.2f, 0.15f, 1.0f});
	StartPoint::Renderer2D::EndScene();
	//std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader)->Bind();
	//std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);
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
