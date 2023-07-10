#pragma once
#include <StartPoint/Renderer/Texture.h>

namespace StartPoint 
{

	class OpenGLTextur2D : public Texture2D 
	{
	public:
		OpenGLTextur2D(const std::string& path);
		virtual ~OpenGLTextur2D();

		virtual unsigned int GetWidth() override { return m_Width; }
		virtual unsigned int GetHeight() override { return m_Height; }

		virtual void Bind(unsigned int slot) const override;
	private:
		std::string m_Path;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_RendererID;
	};

}