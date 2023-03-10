#include "OpenGLTexture2D.h"

#include "Hypnosis/Core/Log.h"

#include <stb_image.h>
#include <glad/glad.h>

#include <iostream>


namespace Hypnosis {

	/*OpenGLTexture2D::OpenGLTexture2D(uint32_t* data, int w, int h) : data(data)
	{
		width = w;
		height = h;
		SetData(data);
	}*/

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path), width(0), height(0)
	{
		int w, h, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

		// TODO: Data from stbi gets deleted later. May affect when an image is loaded
		this->data = data;

		name = path.substr(path.find_last_of("/") + 1, path.length());

		if (!data)
		{
			HS_CORE_ERROR("Texture {0} couldn't be loaded.", path);
			return;
		}

		width = w;
		height = h;

		GLint storageFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			storageFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			storageFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		if (!storageFormat || !dataFormat)
		{
			std::cout << "[INFO] Texture format not supported" << std::endl;
			return;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glBindTexture(GL_TEXTURE_2D, rendererId);
		glTextureStorage2D(rendererId, 1, storageFormat, width, height);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererId, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererId);
	}

	void OpenGLTexture2D::SetData(uint32_t* data)
	{
		if (rendererId > 0)
			glDeleteTextures(1, &rendererId);

		this->data = data;
		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glBindTexture(GL_TEXTURE_2D, rendererId);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);		

	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, rendererId);
		//glBindTextureUnit(slot, rendererId);
	}

	void OpenGLTexture2D::BindImage()
	{
		glBindImageTexture(0, rendererId, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::UnbindImage()
	{
		glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	}

}