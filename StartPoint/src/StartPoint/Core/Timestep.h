#pragma once

namespace StartPoint {
	// Timestep class for recording current time
	class Timestep {
	public:
		Timestep(float time)
			: m_Time(time){}

		operator float() { return m_Time; }

		float GetSecond() { return m_Time; }
		float GetMillisecond() { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}