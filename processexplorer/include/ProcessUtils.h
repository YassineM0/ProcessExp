#pragma once

#include <vector>
#include <utility>
#include <string>

// plateform detection

#if defined(_WIN32) || defined(_WIN64)
	#define PLATEFORM_WINDOWS
#elif defined(__linux__)
	#define PLATEFORM_LINUX
#else
	#error "unsupported plateform"
#endif

#ifdef PLATEFORM_WINDOWS
	#include <Windows.h>
#endif

namespace ProcessUtils {

	// alias definitions
	#ifdef PLATEFORM_WINDOWS
		using ProcessID = DWORD;
	#elif PLATEFORM_LINUX
		using ProcessID = unsigned long;
	#endif
	using ProcessList = std::vector < std::pair<ProcessID, std::string>>;

	/**
	*	@brief Get list of running processes (pid + name)	
	*/
	ProcessList GetProcessList();

	/**
	* @brief Check if process exists
	* @param pid Process ID
	*/
	bool IsProcessRunning(ProcessID pid);



}