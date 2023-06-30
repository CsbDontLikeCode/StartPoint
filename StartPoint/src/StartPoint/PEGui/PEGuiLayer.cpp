#include "sppch.h"
#include "PEGuiLayer.h"

//#include <imgui/imgui.h>
//#include <imgui/backends/imgui_impl_glfw.h>
//#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../Application.h" 

namespace StartPoint {
	PEGuiLayer::PEGuiLayer()
		: Layer("PEGuiLayer") {}

	PEGuiLayer::~PEGuiLayer() {}

	void PEGuiLayer::OnAttach()
	{
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO();
		//(void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		//// ����ImGui��ʽ
		//ImGui::StyleColorsDark();

		//ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		//Application& app = Application::Get();
		//GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//ImGui_ImplGlfw_InitForOpenGL(window, true);

		//ImGui_ImplOpenGL3_Init("#version 410");
	}

	void PEGuiLayer::OnDetach()
	{

	}

	void PEGuiLayer::OnUpdate()
	{
		//ImGuiIO& io = ImGui::GetIO();
		//Application& app = Application::Get();
		//io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//float time = (float)glfwGetTime();
		//io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		//m_Time = time;

		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui::NewFrame();

		//static bool show = true;
		//ImGui::ShowDemoWindow(&show);

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}