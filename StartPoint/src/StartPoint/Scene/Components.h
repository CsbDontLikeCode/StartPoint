#pragma once
#include <glm/glm.hpp>
#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace StartPoint
{
	
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;	// ---------------------------->Whether the camera length width ratio is fixed.

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		// -----------------------------------------------------------------------------
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);
		// -----------------------------------------------------------------------------
		//std::function<void(ScriptableEntity* instance)> OnCreateFunction;
		//std::function<void(ScriptableEntity* instance)> OnDestroyFunction;
		//std::function<void(ScriptableEntity* instance, Timestep)> OnUpdateFunction;
		// =============================================================================
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
			//OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			//OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			//OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { ((T*)instance)->OnUpdate(ts); };
		}
	};

}