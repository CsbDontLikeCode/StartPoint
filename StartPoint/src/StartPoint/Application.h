#pragma once

#include "Core.h"

namespace StartPoint {
	class SP_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// 将由用户设置
	Application* createApplication();
}
