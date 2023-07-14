#pragma once

#include <StartPoint/Renderer/OrthegraphicCamera.h>

namespace StartPoint 
{

	class Renderer2D 
	{
	public:
		// Init and Shutdown will be equivalent to constructor and destructor
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthegraphicCamera& camera);
		static void EndScene();

		// Draw geometric shapes
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};

}