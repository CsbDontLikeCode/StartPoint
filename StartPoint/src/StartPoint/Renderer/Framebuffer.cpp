#include <sppch.h>

#include "Framebuffer.h"
#include <Platform/OpenGL/OpenGLFramebuffer.h>
#include <StartPoint/Renderer/Renderer.h>

namespace StartPoint 
{

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			SP_CORE_ASSERT(false, "RendererAPI None is not suppurted"); return nullptr;
		case RendererAPI::API::OpenGL:			return CreateRef<OpenGLFramebuffer>(spec);
		}

		SP_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}