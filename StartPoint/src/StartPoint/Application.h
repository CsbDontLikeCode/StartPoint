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

	// �����û�����
	Application* createApplication();
}
