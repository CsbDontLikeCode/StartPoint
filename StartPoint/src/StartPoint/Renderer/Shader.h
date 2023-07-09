#pragma once

#include <string>
#include <glm/glm.hpp>

namespace StartPoint {

	class Shader {
	private:
		unsigned int m_RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		~Shader();

		void Bind() const;

		void Unbind() const;

		void UploadUniformFloat4(const std::string& name, const glm::vec4& color);

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};

}