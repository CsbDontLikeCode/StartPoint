#pragma once

#include <StartPoint/Core/Core.h>

namespace StartPoint 
{
	struct FramebufferSpecification
	{
		unsigned int Width, Height;
		unsigned int Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual unsigned int GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		 static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};

}
