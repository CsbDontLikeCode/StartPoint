#include <StartPoint.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temporary
#include <Platform/OpenGL/OpenGLShader.h>


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

		StartPoint::Ref<StartPoint::VertexBuffer> squareVB;
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
		m_Shader.reset(StartPoint::Shader::Create(vertexSrc, fragmentSrc));

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
		m_Shader2.reset(StartPoint::Shader::Create(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(StartPoint::Timestep timestep) override
	{
		// Explanation: the class "Timestep" has overrided the float conversion.
		// When assign the instance of class "Timestep" to a float type variable, the 
		// instance will automatically return the instance's member properties-"m_Time".
		float deltatime = timestep;

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

		// Unlike the camera move, transform matrix moves the specific object in the scene.
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
		glm::vec4 blueColor(0.25f, 0.25f, 1.0f, 1.0f);

		StartPoint::Renderer::BeginScene(m_Camera);
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 0) 
			{
				std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader2)->UploadUniformFloat4("u_Color", glm::vec4(m_SquareColor, 1.0f));
			}
			else 
			{
				std::dynamic_pointer_cast<StartPoint::OpenGLShader>(m_Shader2)->UploadUniformFloat4("u_Color", blueColor);
			}
			glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), glm::vec3((float)i, 0.0f, 0.0f)) * scale;
			StartPoint::Renderer::Submit(m_SquareVA, m_Shader2, transform2);
		}
		StartPoint::Renderer::Submit(m_VertexArray, m_Shader);
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

	}
private:
	//Ref is a kind of template use based on std::shared_ptr<>.
	//Besides, there is a template use of std::unique_ptr<> named Scope.
	//The defination is in "Core.h" file.
	StartPoint::Ref<StartPoint::Shader> m_Shader;
	//std::shared_ptr<StartPoint::Shader> m_Shader;
	StartPoint::Ref<StartPoint::Shader> m_Shader2;
	//std::shared_ptr<StartPoint::Shader> m_Shader2;
	StartPoint::Ref<StartPoint::VertexArray> m_VertexArray;
	//std::shared_ptr<StartPoint::VertexArray> m_VertexArray;
	StartPoint::Ref<StartPoint::VertexArray> m_SquareVA;
	//std::shared_ptr<StartPoint::VertexArray> m_SquareVA;
	StartPoint::Ref<StartPoint::VertexBuffer> m_VertexBuffer;
	//std::shared_ptr<StartPoint::VertexBuffer> m_VertexBuffer;
	StartPoint::Ref<StartPoint::IndexBuffer> m_IndexBuffer;
	//std::shared_ptr<StartPoint::IndexBuffer> m_IndexBuffer;

	StartPoint::OrthegraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;					// Camera's current position, it will be set in constructor
	float m_CameraMoveSpeed = 2.0f;				// Camera's move speed for "¡ü" "¡ý" "¡û" "¡ú"
	float m_CameraRotation = 0.0f;				// Camera's current rotation
	float m_CameraRotationSpeed = 15.0f;		// Camera's rotate speed
	glm::vec3 m_SquareColor = glm::vec3(0.3f, 0.6f, 0.9f);
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
