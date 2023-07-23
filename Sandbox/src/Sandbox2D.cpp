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
	m_SpriteSheet = StartPoint::Texture2D::Create("assets/game_test/textures/RPGpack_sheet_2X.png");
	glm::vec2 coords = { 7.0f, 6.0f };
	glm::vec2 size = { 128.0f, 128.f };
	m_SpriteTexture = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1.0f, 11.0f }, { 128.0f, 128.0f }, { 1, 1 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
	m_SubTextureMap['D'] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6.0f, 11.0f }, { 128.0f, 128.0f });
	m_SubTextureMap['W'] = StartPoint::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11.0f, 11.0f }, { 128.0f, 128.0f });

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.01f, m_Particle.SizeVariation = 0.05f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(1.0f);
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
	static bool dockspaceOpen = true;
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) { StartPoint::Application::Get().Close(); }
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");
	ImGui::Text("Renderer2D Stats");

	auto stats = StartPoint::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	uint32_t texture = m_TextureAzi->GetRendererID();
	ImGui::Image((void*)texture, ImVec2{ 520.0f, 520.0f });
	//ImGui::ColorEdit4("Squares' color except blue ones", glm::value_ptr(m_SquareColor));
	ImGui::End();

	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
