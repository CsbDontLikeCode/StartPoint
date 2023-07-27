#include <sppch.h>
#include <glm/glm.hpp>

#include "Scene.h"

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

		// m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>(entity);

		//if(m_Registry.all_of<TransformComponent>(entity))
		//{
		//	TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		//}

		//auto view = m_Registry.view<TransformComponent>();
		//for (auto entity : view)
		//{
		//	TransformComponent& transform = view.get<TransformComponent>(entity);
		//}

		//auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		//for (auto entity : group)
		//{
		//	auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		//}
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		//for (auto entity : group)
		//{
		//	auto [transform, spriteRenderer] = group.get<TransformComponent, SpriteRendererComponent>(entity);
		//	//Renderer2D::DrawQuad
		//}

		auto view = m_Registry.view<const TransformComponent, SpriteRendererComponent>();
		for (auto entity : view) {
			auto& transformComponent = view.get<TransformComponent>(entity);
			auto& spriteRendererComponent = view.get<SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transformComponent.Transform, spriteRendererComponent.Color);
		}
	}

}