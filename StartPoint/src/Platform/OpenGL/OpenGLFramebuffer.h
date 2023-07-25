#pragma once
#include <StartPoint/Renderer/Framebuffer.h>

namespace StartPoint 
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

	    virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(unsigned int width, unsigned int height) override;

		virtual unsigned int GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererId;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};

}