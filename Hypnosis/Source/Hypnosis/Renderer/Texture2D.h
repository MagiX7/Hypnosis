#pragma once

#include "Hypnosis/Core/Core.h"

#include <memory>
#include <string>

namespace Hypnosis {

	class Texture2D
	{
	public:
		virtual ~Texture2D() {};

		static Ref<Texture2D> Create(const std::string& path);

		virtual void Bind(uint32_t slot = 0) = 0;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual inline uint32_t GetId() = 0;

		virtual const std::string& GetName() = 0;

	};

}