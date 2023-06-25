#pragma once

#include "Event.h"

#include <sstream>

namespace StartPoint {
	class SP_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}

		inline float GetX() const
		{
			return m_MouseX;
		}

		inline float GetY() const
		{
			return m_MouseY;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent:" << m_MouseX << "," << m_MouseY << "\n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)

		//EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		int x = (EventCategoryKeyboard | EventCategoryInput);
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

		float m_MouseX, m_MouseY;
	};
	
	class SP_API MouseScrolledEvent : public Event
	{

	};

	class SP_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const
		{
			return m_Button;
		}

		//EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button){}

		int m_Button;
	};

	class SP_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:" << m_Button << "\n";
			return ss.str();
		}
	};

	class SP_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}