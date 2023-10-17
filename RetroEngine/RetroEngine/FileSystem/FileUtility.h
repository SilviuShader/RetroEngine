#pragma once

#include <string>

namespace RetroEngine::FileSystem
{
	class FileUtility
	{
	public:

		static std::string ReadFile(const std::string&);
	};
}