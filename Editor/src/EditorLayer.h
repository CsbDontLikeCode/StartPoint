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
		void SaveSceneAs();
	private:
		OrthegraphicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		// Scene
		Ref<Scene> m_ActiveScene;
		// EditorCamera
		EditorCamera m_EditorCamera;

		int m_GizmoType = -1;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Entity m_HoveredEntity;

		SceneHierachyPanel m_SceneHierachyPanel;
		ContextBrowserPanel m_ContextBrowserPanel;
	};
}
