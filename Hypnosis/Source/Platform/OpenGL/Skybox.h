//#pragma once
//
//#include "Hypnosis/Core/PerspectiveCamera.h"
//
//#include <memory>
//#include <vector>
//#include <string>
//
//namespace Hypnosis {
//
//	class OpenGLVertexBuffer;
//	class OpenGLVertexArray;
//	class OpenGLFrameBuffer;
//	class OpenGLShader;
//
//	class Skybox
//	{
//	public:
//		Skybox(std::string path);
//		~Skybox();
//
//		void Draw(const glm::mat3& view, const glm::mat4& projection);
//
//		inline const std::string& GetName() { return name; }
//		inline const std::string& GetPath() { return path; }
//		inline unsigned int GetId() { return cubemapID; }
//		inline unsigned int GetIrradianceMapId() { return irradianceMapID; }
//		inline unsigned int GetHDRId() { return hdrTexture; }
//		inline unsigned int GetPrefilterMapId() { return prefilterMap; }
//		inline unsigned int GetBRDFId() { return brdfTexture; }
//		inline unsigned int GetFBO() { return captureFBO; }
//		inline unsigned int GetRBO() { return captureRBO; }
//
//		inline float& GetReflectionLod() { return reflectionLod; }
//		inline float SetReflectionLod(float value) { reflectionLod = value; }
//
//		inline bool& IsReflectionEnabled() { return enableReflection; }
//		inline void SetIsReflectionEnabled(bool value) { enableReflection = value; }
//
//		void BindIrradianceMap(int slot);
//		void BindPrefilterMap(int slot);
//		void BindBRDF(int slot);
//
//	private:
//		void SetUpCube();
//		void SetUpQuad();
//		
//		void DrawCube();
//		void DrawQuad();
//
//	private:
//		std::string name;
//		std::string path;
//		unsigned int captureFBO, captureRBO;
//		unsigned int cubemapID, irradianceMapID;
//		unsigned int hdrTexture, brdfTexture;
//		unsigned int prefilterMap;
//
//		Scope<OpenGLVertexBuffer> cubeVbo;
//		Scope<OpenGLVertexArray> cubeVao;
//		Scope<OpenGLVertexBuffer> quadVbo;
//		Scope<OpenGLVertexArray> quadVao;
//		Scope<OpenGLShader> skyboxShader;
//		Scope<OpenGLShader> hdrToCubemapShader;
//		Scope<OpenGLShader> irradianceMapShader;
//		Scope<OpenGLShader> prefilterShader;
//		Scope<OpenGLShader> brdfShader;
//		
//		float reflectionLod;
//		bool enableReflection;
//	};
//
//}