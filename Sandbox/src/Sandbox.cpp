#include <iostream>
#include <StartPoint.h>
#include <imgui.h>

class ExampleLayer : public StartPoint::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.5f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(StartPoint::VertexArray::Create());
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


		m_SquareVA.reset(StartPoint::VertexArray::Create());
		float vertices2[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,   // right-top corner
			0.5f, -0.5f, 0.0f,  // right-botton corner
			0.5f,  0.5f, 0.0f, // left-botton corner
		   -0.5f,  0.5f, 0.0f   // left-top corner
		};

		std::shared_ptr<StartPoint::VertexBuffer> squareVB;
		squareVB.reset(StartPoint::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		StartPoint::BufferLayout squareLayout = {
			{StartPoint::ShaderDataType::Float3, "a_Position"}
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		unsigned int indices2[6] = {
			0, 1, 2, // first triangle
			2, 3, 0  // second triangle
		};
		std::shared_ptr<StartPoint::IndexBuffer> squareIB;
		squareIB.reset(StartPoint::IndexBuffer::Create(indices2, sizeof(indices2)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 VP_Matrix;

			out vec3 position;
			out vec4 a_color;	
			
			void main(){
				position = a_Position;
				gl_Position = VP_Matrix * vec4(a_Position, 1.0);
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
		m_Shader.reset(new StartPoint::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 VP_Matrix;
			
			void main(){
				gl_Position = VP_Matrix * vec4(a_Position, 1.0);

			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			void main(){
				color = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";
		m_Shader2.reset(new StartPoint::Shader(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(StartPoint::Timestep timestep) override
	{
		// Explanation: the class "Timestep" has overrided the float conversion.
		// When assign the instance of class "Timestep" to a float type variable, the 
		// instance will automatically return the instance's member properties-"m_Time".
		float deltatime = timestep;
		SP_INFO("Deltatime:{0}.", deltatime);
		// Move the camera(left and right)
		if (StartPoint::Input::IsKeyPressed(SP_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltatime;
		}
		else if (StartPoint::Input::IsKeyPressed(SP_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltatime;
		}
		// Move the camera(up and down)
		if (StartPoint::Input::IsKeyPressed(SP_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltatime;
		}
		else if (StartPoint::Input::IsKeyPressed(SP_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltatime;
		}
		// Rotate the camera
		if (StartPoint::Input::IsKeyPressed(SP_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * deltatime;
		}
		else if (StartPoint::Input::IsKeyPressed(SP_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * deltatime;
		}

		StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		StartPoint::RenderCommand::Clear();

		// Change the position of the camera
		m_Camera.SetPosition(m_CameraPosition);
		// Rotate the angle of view
		m_Camera.SetRotation(m_CameraRotation);

		StartPoint::Renderer::BeginScene(m_Camera);
		StartPoint::Renderer::Submit(m_SquareVA, m_Shader2);
		StartPoint::Renderer::Submit(m_VertexArray, m_Shader);
		StartPoint::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(StartPoint::Event& event) override
	{

	}
private:
	std::shared_ptr<StartPoint::Shader> m_Shader;
	std::shared_ptr<StartPoint::Shader> m_Shader2;
	std::shared_ptr<StartPoint::VertexArray> m_VertexArray;
	std::shared_ptr<StartPoint::VertexArray> m_SquareVA;
	std::shared_ptr<StartPoint::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<StartPoint::IndexBuffer> m_IndexBuffer;

	StartPoint::OrthegraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;					// Camera's current position, it will be set in constructor
	float m_CameraMoveSpeed = 2.0f;				// Camera's move speed for "¡ü" "¡ý" "¡û" "¡ú"
	float m_CameraRotation = 0.0f;				// Camera's current rotation
	float m_CameraRotationSpeed = 15.0f;		// Camera's rotate speed
};

class Sandbox : public StartPoint::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		// PushOverlay(new StartPoint::ImGuiLayer());
	}

	~Sandbox() {

	}

};

StartPoint::Application* StartPoint::createApplication() {
	return new Sandbox();
}
