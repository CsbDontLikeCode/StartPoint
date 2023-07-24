#pragma once
#include <StartPoint.h>

#include <glm/gtc/matrix_transform.hpp>

#include "ParticleSystem.h"


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
		OrthegraphicCameraController m_CameraController;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_Shader;

		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_TextureAzi;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_SpriteTexture;
		Ref<Framebuffer> m_Framebuffer;

		glm::vec4 m_SquareColor = glm::vec4(0.3f, 0.6f, 0.9f, 1.0f);

		ParticleSystem m_ParticleSystem;
		ParticleProps m_Particle;

		unsigned int m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> m_SubTextureMap;
	};
}
