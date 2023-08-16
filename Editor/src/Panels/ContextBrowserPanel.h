#pragma once
#include <filesystem>

namespace StartPoint
{
	class ContextBrowserPanel
	{
	public:
		ContextBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
	};
}