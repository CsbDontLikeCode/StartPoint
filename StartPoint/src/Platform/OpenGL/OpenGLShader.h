#pragma once
#include <StartPoint/Renderer/Shader.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace StartPoint {

	class OpenGLShader : public Shader
	{
	private:
		unsigned int m_RendererID;
		std::string m_Name;
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec3) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec4) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& mat4) override;

		virtual const std::string& GetName() { return m_Name; };

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec2);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec3);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec4);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix3);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix4);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSource);
	};

}