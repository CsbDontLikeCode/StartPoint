#pragma once
#include <StartPoint.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Panels/SceneHierachyPanel.h"


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
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		OrthegraphicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		// Scene
		Ref<Scene> m_ActiveScene;

		int m_GizmoType = -1;

		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		SceneHierachyPanel m_SceneHierachyPanel;
	};
}
