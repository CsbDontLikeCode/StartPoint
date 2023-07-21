#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
	m_Texture = StartPoint::Texture2D::Create("assets/textures/Yin.jpg");
	m_TextureAzi = StartPoint::Texture2D::Create("assets/textures/Azi.png");

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.01f, m_Particle.SizeVariation = 0.05f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(StartPoint::Timestep timestep)
{
	 // Update
	 m_CameraController.OnUpdate(timestep);

	// Render preparation.
	 StartPoint::Renderer2D::ResetStats();
	{
		 SP_PROFILE_SCOPE("Render Prep");
		 // Sky blue color - (0.46f, 0.84f, 0.91f)
		 StartPoint::RenderCommand::SetClearColor({ 0.46f, 0.84f, 0.91f, 1.0f });
		 StartPoint::RenderCommand::Clear();
	}

	// Render
	{
		SP_PROFILE_SCOPE("Render");

		static float rotation = 0.0f;
		rotation += timestep * 3.1415926f * 2;

		StartPoint::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// Position,Size and Color
		StartPoint::Renderer2D::DrawQuad({ -0.5f, 0.5f }, { 0.25f, 0.25f }, { 0.8f, 0.2f, 0.15f, 1.0f });
		StartPoint::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.5f, 0.5f }, { 0.1f, 0.1f, 0.85f, 1.0f });

		for (float y = -1.0f; y < 1.0f; y += 0.1f) 
		{
			for (float x = -1.0f; x < 1.0f; x += 0.1f) 
			{
				float r = (x + 1.0f) / 2;
				float g = (y + 1.0f) / 2;
				StartPoint::Renderer2D::DrawQuad({ x, y, -0.2 }, { 0.09f, 0.09f }, { r, g, 0.85f, 1.0f });
			}
		}
		StartPoint::Renderer2D::DrawRotatedQuad({ 0.75f, 0.0f, 0.1f }, { 0.5f, 0.5f }, rotation, { 0.1f, 0.95f, 0.85f, 1.0f });

		StartPoint::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f, 0.0f }, { 0.5f, 0.5f }, 45.0f, m_TextureAzi, 1.0f);
		StartPoint::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_Texture);
		
		StartPoint::Renderer2D::EndScene();
	}

	if (StartPoint::Input::IsMouseButtonPressed(SP_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = StartPoint::Input::GetMousePosition();
		auto width = StartPoint::Application::Get().GetWindow().GetWidth();
		auto height = StartPoint::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(timestep);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Renderer2D Stats");

	auto stats = StartPoint::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	//ImGui::ColorEdit4("Squares' color except blue ones", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
