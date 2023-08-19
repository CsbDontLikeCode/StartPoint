#pragma once
#include <StartPoint/Renderer/Texture.h>
#include <glad/glad.h>

namespace StartPoint 
{

	class OpenGLTextur2D : public Texture2D 
	{
	public:
		OpenGLTextur2D(const std::string& path);
		OpenGLTextur2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTextur2D();

		virtual unsigned int GetWidth() override { return m_Width; }
		virtual unsigned int GetHeight() override { return m_Height; }
		virtual unsigned int GetRendererID() const override { return m_RendererID; }
		virtual const std::string GetTexturePath() const override { return m_Path; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(unsigned int slot) const override;

		virtual bool operator==(const Texture& other) const override 
		{ 
			return m_RendererID == ((OpenGLTextur2D&)other).m_RendererID;
		};
	private:
		std::string m_Path;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}