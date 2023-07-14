#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
// Temporary
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
	m_SquareVA = StartPoint::VertexArray::Create();
	float vertices[4 * 3] = {
		//Position			
	   -0.5f, -0.5f, 0.0f,			//right-top corner
		0.5f, -0.5f, 0.0f,			//right-botton corner
		0.5f,  0.5f, 0.0f,			//left-botton corner
	   -0.5f,  0.5f, 0.0f			//left-top corner
	};
	StartPoint::Ref<StartPoint::VertexBuffer> squareVB;
	squareVB.reset(StartPoint::VertexBuffer::Create(vertices, sizeof(vertices)));
	StartPoint::BufferLayout squareLayout = {
		{StartPoint::ShaderDataType::Float3, "a_Position"}
	};
	squareVB->SetLayout(squareLayout);
	m_SquareVA->AddVertexBuffer(squareVB);
	unsigned int indices[6] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};
	StartPoint::Ref<StartPoint::IndexBuffer> squareIB;
	squareIB.reset(StartPoint::IndexBuffer::Create(indices, sizeof(indices)));
	m_SquareVA->SetIndexBuffer(squareIB);


	m_Shader = StartPoint::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(StartPoint::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	// Render
	StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	StartPoint::RenderCommand::Clear();

	// Unlike the camera move, transform matrix moves the specific object in the scene.
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));

	StartPoint::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);
	StartPoint::Renderer::Submit(m_SquareVA, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(0.75f)));

	StartPoint::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Squares' color except blue ones", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
