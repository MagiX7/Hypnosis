#pragma once

#include "Hypnosis/Renderer/Texture2D.h"

#include <string>

namespace Hypnosis {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		//OpenGLTexture2D(uint32_t* data, int w, int h);
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();

		void SetData(uint32_t* data);

		virtual void Bind(uint32_t slot = 0) override;
		void BindImage();
		void Unbind();
		void UnbindImage();

		inline const void* GetData() const { return data; }

		virtual unsigned int GetWidth() override { return width; }
		virtual unsigned int GetHeight() override { return height; }

		inline uint32_t GetId() { return rendererId; }

		inline const std::string& GetName() { return name; }

		inline void SetName(std::string value) { name = value; }

	private:
		uint32_t rendererId;

		std::string path;
		std::string name;
		unsigned int width;
		unsigned int height;
		void* data;
	};

}