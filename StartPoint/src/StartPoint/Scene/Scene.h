#pragma once
#include <entt/entt.hpp>
#include <StartPoint/Core/Timestep.h>
#include <StartPoint/Renderer/Renderer2D.h>
#include <StartPoint/Renderer/EditorCamera.h>

namespace StartPoint
{
	class Entity;

	class Scene 
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "");
		// The "entity" is just a unique ID(unsigned int type).
		void DestroyEntity(Entity entity);

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnViewportResize(uint32_t	width, uint32_t height);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		// The container of entity and component.
		entt::registry m_Registry;

		// The width and height of viewport.
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierachyPanel;
		friend class SceneSerializer;
	};
}