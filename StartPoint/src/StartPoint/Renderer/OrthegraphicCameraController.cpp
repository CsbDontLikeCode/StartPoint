#include <sppch.h>
#include "OrthegraphicCameraController.h"
#include <StartPoint/Core/Input.h>
#include <StartPoint/Core/KeyCodes.h>

namespace StartPoint
{

	OrthegraphicCameraController::OrthegraphicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_CameraBounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera (m_CameraBounds.Left, m_CameraBounds.Right, m_CameraBounds.Bottom, m_CameraBounds.Top), m_Rotation(rotation)
	{}

	void OrthegraphicCameraController::OnUpdate(Timestep timestep)
	{
		// Explanation: the class "Timestep" has overrided the float conversion.
		// When assign the instance of class "Timestep" to a float type variable, the 
		// instance will automatically return the instance's member properties-"m_Time".
		float deltatime = timestep;

		// Move the camera(left and right)
		if (Input::IsKeyPressed(SP_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltatime;
		}
		else if (Input::IsKeyPressed(SP_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltatime;
		}
		// Move the camera(up and down)
		if (Input::IsKeyPressed(SP_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltatime;
		}
		else if (Input::IsKeyPressed(SP_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltatime;
		}
		m_Camera.SetPosition(m_CameraPosition);

		// Rotate the camera
		if (m_Rotation) 
		{
			if (Input::IsKeyPressed(SP_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * deltatime;
			}
			else if (Input::IsKeyPressed(SP_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * deltatime;
			}
		}
		m_Camera.SetRotation(m_CameraRotation);
		m_CameraMoveSpeed = m_ZoomLevel;
	}

	void OrthegraphicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SP_BIND_ENENT_FN(OrthegraphicCameraController::OnMouseScorlled));
		dispatcher.Dispatch<WindowResizeEvent>(SP_BIND_ENENT_FN(OrthegraphicCameraController::OnWindowResized));
	}

	void OrthegraphicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		CalculateView();

	}

	void OrthegraphicCameraController::CalculateView()
	{
		m_CameraBounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthegraphicCameraController::OnMouseScorlled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.05f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}

	OrthegraphicCamera& OrthegraphicCameraController::GetCamera()
	{
		return m_Camera;
	}

	bool OrthegraphicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CalculateView();
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}