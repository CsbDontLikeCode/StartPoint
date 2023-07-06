#pragma once
#include "RendererAPI.h"
#include "OrthegraphicCamera.h"
#include "Shader.h"

namespace StartPoint {

	class Renderer {
	public:
		static void BeginScene(OrthegraphicCamera& camera);
		static void EndScene();
		
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader> shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}