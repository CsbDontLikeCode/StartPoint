#include <iostream>
#include <StartPoint.h>

class Sandbox : public StartPoint::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}


};

StartPoint::Application* StartPoint::createApplication() {
	return new Sandbox();
}
