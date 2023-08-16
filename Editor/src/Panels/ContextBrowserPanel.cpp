#include <sppch.h>

#include "ContextBrowserPanel.h"

#include <imgui.h>

namespace StartPoint
{
	static const std::filesystem::path s_AssetPath = "assets";

	ContextBrowserPanel::ContextBrowserPanel()
		: m_CurrentDirectory(s_AssetPath){}

	void ContextBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("ContextBrouser");

		if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}
		
		for (auto& directoryEntity : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntity.path();
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();
			if(directoryEntity.is_directory())
			{
				if (ImGui::Button(filenameString.c_str()))
				{
					m_CurrentDirectory /= path.filename();
				}
			}
			else 
			{
				if (ImGui::Button(filenameString.c_str()))
				{

				}
			}
		}

		ImGui::End();
	}
}