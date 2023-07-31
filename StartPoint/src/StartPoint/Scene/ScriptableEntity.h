#pragma once
#include "Entity.h"

namespace StartPoint 
{

	class ScriptableEntity
	{
		public:
			// Get any of m_Entity's components.
			template <typename T>
			T& GetComponent()
			{
				return m_Entity.GetComponent<T>();
			}

		private:
			Entity m_Entity;
			friend class Scene;
	};


}