#pragma once
#include <filesystem>
#include <StartPoint/Renderer/Texture.h>

namespace StartPoint
{
	class ContextBrowserPanel
	{
	public:
		ContextBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}