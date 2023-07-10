#include <sppch.h>
#include "OpenGLTexture.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <StartPoint/Core.h>

namespace StartPoint
{

	OpenGLTextur2D::OpenGLTextur2D(const std::string& path)
		: m_Path(path)
	{
		// The style of image reading is different between OpenGL and stb.
		// Therefore, it is necessary to flip the image vertically.
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
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
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTextur2D::~OpenGLTextur2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTextur2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(0, m_RendererID);
	}

}