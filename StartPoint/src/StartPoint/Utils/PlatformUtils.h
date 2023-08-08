#pragma once

#include <string>

namespace StartPoint
{

	class FileDialogs
	{
	public:
		// "filter" limits the filetype which can be chosen;
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}