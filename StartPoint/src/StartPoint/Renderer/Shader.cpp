#include <sppch.h>
#include "Shader.h"
#include "Renderer.h"
#include <Platform/OpenGL/OpenGLShader.h>

namespace StartPoint {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		SP_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}