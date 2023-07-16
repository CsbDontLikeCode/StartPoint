#pragma once
#include <StartPoint/Core/Core.h>

namespace StartPoint
{

	class Texture 
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}