#pragma once
#include <glm/glm.hpp>

namespace StartPoint 
{

	class OrthegraphicCamera 
	{
	public:
		OrthegraphicCamera(float left, float right, float bottom, float top);

		void SetRotation(float rotation) 
		{ 
			m_Rotation = rotation;
			// Every time camera attribution changes, recalculate the camera's view Matrix.
			RecalculateViewMatrix();
		}
		const float GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3 position) 
		{ 
			m_Position = position; 
			// Every time camera attribution changes, recalculate the camera's view Matrix.
			RecalculateViewMatrix();
		}
		const glm::vec3& GetPosition() const { return m_Position; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}