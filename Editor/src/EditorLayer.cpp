#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace StartPoint 
{

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true) {}

	void EditorLayer::OnAttach()
	{
		m_CameraController.SetZoomLevel(1.0f);

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		auto square2 = m_ActiveScene->CreateEntity("Square2");
		square2.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		m_SquareEntity2 = square2;
		auto square = m_ActiveScene->CreateEntity("Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Primary Camera");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_CameraEntity2 = m_ActiveScene->CreateEntity("Secondary Camera");
		auto& cc = m_CameraEntity2.AddComponent<CameraComponent>();
		cc.Primary = false;

		// Scripts.
		class CameraController : public ScriptableEntity 
		{
		public:
			void OnCreate() 
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}
			// ====================================================================================================
			void OnDestroy()
			{
			}
			// ====================================================================================================
			void OnUpdate(Timestep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float cameraSpeed = 5.0f;
				// ------------------------------------------------------------------------------------------------
				if (Input::IsKeyPressed(KeyCode::A))
					translation.x -= cameraSpeed * ts;
				if (Input::IsKeyPressed(KeyCode::D))
					translation.x += cameraSpeed * ts;
				if (Input::IsKeyPressed(KeyCode::W))
					translation.y += cameraSpeed * ts;
				if (Input::IsKeyPressed(KeyCode::S))
					translation.y -= cameraSpeed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_CameraEntity2.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		m_SceneHierachyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep timestep)
	{
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			if (!m_CameraEntity.GetComponent<CameraComponent>().FixedAspectRatio)
			{
				m_CameraEntity.GetComponent<CameraComponent>().Camera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			}
			
		}

		// Update
		if(m_ViewportFocused)
			m_CameraController.OnUpdate(timestep);

		// Render preparation.
		Renderer2D::ResetStats();
		// auto stats = Renderer2D::GetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.46f, 0.84f, 0.91f, 1.0f });
		RenderCommand::Clear();

		// Render the scene.
		m_ActiveScene->OnUpdate(timestep);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 320.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) { Application::Get().Close(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		m_SceneHierachyPanel.OnImGuiRender();

		// Usage of ImGui.
		ImGui::Begin("Render Status");
		ImGui::Text("Renderer2D Stats");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Rendering Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		glViewport(0, 0, viewportPanelSize.x, viewportPanelSize.y);
		uint32_t texture = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		//ImGui::Image((void*)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });

		ImGui::End();	// Rendering Viewport End.
		ImGui::PopStyleVar();

		ImGui::End();	// Docking End.
	}

	void EditorLayer::OnEvent(Event& event)
	{
		if (m_ViewportHovered) 
		{
			m_CameraController.OnEvent(event);
		}
	}

}
