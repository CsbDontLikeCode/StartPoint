#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include <StartPoint/Events/ApplicationEvent.h>
#include <StartPoint/ImGui/ImGuiLayer.h>
#include "StartPoint/Core/Timestep.h"

namespace StartPoint {
	class SP_API Application
	{
	private:
		static Application* s_Instance;		// Application instance
		bool m_Running = true;				// Application running state
		bool m_Minimized = false;			// Application minimized state

		LayerStack m_LayerStack;			// Layer stack
		std::unique_ptr<Window> m_Window;	// Window object
		ImGuiLayer* m_ImGuiLayer;			// ImGui object
		Timestep* m_Timestep;				// Timer object
		float m_LastFrameTime = 0.0f;				// Record last frame's time to compute the deltatime
	public:
		Application(const std::string& name = "StartPoint Engine");
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// Set by user
	Application* CreateApplication();
}