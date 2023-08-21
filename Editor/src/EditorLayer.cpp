#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <StartPoint/Utils/PlatformUtils.h>

#include <ImGuizmo/ImGuizmo.h>

#include <StartPoint/Math/Math.h>

#include <filesystem>

namespace StartPoint 
{
	extern const std::filesystem::path g_AssetPath;

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true) {}

	void EditorLayer::OnAttach()
	{
		m_CameraController.SetZoomLevel(1.0f);

		m_IconPlay = Texture2D::Create("Resources/Icons/Toolbar/Play.png");
		m_IconStop = Texture2D::Create("Resources/Icons/Toolbar/stop.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		m_EditorCamera = EditorCamera(30.0f, 1.788f, 0.1f, 1000.0f);

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
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		if (m_ViewportFocused || m_ViewportHovered)
		{
			m_CameraController.OnUpdate(timestep);
			m_EditorCamera.OnUpdate(timestep);
		}

		// Render preparation.
		Renderer2D::ResetStats();
		// auto stats = Renderer2D::GetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.46f, 0.84f, 0.91f, 1.0f });
		RenderCommand::Clear();

		m_Framebuffer->ClearAttachment(1, -1);

		switch (m_SceneState)
		{
			case SceneState::Edit:
			{
				//if (m_ViewportFocused)
				//{
				//	m_CameraController.OnUpdate(timestep);
				//}
				m_SceneHierachyPanel.SetAddComponentState(true);
				m_ActiveScene->OnUpdateEditor(timestep, m_EditorCamera);
				break;
			}
			case SceneState::Play:
			{
				m_SceneHierachyPanel.SetAddComponentState(false);
				m_ActiveScene->OnUpdateRuntime(timestep);
				break;
			}
		}

		// Render the scene.
		//m_ActiveScene->OnUpdateRuntime(timestep);
		//m_ActiveScene->OnUpdateEditor(timestep, m_EditorCamera);

		auto[mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) 
		{
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			if (pixelData == -1)
			{
				m_HoveredEntity = {};
			}
			else
			{
				m_HoveredEntity = { entt::entity(pixelData), m_ActiveScene.get()};
			}
		}
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
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					NewScene();
				}
				if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
				{
					OpenScene();
				}
				if (ImGui::MenuItem("Scene Save As", "Ctrl+Shift+S"))
				{
					SaveSceneAs();
				}
				if (ImGui::MenuItem("Exit")) { Application::Get().Close(); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Shift"))
			{
				if (ImGui::MenuItem("Translation"))
				{
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				}
				if (ImGui::MenuItem("Rotation"))
				{
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				}
				if (ImGui::MenuItem("Scale"))
				{
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				}
				if (ImGui::MenuItem("None"))
				{
					m_GizmoType = -1;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		m_SceneHierachyPanel.OnImGuiRender();
		m_ContextBrowserPanel.OnImGuiRender();

		// Usage of ImGui.
		ImGui::Begin("Render Status");
		std::string entityName = "None";
		if(m_HoveredEntity)
		{
			entityName = m_HoveredEntity.GetComponent<TagComponent>().Tag;
		}
		ImGui::Text("Entity: %s", entityName.c_str());

		ImGui::Text("Renderer2D Stats");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Rendering Viewport", NULL, ImGuiWindowFlags_NoTitleBar);
		
		// The point ImGui starts to draw context.
		auto viewportOffset = ImGui::GetCursorPos();

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		//Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		glViewport(0, 0, viewportPanelSize.x, viewportPanelSize.y);
		uint32_t texture = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		//ImGui::Image((void*)texture, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });

		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;
		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				OpenScene(std::filesystem::path(g_AssetPath) / path);
			}
			ImGui::EndDragDropTarget();
		}


		// Gizmos
		Entity selectEntity = m_SceneHierachyPanel.GetSelectedEntity();
		if (selectEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float wWidth = (float)ImGui::GetWindowWidth();
			float wHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, wWidth, wHeight);
			// Runtime Camera
			//auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			//const glm::mat4& cameraProjection = camera.GetProjection();
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());
			// Editor Camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();
			// Entity
			auto& tc = selectEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();
			// Snapping
			bool snap = Input::IsKeyPressed(KeyCode::LeftControl);
			float snapValue = 0.5f;
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
			{
				snapValue = 45.0f;
			}
			float snapValues[3] = { snapValue, snapValue, snapValue };
			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);
			// ----------------------------------------------------------------------------------------------------
			if (ImGuizmo::IsUsing)
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();	// Rendering Viewport End.
		ImGui::PopStyleVar();

		UI_Toolbar();

		ImGui::End();	// Docking End.
	}

	void EditorLayer::UI_Toolbar()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		auto& colors = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		const auto& buttonActive = colors[ImGuiCol_ButtonActive];
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

		ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar 
			| ImGuiWindowFlags_NoScrollWithMouse);
		float size = ImGui::GetWindowHeight() - 4.0f;
		Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
		ImGui::SetCursorPosX((ImGui::GetContentRegionMax().x * 0.5f) - (size * 0.5f));
		if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
		{
			if (m_SceneState == SceneState::Edit)
			{
				OnScenePlay();
			}
			else if (m_SceneState == SceneState::Play)
			{
				OnSceneStop();
			}
		}
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	void EditorLayer::OnScenePlay()
	{
		m_SceneState = SceneState::Play;

		m_RuntimeScene = Scene::Copy(m_EditorScene);

		m_ActiveScene = m_RuntimeScene;
		m_ActiveScene->OnRuntimeStart();
	}

	void EditorLayer::OnSceneStop()
	{
		m_SceneState = SceneState::Edit;
		m_ActiveScene->OnRuntimeStop();
		m_RuntimeScene = nullptr;

		m_ActiveScene = m_EditorScene;
	}

	void EditorLayer::OnDuplicateEntity()
	{
		if (m_SceneState != SceneState::Edit)
			return;

		Entity selectedEntity = m_SceneHierachyPanel.GetSelectedEntity();
		if (selectedEntity)
		{
			m_EditorScene->DuplicateEntity(selectedEntity);
		}
	}

	void EditorLayer::OnEvent(Event& event)
	{
		if (m_ViewportHovered) 
		{
			//m_CameraController.OnEvent(event);
			m_EditorCamera.OnEvent(event);
		}

		

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(SP_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(SP_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(KeyCode::LeftControl) || Input::IsKeyPressed(KeyCode::RightControl);
		bool shift = Input::IsKeyPressed(KeyCode::LeftShift) || Input::IsKeyPressed(KeyCode::LeftShift);

		switch (e.GetKeyCode())
		{
			case KeyCode::N:
			{

				if (control && shift)
				{
					NewScene();
				}
			}
			case KeyCode::O:
			{
				if (control && shift)
				{
					OpenScene();
				}
				break;
			}
			case KeyCode::S:
			{
				if (control)
				{
					if(shift)
						SaveSceneAs();
					else
						SaveScene();
				}
				break;
			}

			case KeyCode::D:
			{
				if (control)
				{
					OnDuplicateEntity();
				}
				break;
			}


			case KeyCode::Q:
				if(m_ViewportFocused || m_ViewportHovered)
					m_GizmoType = -1;
				break;
			case KeyCode::W:
				if (m_ViewportFocused || m_ViewportHovered)
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case KeyCode::E:
				if (m_ViewportFocused || m_ViewportHovered)
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			case KeyCode::R:
				if (m_ViewportFocused || m_ViewportHovered)
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == MouseCode::ButtonLeft)
		{
			if(m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(KeyCode::LeftAlt))
				m_SceneHierachyPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierachyPanel.SetContext(m_ActiveScene);
		m_EditorScenePath = std::filesystem::path();
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("StartPoint Scene (*.sp)\0*.sp\0");
		if (!filepath.empty())
		{
			//m_ActiveScene = CreateRef<Scene>();
			//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//m_SceneHierachyPanel.SetContext(m_ActiveScene);
			//SceneSerializer serializer(m_ActiveScene);
			//serializer.Deserialize(filepath);
			OpenScene(filepath);
		}	
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (m_SceneState != SceneState::Edit)
			OnSceneStop();

		Ref<Scene> newScene = CreateRef<Scene>();
		newScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		SceneSerializer serializer(newScene);
		serializer.Deserialize(path.string());
		m_SceneHierachyPanel.SetContext(newScene);
		
		m_EditorScene = newScene;
		m_EditorScenePath = path;
		m_ActiveScene = m_EditorScene;

		//m_ActiveScene = CreateRef<Scene>();
		//m_EditorScene = m_ActiveScene;
		//m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		//m_SceneHierachyPanel.SetContext(m_ActiveScene);
		//SceneSerializer serializer(m_ActiveScene);
		//serializer.Deserialize(path.string());
	}

	void EditorLayer::SaveScene()
	{
		if (!m_EditorScenePath.empty())
		{
			SceneSerializer serializer(m_EditorScene);
			serializer.Serialize(m_EditorScenePath.string());
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("StartPoint Scene (*.sp)\0*.sp\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);

			m_EditorScenePath = filepath;
		}
	}

	void EditorLayer::SerializeScene(Ref<Scene> scene, const std::filesystem::path& path)
	{
		SceneSerializer serializer(scene);
		serializer.Serialize(path.string());
	}

}
