#include <sppch.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "Entity.h"
#include "Components.h"

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
		// Update scripts.
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) {
				if (!nsc.Instance) {
					nsc.InstantiateFunction();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.OnCreateFunction(nsc.Instance);
				}
				nsc.OnUpdateFunction(nsc.Instance, ts);
			});
		}

		SceneCamera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& transform = view.get<TransformComponent>(entity);
				auto& camera = view.get<CameraComponent>(entity);
				if (camera.Primary) 
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);
			auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : view) {
				auto& transformComponent = view.get<TransformComponent>(entity);
				auto& spriteRendererComponent = view.get<SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transformComponent.Transform, spriteRendererComponent.Color);
			}
			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize the non-fixed cameras.
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

}