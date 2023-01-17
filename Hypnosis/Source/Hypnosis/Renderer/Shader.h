#pragma once

#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>

#include <string>
#include <memory>

namespace Hypnosis {

	class Shader
	{
	public:
		virtual ~Shader() {}

		static std::shared_ptr<Shader> Create(const std::string& path);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniformBool(const std::string& name, bool b) const = 0;

		virtual void SetUniform1i(const std::string& name, int i) const = 0;
		virtual void SetUniform1f(const std::string& name, float f) const = 0;

		virtual void SetUniformVec2f(const std::string& name, float v0, float v1) const = 0;
		virtual void SetUniformVec2f(const std::string& name, glm::vec2 v) const = 0;

		virtual void SetUniformVec3f(const std::string& name, float v0, float v1, float v2) const = 0;
		virtual void SetUniformVec3f(const std::string& name, glm::vec3 v) const = 0;

		virtual void SetUniformVec4f(const std::string& name, float v0, float v1, float v2, float v3) const = 0;
		virtual void SetUniformVec4f(const std::string& name, glm::vec4 v) const = 0;

		virtual void SetUniformMatrix3f(const std::string& name, const glm::mat3x3& mat) const = 0;
		virtual void SetUniformMatrix4f(const std::string& name, const glm::mat4x4& mat) const = 0;

	};

}