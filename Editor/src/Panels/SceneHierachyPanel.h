#pragma once
#include <StartPoint/Core/Core.h>
#include <StartPoint/Scene/Scene.h>
#include <StartPoint/Scene/Entity.h>
#include <StartPoint/Core/Log.h>

namespace StartPoint
{

	class SceneHierachyPanel
	{
	public:
		SceneHierachyPanel() = default;
		SceneHierachyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; };
		void SetSelectedEntity(Entity entity) { m_SelectionContext = entity; };
		void SetAddComponentState(bool state) { addComponentState = state; };
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
		bool addComponentState = true;
	};

}