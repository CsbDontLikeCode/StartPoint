#include <imgui.h>
#include <StartPoint/Scene/Components.h>
#include <glm/gtc/type_ptr.hpp>

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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		// TODELETE::The following code is invalid.
		//m_Context->m_Registry.each([&](auto entityID)
		//{
		//	Entity entity{ entityID, m_Context.get() };
		//	auto& tc = entity.GetComponent<TagComponent>();
		//	ImGui::Text("%s", tc.Tag);
		//});

		ImGui::End();

		// Properties edit.
		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);
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

	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		// TagComponent.
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		// TransformComponent.
		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}
		}
	}
}