#pragma once

#include <entt/entt.hpp>
#include <StartPoint/Core/Timestep.h>
#include <StartPoint/Renderer/Renderer2D.h>

#include "Components.h"

namespace StartPoint
{
	class Entity;

	class Scene 
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "");

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t	width, uint32_t height);
	private:
		// The container of entity and component.
		entt::registry m_Registry;

		// The width and height of viewport.
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;

		friend class Entity;
	};

}