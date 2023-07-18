#include <sppch.h>
#include "OpenGLTexture.h"
#include <stb_image/stb_image.h>
#include <StartPoint/Core/Core.h>

namespace StartPoint
{

	OpenGLTextur2D::OpenGLTextur2D(const std::string& path)
		: m_Path(path)
	{
		SP_PROFILE_FUNCTION();

		// The style of image reading is different between OpenGL and stb.
		// Therefore, it is necessary to flip the image vertically.
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		stbi_uc* data = nullptr;
		{
			SP_PROFILE_SCOPE("stbi_load - OpenGLTextur2D::OpenGLTextur2D(const std::string& path)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		
		SP_CORE_ASSERT(data, "Fail to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) 
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) 
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		SP_CORE_ASSERT(internalFormat & dataFormat, "Image format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTextur2D::OpenGLTextur2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTextur2D::~OpenGLTextur2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTextur2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = (m_DataFormat == GL_RGBA ? 4 : 3);
		SP_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTextur2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(0, m_RendererID);
	}

}