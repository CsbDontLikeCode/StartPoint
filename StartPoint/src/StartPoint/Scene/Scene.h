#pragma once

#include <entt/entt.hpp>
#include <StartPoint/Core/Timestep.h>
#include <StartPoint/Renderer/Renderer2D.h>

//#include "Entity.h"
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
	private:
		// The container of entity and component.
		entt::registry m_Registry;

		friend class Entity;
	};

}