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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual unsigned int GetColorAttachmentRendererID(uint32_t index = 0) const override { return m_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererId;
		//uint32_t m_ColorAttachment;
		//uint32_t m_DepthAttachment;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector <uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};

}