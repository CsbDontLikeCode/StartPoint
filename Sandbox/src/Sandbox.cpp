#include <iostream>
#include <StartPoint.h>
#include <imgui.h>

class ExampleLayer : public StartPoint::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"){}

	void OnUpdate() override
	{
		//SP_INFO("ExampleLayer::Update");

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
	}

	void OnEvent(StartPoint::Event& event) override
	{
		//SP_TRACE("{0}", event);
	}
};

class Sandbox : public StartPoint::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		// PushOverlay(new StartPoint::ImGuiLayer());
	}

	~Sandbox() {

	}

};

StartPoint::Application* StartPoint::createApplication() {
	return new Sandbox();
}
