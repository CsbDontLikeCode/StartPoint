#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern StartPoint::Application* StartPoint::createApplication();

int main(int argc, char** argv) {
	StartPoint::Log::init();
	//StartPoint::Log::GetCoreLogger()->warn("��ʼ����־");
	SP_CORE_WARN("CORE WARN!");
	//StartPoint::Log::GetClientLogger()->info("��ʼ����־");
	int a = 666;
	SP_INFO("CLIENT INFO! Var = {0}", a);

	auto app = StartPoint::createApplication();
	app->Run();
	delete app;
}

#endif