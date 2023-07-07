#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "StartPoint/Core/Timestep.h"

namespace StartPoint {
	class SP_API Application
	{
	private:
		static Application* s_Instance;		// Application instance
		bool m_Running = true;				// Application running state

		LayerStack m_LayerStack;			// Layer stack
		std::unique_ptr<Window> m_Window;	// Window object
		ImGuiLayer* m_ImGuiLayer;			// ImGui object
		Timestep* m_Timestep;				// Timer object
		float m_LastFrameTime = 0.0f;				// Record last frame's time to compute the deltatime
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
	};

	// Set by user
	Application* createApplication();
}
