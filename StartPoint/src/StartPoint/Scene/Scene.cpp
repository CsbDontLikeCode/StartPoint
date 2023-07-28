#include <sppch.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Entity.h"

namespace StartPoint 
{

	static void DoMath(const glm::mat4& transform)
	{
	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
	}

	Scene::Scene()
	{
		// entt::entity type->uint32_t, because of this, all operations on entities need to go through the registry.
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto view = m_Registry.view<const TransformComponent, SpriteRendererComponent>();
		for (auto entity : view) {
			auto& transformComponent = view.get<TransformComponent>(entity);
			auto& spriteRendererComponent = view.get<SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transformComponent.Transform, spriteRendererComponent.Color);
		}
	}

}