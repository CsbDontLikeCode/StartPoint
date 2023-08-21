#pragma once
#include <StartPoint.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Panels/SceneHierachyPanel.h"
#include "Panels/ContextBrowserPanel.h"

#include "StartPoint/Renderer/EditorCamera.h"


namespace StartPoint 
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		// UI Panels
		void UI_Toolbar();
		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();
	private:
		OrthegraphicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		// Scene
		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene, m_RuntimeScene;
		std::filesystem::path m_EditorScenePath;
		// EditorCamera
		EditorCamera m_EditorCamera;

		int m_GizmoType = -1;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Entity m_HoveredEntity;

		SceneHierachyPanel m_SceneHierachyPanel;
		ContextBrowserPanel m_ContextBrowserPanel;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};

		SceneState m_SceneState = SceneState::Edit;
		Ref<Texture2D> m_IconPlay, m_IconStop;
	};
}
