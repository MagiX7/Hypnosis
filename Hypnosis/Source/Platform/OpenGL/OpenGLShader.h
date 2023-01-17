#pragma once

#include "Hypnosis/Renderer/Shader.h"

#include <unordered_map>
#include <string>

namespace Hypnosis {

	enum class ShaderType
	{
		FRAGMENT = 0,
		VERTEX,
		GEOMETRY
	};

	struct UniformData
	{
		unsigned int type;
		float data;
		std::string name;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		bool Refresh();

		inline const std::string& GetName() { return name; }
		inline void SetName(const std::string n) { name = n; }
		char* GetLastModifiedDate();

		virtual void SetUniformBool(const std::string& name, bool b) const override;

		virtual void SetUniform1i(const std::string& name, int i) const override;
		virtual void SetUniform1f(const std::string& name, float f) const override;

		virtual void SetUniformVec2f(const std::string& name, float v0, float v1) const override;
		virtual void SetUniformVec2f(const std::string& name, glm::vec2 v) const override;

		virtual void SetUniformVec3f(const std::string& name, float v0, float v1, float v2) const override;
		virtual void SetUniformVec3f(const std::string& name, glm::vec3 v) const override;

		virtual void SetUniformVec4f(const std::string& name, float v0, float v1, float v2, float v3) const override;
		virtual void SetUniformVec4f(const std::string& name, glm::vec4 v) const override;

		virtual void SetUniformMatrix3f(const std::string& name, const glm::mat3x3& mat) const override;
		virtual void SetUniformMatrix4f(const std::string& name, const glm::mat4x4& mat) const override;

		inline const std::string& GetPath() { return path; }

		std::list<UniformData> GetUniforms();
		void UpdateSourceCode(const std::string& newSource);

	private:
		unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
		std::string ReadFile();
		std::unordered_map<unsigned int, std::string> SplitShaders(const std::string& source);

		void ReCompile(bool reReadSource = true);

	private:
		std::string name;
		unsigned int rendererID;
		std::string source;
		std::string path;

		bool created;

		std::unordered_map<std::string, int> uniformsLocation;

		struct _stat lastStat;
		char timeBuf[26];
	};

}