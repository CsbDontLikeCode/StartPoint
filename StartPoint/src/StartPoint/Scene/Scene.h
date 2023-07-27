#pragma once

#include <entt/entt.hpp>
#include <StartPoint/Core/Timestep.h>
#include <StartPoint.h>

#include "Components.h"

namespace StartPoint
{

	class Scene 
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		// The container of entity and component.
		entt::registry m_Registry;
	};

}