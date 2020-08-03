#ifndef OS_HPP
#define OS_HPP

enum class OperatingSystem {
	Linux,
	Mac,
	Windows
};

constexpr OperatingSystem CurrentOS =
	#if _WIN32
		OperatingSystem::Windows;
	#elif __APPLE__
		OperatingSystem::Mac;
	#else
		OperatingSystem::Linux;
	#endif

#endif // Include guard.
