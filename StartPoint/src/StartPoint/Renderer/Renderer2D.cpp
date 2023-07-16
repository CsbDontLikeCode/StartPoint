#include <sppch.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"


namespace StartPoint 
{

	struct Renderer2DStorage 
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> CommonShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();
		float vertices[4 * 5] = {
			//Position			
		   -0.5f, -0.5f, 0.0f,	0.0f, 0.0f,		//right-top corner
			0.5f, -0.5f, 0.0f,	1.0f, 0.0f,		//right-botton corner
			0.5f,  0.5f, 0.0f,	1.0f, 1.0f,		//left-botton corner
		   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f		//left-top corner
		};
		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"}, 
			{ShaderDataType::Float2, "a_TexCoord"}
		};
		squareVB->SetLayout(squareLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
		unsigned int indices[6] = {
			0, 1, 2, // first triangle
			2, 3, 0  // second triangle
		};
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(indices, sizeof(indices)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t wihteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&wihteTextureData, sizeof(uint32_t));


		s_Data->CommonShader = Shader::Create("assets/shaders/CommonShader.glsl");
		//s_Data->CommonShader = Shader::Create("assets/shaders/FlatColorShader.glsl");
		s_Data->CommonShader->Bind();
		s_Data->CommonShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const OrthegraphicCamera& camera)
	{
		s_Data->CommonShader->Bind();
		s_Data->CommonShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->CommonShader->SetFloat4("u_Color", color);
		s_Data->CommonShader->SetFloat("u_TexScale", 1.0f);
		// Bind white texture
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data->CommonShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->CommonShader->SetFloat4("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		s_Data->CommonShader->SetFloat("u_TexScale", 2.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		s_Data->CommonShader->SetMat4("u_Transform", transform);

		texture->Bind();

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}