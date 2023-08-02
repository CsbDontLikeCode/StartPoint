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
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}