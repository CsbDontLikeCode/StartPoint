#include <imgui.h>
#include <imgui_internal.h>
#include <StartPoint/Scene/Components.h>
#include <glm/gtc/type_ptr.hpp>

#include "SceneHierachyPanel.h"

#include <filesystem>

namespace StartPoint
{
	extern const std::filesystem::path g_AssetPath;

	SceneHierachyPanel::SceneHierachyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierachyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
		m_SelectionContext = {};
	}

	static inline bool BeginPopupContextWindow(const char* str_id, ImGuiMouseButton mb, bool over_items)
	{
		return ImGui::BeginPopupContextWindow(str_id, mb | (over_items ? 0 : ImGuiPopupFlags_NoOpenOverItems)); 

	}

	void SceneHierachyPanel::OnImGuiRender()
	{
		ImGui::Begin("SceneHierachy");

		if (m_Context) 
		{
			auto view = m_Context->m_Registry.view<TagComponent>();

			for (auto entity : view) {
				Entity ety{ entity, m_Context.get() };
				DrawEntityNode(ety);
			}

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectionContext = {};



			// Right-Click on blank space.
			if (BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create New Entity"))
				{
					m_Context->CreateEntity("Entity");
				}
				ImGui::EndPopup();
			}
		}

		ImGui::End();

		// Properties edit.
		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}
		ImGui::End();
	}
	void SceneHierachyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		//ImGui::Text("%s", tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				entityDeleted = true;
			}
			ImGui::EndPopup();
		}

		if (opened)
		{
			//ImGui::TreePop();
			//ImGui::Text("%s", tag.c_str());
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}
	// ====================================================================================================
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto firstFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.25f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(firstFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.4f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
		ImGui::PushFont(firstFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(firstFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}
	// ====================================================================================================
	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contextRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contextRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("-", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					removeComponent = true;
				}
				ImGui::EndPopup();
			}
			if (open) 
			{
				uiFunction(component);
				ImGui::TreePop();
			}
			if (removeComponent)
			{
				entity.RemoveComponent<T>();
			}
		}
	}
	// ====================================================================================================
	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		// ----------------------------------------------------------------------------------------------------
		// TagComponent.
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::Button("Add Component"))
		{
			if (addComponentState)
				ImGui::OpenPopup("AddComponent");
			else 
				SP_CORE_INFO("You can't add components now.");
		}
		if (ImGui::BeginPopup("AddComponent"))
		{
			// Add Camera Component.
			if (ImGui::MenuItem("Camera"))
			{
				if (m_SelectionContext.HasComponent<CameraComponent>())
				{
					SP_INFO("Camera exist!");
					ImGui::CloseCurrentPopup();
				}
				else
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			// Add Sprite Renderer Component.
			if (ImGui::MenuItem("Sprite Renderer"))
			{
				if (m_SelectionContext.HasComponent<SpriteRendererComponent>())
				{
					SP_INFO("Sprite Renderer exist!");
					ImGui::CloseCurrentPopup();
				}
				else
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			// Add Rigidbody2D Component.
			if (ImGui::MenuItem("Rigidbody2D"))
			{
				if (m_SelectionContext.HasComponent<Rigidbody2DComponent>())
				{
					SP_INFO("Rigidbody2D exist!");
					ImGui::CloseCurrentPopup();
				}
				else
				{
					m_SelectionContext.AddComponent<Rigidbody2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			// Add BoxCollider2D Component.
			if (ImGui::MenuItem("BoxCollider2D"))
			{
				if (m_SelectionContext.HasComponent<BoxCollider2DComponent>())
				{
					SP_INFO("BoxCollider2D exist!");
					ImGui::CloseCurrentPopup();
				}
				else
				{
					m_SelectionContext.AddComponent<BoxCollider2DComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			// Add Transform Component.
			if (ImGui::MenuItem("Transform"))
			{
				if (m_SelectionContext.HasComponent<TransformComponent>())
				{
					SP_INFO("Transform exist!");
					ImGui::CloseCurrentPopup();
				}
				else
				{
					m_SelectionContext.AddComponent<TransformComponent>();
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();
		// ----------------------------------------------------------------------------------------------------
		// SpriteRendererComponent.
		DrawComponent<SpriteRendererComponent>("Renderer/Color", entity,[](auto& component) {
			ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

			ImGui::Button("Texture", ImVec2(100.0f, 0.0f));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path texturePath = std::filesystem::path(g_AssetPath) / path;
					component.Texture = Texture2D::Create(texturePath.string());
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);
		});
		// ----------------------------------------------------------------------------------------------------
		// Rigidbody2D Component.
		DrawComponent<Rigidbody2DComponent>("Rigidbody2D", entity, [](auto& component) {
			const char* bodyTypeStrings[] = { "Static", "Dynamic", "Kinematic"};
			const char* currentBodyTypeString = bodyTypeStrings[(int)component.Type];
			if (ImGui::BeginCombo("Body Type", currentBodyTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = (currentBodyTypeString == bodyTypeStrings[i]);
					if (ImGui::Selectable(bodyTypeStrings[i], isSelected))
					{
						currentBodyTypeString = bodyTypeStrings[i];
						component.Type = (Rigidbody2DComponent::BodyType)i;
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Checkbox("Fixed Rotation", &component.FixedRotation);
		});
		// ----------------------------------------------------------------------------------------------------
		// Box Collider 2D Component.
		DrawComponent<BoxCollider2DComponent>("BoxCollider2D", entity, [](auto& component) {
			ImGui::DragFloat2("Offset", glm::value_ptr(component.Offset));
			ImGui::DragFloat2("Size", glm::value_ptr(component.Size));
			ImGui::DragFloat("Density", &component.Density, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction", &component.Friction, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &component.Restitution, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution Threshold", &component.RestitutionThreshold, 0.01f, 0.0f);
		});
		// ----------------------------------------------------------------------------------------------------
		// TransformComponent.
		DrawComponent<TransformComponent>("Transform", entity, [](auto& component) {
			DrawVec3Control("Translation", component.Translation);
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", component.Scale, 1.0f);
		});
		// ----------------------------------------------------------------------------------------------------
		// CameraComponent.
		DrawComponent<CameraComponent>("Camera", entity, [](auto& component) {
			auto& cameraComponent = component;
			auto& camera = component.Camera;
			// ----------------------------------------------------------------------------------------------------
			ImGui::Checkbox("Primary", &cameraComponent.Primary);
			// ----------------------------------------------------------------------------------------------------
			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = (currentProjectionTypeString == projectionTypeStrings[i]);
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}
					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			// ----------------------------------------------------------------------------------------------------
			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float perspectiveFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
				if (ImGui::DragFloat("Vertival FOV", &perspectiveFOV))
				{
					camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveFOV));
				}
				float nearClip = camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("NearClip", &nearClip))
				{
					camera.SetPerspectiveNearClip(nearClip);
				}
				float farClip = camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("FarClip", &farClip))
				{
					camera.SetPerspectiveFarClip(farClip);
				}
			}
			// ----------------------------------------------------------------------------------------------------
			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthoSize = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &orthoSize))
				{
					camera.SetOrthographicSize(orthoSize);
				}
				float nearClip = camera.GetOrthographicNearClip();
				if (ImGui::DragFloat("NearClip", &nearClip))
				{
					camera.SetOrthographicNearClip(nearClip);
				}
				float farClip = camera.GetOrthographicFarClip();
				if (ImGui::DragFloat("FarClip", &farClip))
				{
					camera.SetOrthographicFarClip(farClip);
				}
				ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);
			}
			});
	}
}