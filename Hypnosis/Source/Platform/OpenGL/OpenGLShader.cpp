#include "OpenGLShader.h"
#include "Hypnosis/Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <assert.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>

namespace Hypnosis {

	GLenum GetShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment")
			return GL_FRAGMENT_SHADER;
	}


	OpenGLShader::OpenGLShader(const std::string& path) : path(path), rendererID(0)
	{
		int s = path.find_last_of("/");
		int e = path.find_last_of(".");
		name = path.substr(s + 1, e - s - 1);

		struct _stat nowStat;
		if (_stat(path.c_str(), &nowStat) == 0)
		{
			lastStat = nowStat;
		}

		source = ReadFile();
		auto shaderSources = SplitShaders(source);
		CreateShader(shaderSources[GL_VERTEX_SHADER], shaderSources[GL_FRAGMENT_SHADER]);

		created = true;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(rendererID);
	}

	void OpenGLShader::Unbind() const 
	{
		glUseProgram(0);
	}

	void OpenGLShader::ReCompile(bool reReadSource)
	{
		if (reReadSource)
			source = ReadFile();

		auto shaderSources = SplitShaders(source);

		CreateShader(shaderSources[GL_VERTEX_SHADER], shaderSources[GL_FRAGMENT_SHADER]);
	}

	bool OpenGLShader::Refresh()
	{
		struct _stat nowStat;
		if (_stat(path.c_str(), &nowStat) == 0)
		{
			if (lastStat.st_mtime != nowStat.st_mtime)
			{
				ctime_s(timeBuf, 26, &lastStat.st_mtime);
				printf("Time modified : %s", timeBuf);

				ReCompile();

				lastStat = nowStat;

				return true;
			}
		}

		return false;
	}

	char* OpenGLShader::GetLastModifiedDate()
	{
		ctime_s(timeBuf, 26, &lastStat.st_mtime);
		return timeBuf;
	}

	void OpenGLShader::SetUniformBool(const std::string& name, bool b) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, b);
	}

	void OpenGLShader::SetUniform1i(const std::string& name, int i) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1i(location, i);
	}

	void OpenGLShader::SetUniform1f(const std::string& name, float f) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, f);
	}

	void OpenGLShader::SetUniformVec2f(const std::string& name, float v0, float v1) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform2f(location, v0, v1);
	}

	void OpenGLShader::SetUniformVec2f(const std::string& name, glm::vec2 v) const
	{
		SetUniformVec2f(name, v.x, v.y);
	}

	void OpenGLShader::SetUniformVec3f(const std::string& name, float v0, float v1, float v2) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform3f(location, v0, v1, v2);
	}

	void OpenGLShader::SetUniformVec3f(const std::string& name, glm::vec3 v) const
	{
		SetUniformVec3f(name, v.x, v.y, v.z);
	}

	void OpenGLShader::SetUniformVec4f(const std::string& name, float v0, float v1, float v2, float v3) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4f(location, v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniformVec4f(const std::string& name, glm::vec4 v) const
	{
		SetUniformVec4f(name, v.x, v.y, v.z, v.w);
	}

	void OpenGLShader::SetUniformMatrix3f(const std::string& name, const glm::mat3x3& mat) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetUniformMatrix4f(const std::string& name, const glm::mat4x4& mat) const
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	std::list<UniformData> OpenGLShader::GetUniforms()
	{
		//std::unordered_map<std::string, float> ret;
		std::list<UniformData> ret;

		GLint numActiveAttribs = 0;
		GLint numActiveUniforms = 0;
		glGetProgramInterfaceiv(rendererID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numActiveAttribs);
		glGetProgramInterfaceiv(rendererID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numActiveUniforms);

		std::vector<GLchar> nameData(256);
		std::vector<GLenum> properties;
		properties.push_back(GL_NAME_LENGTH);
		properties.push_back(GL_TYPE);
		properties.push_back(GL_ARRAY_SIZE);
		properties.push_back(GL_ARRAY_STRIDE);
		properties.push_back(GL_OFFSET);

		std::vector<GLint> values(properties.size());

		UniformData retData;
		for (int attrib = 0; attrib < numActiveUniforms; ++attrib)
		{
			glGetProgramResourceiv(rendererID, GL_UNIFORM, attrib, properties.size(),
				&properties[0], values.size(), NULL, &values[0]);

			//if (values[1] != GL_FLOAT) // If it is not a float, we continue iterating
			//	continue;

			/*if (values[0] == -1)
				continue;*/
			if (values[1] != GL_FLOAT)
			{
				continue;
			}

			nameData.resize(values[0]); // The length of the name.
			glGetProgramResourceName(rendererID, GL_UNIFORM, attrib, nameData.size(), NULL, &nameData[0]);

			std::string name((char*)&nameData[0], nameData.size() - 1);

			retData.name = name;
			retData.type = properties[1];
			retData.data = values[0];
			ret.push_back(retData);
			//ret[attrib] = values[attrib];
		}

		return ret;
	}

	void OpenGLShader::UpdateSourceCode(const std::string& newSource)
	{
		source = newSource;
		ReCompile(false);
	}

	unsigned int OpenGLShader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		const char* vsource = vertexSource.c_str();
		glShaderSource(vs, 1, &vsource, NULL);
		glCompileShader(vs);

		int success;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vs, 512, NULL, infoLog);
			ZN_CORE_ERROR("{0} Vertex Shader compilation failed {1}", name, infoLog);
		}

		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fsource = fragmentSource.c_str();
		glShaderSource(fs, 1, &fsource, NULL);
		glCompileShader(fs);

		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fs, 512, NULL, infoLog);
			ZN_CORE_ERROR("{0} Fragment Shader compilation failed {1}", name, infoLog);
		}

		rendererID = glCreateProgram();
		glAttachShader(rendererID, vs);
		glAttachShader(rendererID, fs);

		glLinkProgram(rendererID);
		glValidateProgram(rendererID);

		glGetProgramiv(rendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(rendererID, 512, NULL, infoLog);
			ZN_CORE_ERROR("{0} shader linking failed {1}", name, infoLog);
		}

		glDetachShader(rendererID, vs);
		glDeleteShader(vs);

		glDetachShader(rendererID, fs);
		glDeleteShader(fs);

		return 0;
	}

	std::string OpenGLShader::ReadFile()
	{
		std::string ret;
		std::ifstream in(path, std::ios::in, std::ios::binary);

		if (in)
		{
			// We seek for the end of file so we can set the returning string size
			in.seekg(0, std::ios::end);
			ret.resize(in.tellg());

			// We now seek for the file beginning to put it at the string (passing the string's first position and its size)
			in.seekg(0, std::ios::beg);
			in.read(&ret[0], ret.size());

			// Finally close the file
			in.close();
		}
		else
		{
			ZN_CORE_ERROR("Could not locate the shader: {0}", name);
		}

		return ret;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::SplitShaders(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> ret;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t lineEnding = source.find_first_of("\r\n", pos);

			size_t beginPos = pos + typeTokenLength + 1;
			std::string shaderType = source.substr(beginPos, lineEnding - beginPos);

			size_t nextLine = source.find_first_not_of("\r\n", lineEnding);
			pos = source.find(typeToken, nextLine);

			ret[GetShaderTypeFromString(shaderType)] = pos == std::string::npos ? source.substr(nextLine) : source.substr(nextLine, pos - nextLine);
		}

		return ret;
	}
}