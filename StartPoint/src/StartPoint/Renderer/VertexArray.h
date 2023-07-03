#pragma once

#include <StartPoint/Renderer/Buffer.h>

namespace StartPoint {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int size);
	private:
	};

}