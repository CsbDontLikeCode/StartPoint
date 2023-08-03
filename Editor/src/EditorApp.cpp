#include <StartPoint.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Temporary
#include <Platform/OpenGL/OpenGLShader.h>

#include "EditorLayer.h"


// -----³ÌÐòÈë¿Ú------------------
#include "StartPoint/Core/EntryPoint.h"
// -------------------------------


namespace StartPoint 
{

	class SpEditor : public Application 
	{
	public:
		SpEditor() 
			: Application("StartPoint Editor")
		{
			// PushLayer(new ExampleLayer());
			PushOverlay(new EditorLayer());
		}

		~SpEditor() {

		}
	};

	Application* CreateApplication() {
		return new SpEditor();
	}

}