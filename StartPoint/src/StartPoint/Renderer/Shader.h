#pragma once

#include <string>

namespace StartPoint {

	class Shader {
	private:
		unsigned int m_RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	

	};

}