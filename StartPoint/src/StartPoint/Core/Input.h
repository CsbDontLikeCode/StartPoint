#pragma once

#include <StartPoint/Core/Core.h>
#include <glad/glad.h>

namespace StartPoint {

	class SP_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}