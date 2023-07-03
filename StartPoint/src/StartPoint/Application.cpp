#include "sppch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <glad/glad.h>
#include "Input.h"
#include <GLFW/glfw3.h>


namespace StartPoint {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) 
	{
		switch (type) 
		{
		case ShaderDataType::Float:				return GL_FLOAT;
		case ShaderDataType::Float2:			return GL_FLOAT;
		case ShaderDataType::Float3:			return GL_FLOAT;
		case ShaderDataType::Float4:			return GL_FLOAT;
		case ShaderDataType::Mat3:				return GL_FLOAT;
		case ShaderDataType::Mat4:				return GL_FLOAT;
		case ShaderDataType::Int:				return GL_INT;
		case ShaderDataType::Int2:				return GL_INT;
		case ShaderDataType::Int3:				return GL_INT;
		case ShaderDataType::Int4:				return GL_INT;
		case ShaderDataType::Bool:				return GL_BOOL;
		}

		SP_CORE_ASSERT(false, "Unknown ShaderDataType~");
		return 0;
	}

	Application::Application()
	{
		SP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		// Index Buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// Set action scope
		// "layout" will be deleted automatically out of action scope
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		unsigned int index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& i : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				i.GetElementCount(), 
				ShaderDataTypeToOpenGLBaseType(i.Type), 
				i.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(),
				(const void*)i.Offset);
			index++;
		}

		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 position;
			out vec4 a_color;	
			
			void main(){
				position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

		for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() 
	{
		while(m_Running)
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}