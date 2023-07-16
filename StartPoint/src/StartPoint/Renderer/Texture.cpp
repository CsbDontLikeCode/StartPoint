#include <sppch.h>
#include "Texture.h"
#include <StartPoint/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLTexture.h>

namespace StartPoint 
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLTextur2D>(width, height);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLTextur2D>(path);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

}

