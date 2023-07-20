#include <StartPoint.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temporary
#include <Platform/OpenGL/OpenGLShader.h>

#include "Sandbox2D.h"


// -----³ÌÐòÈë¿Ú------------------
#include "StartPoint/Core/EntryPoint.h"
// -------------------------------


class ExampleLayer : public StartPoint::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = StartPoint::VertexArray::Create();
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(StartPoint::VertexBuffer::Create(vertices, sizeof(vertices)));
		StartPoint::BufferLayout layout = {
			{StartPoint::ShaderDataType::Float3, "a_Position"},
			{StartPoint::ShaderDataType::Float4, "a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(StartPoint::IndexBuffer::Create(indices, sizeof(indices)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA = StartPoint::VertexArray::Create();
		float vertices2[5 * 4] = {
			//Position			//Texture
		   -0.5f, -0.5f, 0.0f,	0.0f, 0.0f,		//right-top corner
			0.5f, -0.5f, 0.0f,	1.0f, 0.0f,		//right-botton corner
			0.5f,  0.5f, 0.0f,	1.0f, 1.0f,		//left-botton corner
		   -0.5f,  0.5f, 0.0f,	0.0f, 1.0f		//left-top corner
		};

		StartPoint::Ref<StartPoint::VertexBuffer> squareVB;
		squareVB.reset(StartPoint::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		StartPoint::BufferLayout squareLayout = {
			{StartPoint::ShaderDataType::Float3, "a_Position"},
			{StartPoint::ShaderDataType::Float2, "a_TexCoord"}
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		unsigned int indices2[6] = {
			0, 1, 2, // first triangle
			2, 3, 0  // second triangle
		};
		StartPoint::Ref<StartPoint::IndexBuffer> squareIB;
		squareIB.reset(StartPoint::IndexBuffer::Create(indices2, sizeof(indices2)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 VP_Matrix;
			uniform mat4 transform;

			out vec3 position;
			out vec4 a_color;	
			
			void main(){
				position = a_Position;
				gl_Position = VP_Matrix * transform * vec4(a_Position, 1.0);
				a_color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 position;
			in vec4 a_color;
			
			void main(){
				color = a_color;
			}
		)";

		m_Shader = StartPoint::Shader::Create("m_Shader", vertexSrc, fragmentSrc);
		m_ShaderLibrary.Add("Shader", m_Shader);

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 VP_Matrix;
			uniform mat4 transform;
			
			
			void main(){
				gl_Position = VP_Matrix * transform * vec4(a_Position, 1.0);

			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			uniform vec4 u_Color;			

			layout(location = 0) out vec4 color;

			void main(){
				color = u_Color;
			}
		)";
		m_Shader2 = StartPoint::Shader::Create("m_Shader2", vertexSrc2, fragmentSrc2);
		m_ShaderLibrary.Add("Shader2", m_Shader2);


		m_TextureShader = StartPoint::Shader::Create("assets/shaders/Texture.glsl");
		m_Texture2D = StartPoint::Texture2D::Create("assets/textures/Yin.jpg");
		//m_FrameTexture2D = StartPoint::Texture2D::Create("assets/textures/awesomeface.png");	// For texture blend test

		std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
		m_ShaderLibrary.Add("Texture", m_TextureShader);
	}

	void OnUpdate(StartPoint::Timestep timestep) override
	{
		m_CameraController.OnUpdate(timestep);
		
		StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		StartPoint::RenderCommand::Clear();

		// Unlike the camera move, transform matrix moves the specific object in the scene.
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
		glm::vec4 blueColor(0.25f, 0.25f, 1.0f, 1.0f);

		StartPoint::Renderer::BeginScene(m_CameraController.GetCamera());

		for (int i = 0; i < 2; i++) {
			if (i % 2 == 0) 
			{
				std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader2)->UploadUniformFloat4("u_Color", glm::vec4(m_SquareColor, 1.0f));
			}
			else 
			{
				std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader2)->UploadUniformFloat4("u_Color", blueColor);
			}
			glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3((float)(i + 1), 0.0f, 0.0f)) * scale;
			StartPoint::Renderer::Submit(m_SquareVA, m_Shader2, transform2);
		}

		std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_TextureShader)->UploadUniformFloat4("u_Color", blueColor);
		m_Texture2D->Bind();
		StartPoint::Renderer::Submit(m_SquareVA, m_ShaderLibrary.Get("Texture"), glm::scale(glm::mat4(1.0f), glm::vec3(0.75f)));
		//m_FrameTexture2D->Bind();																						// For texture blend test
		//StartPoint::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(0.75f)));		// For texture blend test
		
		StartPoint::Renderer::Submit(m_VertexArray, m_ShaderLibrary.Get("Shader"),glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) * scale);

		StartPoint::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Squares' color except blue ones", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(StartPoint::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}
private:
	//Ref is a kind of template use based on std::shared_ptr<>.
	//Besides, there is a template use of std::unique_ptr<> named Scope.
	//The defination is in "Core.h" file.
	StartPoint::ShaderLibrary m_ShaderLibrary;
	StartPoint::Ref<StartPoint::Shader> m_Shader;
	StartPoint::Ref<StartPoint::Shader> m_Shader2;
	StartPoint::Ref<StartPoint::Shader> m_TextureShader;
	StartPoint::Ref<StartPoint::VertexArray> m_VertexArray;
	StartPoint::Ref<StartPoint::VertexArray> m_SquareVA;
	StartPoint::Ref<StartPoint::VertexBuffer> m_VertexBuffer;
	StartPoint::Ref<StartPoint::IndexBuffer> m_IndexBuffer;
	StartPoint::Ref<StartPoint::Texture2D> m_Texture2D;
	//StartPoint::Ref<StartPoint::Texture2D> m_FrameTexture2D;	// For texture blend test

	//StartPoint::OrthegraphicCamera m_Camera;
	StartPoint::OrthegraphicCameraController m_CameraController;
	
	glm::vec3 m_SquareColor = glm::vec3(0.3f, 0.6f, 0.9f);
};

class Sandbox : public StartPoint::Application {

public:
	Sandbox() {
		// PushLayer(new ExampleLayer());
		PushOverlay(new Sandbox2D());
	}

	~Sandbox() {

	}

};

StartPoint::Application* StartPoint::CreateApplication() {
	return new Sandbox();
}
