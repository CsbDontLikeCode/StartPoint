#pragma once
#include <StartPoint/Renderer/GraphicsContext.h>
#include <StartPoint/Core.h>

struct GLFWwindow;

namespace StartPoint {

	class OpenGLContext : public GraphicsContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;

		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}