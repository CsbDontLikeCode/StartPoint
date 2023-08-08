#include <sppch.h>
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <StartPoint/Core/Log.h>

namespace StartPoint {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SP_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void OpenGLContext::init()
	{
		SP_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SP_CORE_ASSERT(status, "Failed to initialize GLAD!");

		std::cout << "OpenGL Renderer:" << glGetString(GL_VENDOR) << "-" << glGetString(GL_RENDERER) << std::endl;
	}

	void OpenGLContext::SwapBuffers()
	{
		SP_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
