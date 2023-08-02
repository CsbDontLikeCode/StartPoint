#include <imgui.h>
#include <StartPoint/Scene/Components.h>

#include "SceneHierachyPanel.h"

namespace StartPoint 
{
	SceneHierachyPanel::SceneHierachyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierachyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierachyPanel::OnImGuiRender()
	{
		ImGui::Begin("SceneHierachy");

		auto view = m_Context->m_Registry.view<TagComponent>();

		for (auto entity : view) {
			Entity ety{ entity, m_Context.get() };
			DrawEntityNode(ety);
			//auto& tag = view.get<TagComponent>(entity);
			//ImGui::Text("%s", tag.Tag.c_str());
		}

		// TODELETE::The following code is invalid.
		//m_Context->m_Registry.each([&](auto entityID)
		//{
		//	Entity entity{ entityID, m_Context.get() };
		//	auto& tc = entity.GetComponent<TagComponent>();
		//	ImGui::Text("%s", tc.Tag);
		//});

		ImGui::End();
	}
	void SceneHierachyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		//ImGui::Text("%s", tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
			ImGui::Text("%s", tag.c_str());
		}
	}
}