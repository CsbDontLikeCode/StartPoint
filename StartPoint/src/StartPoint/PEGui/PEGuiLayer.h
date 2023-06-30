#pragma once

#include "../Layer.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/ApplicationEvent.h"

namespace StartPoint {

	class SP_API PEGuiLayer : public Layer
	{
	public:
		PEGuiLayer();
		~PEGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;

	private:
		float m_Time = 0.0f;
	};

}