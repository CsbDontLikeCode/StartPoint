#pragma once

#include "Event.h"

#include "sppch.h"

namespace StartPoint{

	class SP_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const 
		{
			return m_KeyCode;
		}
		//EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode){}

		int m_KeyCode;
	};

	class SP_API KeyPressedEvent : public KeyEvent 
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class SP_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode  << "\n";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class SP_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}