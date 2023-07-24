#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern StartPoint::Application* StartPoint::CreateApplication();

int main(int argc, char** argv) 
 {
	StartPoint::Log::init();

	SP_PROFILE_BEGIN_SESSION("Startup", "StartPointProfile-Startup.json");
	auto app = StartPoint::CreateApplication();
	SP_PROFILE_END_SESSION();
	
	SP_PROFILE_BEGIN_SESSION("Runtime", "StartPointProfile-Runtime.json");
	app->Run();
	SP_PROFILE_END_SESSION();
	
	SP_PROFILE_BEGIN_SESSION("Shutdown", "StartPointProfile-Shutdown.json");
	delete app;
	SP_PROFILE_END_SESSION();
}

#endif