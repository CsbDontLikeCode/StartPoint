#pragma once
#include "StartPoint/Window.h"
#include <GLFW/glfw3.h>
#include <StartPoint/Renderer/GraphicsContext.h>

namespace StartPoint {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override
		{
			return m_Data.Width;
		}

		inline unsigned int GetHeight() const override
		{
			return m_Data.Height;
		}

		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		inline virtual void* GetNativeWindow() const
		{
			return m_Window;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData 
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}