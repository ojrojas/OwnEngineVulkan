#pragma once
#include <cstdint>
#include <string>
#include <iostream>

namespace OwnEngine {
	struct MakeVersion {
		uint32_t major;
		uint32_t minor;
		uint32_t patch;
	};

	static void LogInfo(std::string message, std::string className)
	{
		std::cout << "[INFO]" << message << std::endl;
	}

	static void LogWarn(std::string message, std::string className)
	{
		std::cout << "[WARN]" << message << std::endl;
	}

	static std::string GetOsName()
	{
#ifdef _WIN32
		return "Windows 32-bit";
#elif _WIN64
		return "Windows 64-bit";
#elif __APPLE__ || __MACH__
		return "Mac OSX";
#elif __linux__
		return "Linux";
#elif __FreeBSD__
		return "FreeBSD";
#elif __unix || __unix__
		return "Unix";
#else
		return "Other";
#endif
	}
}