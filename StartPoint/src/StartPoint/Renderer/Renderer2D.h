 #pragma once

#include <StartPoint/Renderer/OrthegraphicCamera.h>
#include <StartPoint/Renderer/Texture.h>
#include <StartPoint/Renderer/SubTexture2D.h>
#include <StartPoint/Renderer/Camera.h>
#include <StartPoint/Renderer/EditorCamera.h>
#include <StartPoint/Scene/Components.h>

namespace StartPoint 
{

	class Renderer2D 
	{
	public:
		// Init and Shutdown will be equivalent to constructor and destructor
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthegraphicCamera& camera);
		static void EndScene();
		static void Flush();

		// Draw geometric shapes
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Rotation is in radians.
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Draw Circles.
		static void DrawCircle(const glm::vec3& position, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005, int entityID = -1);
		static void DrawCircle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005, int entityID = -1);
		static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005, int entityID = -1);

		// Draw Lines.
		static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, int entityID = -1);

		// Draw Rects.
		static void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, int entityID = -1);
		static void DrawRect(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		
		// Draw quad Entity.
		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int EntityID);

		static float GetLineWidth();
		static void SetLineWitdh(float width);

		struct Statistics
		{
			unsigned int DrawCalls = 0;
			unsigned int QuadCount = 0;

			// What's the meaning of these two functions?
			unsigned int GetTotalVertexCount() { return QuadCount * 4; }
			unsigned int GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void FlushAndReset();
	};

}