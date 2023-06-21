#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern StartPoint::Application* StartPoint::createApplication();

int main(int argc, char** argv) {
	auto app = StartPoint::createApplication();
	app->Run();
	delete app;
}

#endif