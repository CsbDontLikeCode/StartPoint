#pragma once
#include <StartPoint/Renderer/OrthegraphicCamera.h>
#include <StartPoint/Core/Timestep.h>
#include <StartPoint/Events/ApplicationEvent.h>
#include <StartPoint/Events/MouseEvent.h>

namespace StartPoint
{
	struct OrthegraphicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return  Top - Bottom; }
	};

	class OrthegraphicCameraController
	{
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthegraphicCameraBounds m_CameraBounds;
		OrthegraphicCamera m_Camera;

		bool m_Rotation;
		
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 2.5f;
		float m_CameraRotationSpeed = 15.0f;
	public:
		OrthegraphicCameraController(float aspectRatio, bool rotation = false);
		OrthegraphicCamera& GetCamera();
		//const OrthegraphicCamera& const GetCamera();

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);

		const OrthegraphicCameraBounds& GetBounds() const { return m_CameraBounds;  }
	private:
		bool OnMouseScorlled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	};

}