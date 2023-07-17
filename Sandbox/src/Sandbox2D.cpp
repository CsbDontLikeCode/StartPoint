#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer 
{
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
public:
	Timer(const char* name, Fn&& func) 
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
		{
			Stop();
		}
	}

	void Stop() 
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;
		float duration = (end - start) * 0.001f;

		//std::cout << m_Name <<"------Duration:" << duration << "ms" << std::endl;
		m_Func({ m_Name, duration });
	}
};

#define PROFILE_SCOPE(name) Timer timer(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
//#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true){}

void Sandbox2D::OnAttach()
{
	m_Texture = StartPoint::Texture2D::Create("assets/textures/Yin.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(StartPoint::Timestep timestep)
{
	// Performance testing, test this function's time consuming.
	//Timer timer("Sandbox2D::OnUpdate", [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
	 PROFILE_SCOPE("Sandbox2D::OnUpdate");

	m_CameraController.OnUpdate(timestep);

	// Render
	StartPoint::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	StartPoint::RenderCommand::Clear();

	// Unlike the camera move, transform matrix moves the specific object in the scene.
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));

	StartPoint::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	// Position,Size and Color
	StartPoint::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.8f, 0.2f, 0.15f, 1.0f});
	StartPoint::Renderer2D::DrawQuad({ 1.0f, 0.5f}, { 0.5f, 0.5f }, {0.1f, 0.1f, 0.85f, 1.0f});
	StartPoint::Renderer2D::DrawQuad({ -0.5f, 0.5f, -0.5f}, { 5.0f, 5.0f }, m_Texture);
	
	StartPoint::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Squares' color except blue ones", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults) 
	{
		char label[50];
		strcpy_s(label, "%.3fms   ");
		strcat_s(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(StartPoint::Event& event)
{
	m_CameraController.OnEvent(event);
}
