#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

static const int s_MapWidth = 24;
static const char* s_MapTiles = 
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWDDDDWWWWWWWWWWW"
"WWWWWWWDDDDDDDDWWWWWWWWW"
"WWWWWWDDDDWWWDDDWWWWWWWW"
"WWWWWDDDDDWWWWWDDWWWWWWW"
"WWWWWWDDDDWWWWDDDWWWWWWW"
"WWWWWWWWDDDWWDDDDWWWWWWW"
"WWWWWWWWWDDDWDDDWWWWWWWW"
"WWWWWWWWWWDDWDDWWWEEEWWW"
"WWWWWWWWWWWDDDWWWWWWWWWW"
"WWWWWWWWWWWDDDWWWWWWWWWW"
"WWWWWWWWWWWWDWWWWWWWWWWW";

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
	m_Texture = StartPoint::Texture2D::Create("assets/textures/Yin.jpg");
	m_TextureAzi = StartPoint::Texture2D::Create("assets/textures/Azi.png");
	//m_SpriteSheet = StartPoint::Texture2D::Create("assets/game_test/textures/RPGpack_sheet_2X.png");
	m_SpriteSheet = StartPoint::Texture2D::Create("assets/game_test/textures/player_tilesheet.png");
	glm::vec2 coords = { 7.0f, 6.0f };
	glm::vec2 size = { 128.0f, 128.f };
	m_SpriteTexture = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1.0f, 11.0f }, { 128.0f, 128.0f }, { 1, 1 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
	//m_SubTextureMap[0] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6.0f, 11.0f }, { 128.0f, 128.0f });
	//m_SubTextureMap[1] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11.0f, 11.0f }, { 128.0f, 128.0f });
	//m_SubTextureMap[2] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 5.0f, 5.0f }, { 128.0f, 128.0f });
	m_SubTextureMap[0] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0.0f, 2.0f }, { 80.0f, 110.0f });
	m_SubTextureMap[1] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1.0f, 2.0f }, { 80.0f, 110.0f });
	m_SubTextureMap[2] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2.0f, 2.0f }, { 80.0f, 110.0f });
	m_SubTextureMap[3] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3.0f, 2.0f }, { 80.0f, 110.0f });


	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.01f, m_Particle.SizeVariation = 0.05f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(1.0f);

	StartPoint::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = StartPoint::Framebuffer::Create(fbSpec);
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
		
		m_InternalTime += timestep;
		if (m_InternalTime > 0.33)
		{
			m_InternalTime = 0.0f;
			m_SubTextureMapIndex++;
			if (m_SubTextureMapIndex == 4)
				m_SubTextureMapIndex = 0;
		}
		StartPoint::Renderer2D::DrawQuad({ 1.0f, 0.75f }, { 0.4f, 0.55f }, m_SubTextureMap[m_SubTextureMapIndex]);

		// StartPoint::Renderer2D::DrawCircle({ 0.0f, 0.0f, 0.6f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f });
		
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

	// Game scene generate.
#if 0
	m_CameraController.SetZoomLevel(7.0f);
	StartPoint::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (int y = 0; y < m_MapHeight; y++) 
	{
		for (int x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			StartPoint::Ref<StartPoint::SubTexture2D> texture;
			if (m_SubTextureMap.find(tileType) != m_SubTextureMap.end()) 
			{
				texture = m_SubTextureMap[tileType];
			}
			else
			{
				texture = m_SpriteTexture;
			}
			StartPoint::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}
	StartPoint::Renderer2D::EndScene();
#endif
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
	//uint32_t texture = m_Framebuffer->GetColorAttachmentRendererID();
	uint32_t texture = m_TextureAzi->GetRendererID();
	ImGui::Image((void*)texture, ImVec2{ 100.0f, 100.0f });
	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
