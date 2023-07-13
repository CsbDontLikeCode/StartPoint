#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern StartPoint::Application* StartPoint::createApplication();

int main(int argc, char** argv) {
	StartPoint::Log::init();
	SP_CORE_WARN("CORE WARN!");
	SP_INFO("CLIENT INFO!");

	auto app = StartPoint::createApplication();
	app->Run();
	delete app;
}

#endif