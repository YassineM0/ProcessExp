#include "ProcessUtils.h"

#ifdef PLATEFORM_WINDOWS
	#include <Windows.h>
	#include <TlHelp32.h>
#elif PLATEFORM_LINUX
	/*/*/
#endif

namespace ProcessUtils {
	
	// Cross-Plateform function implementations
	bool IsProcessRunning(ProcessID pid) {
		#ifdef PLATEFORM_WINDOWS
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
		if (process != nullptr) {
			CloseHandle(process);
			return true;
		}
		return false;
		#endif
	}

	// Windows functions implementations
	ProcessList GetProcessList() {
		ProcessList processes;
		// flag -> ignored process id
		HANDLE hSnaphot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		
		if (hSnaphot == INVALID_HANDLE_VALUE) {
			return processes;
		}

		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnaphot, &pe32)) {
			do {
				processes.emplace_back(pe32.th32ProcessID, pe32.szExeFile);
			} while (Process32Next);
		}
		CloseHandle(hSnaphot);
		return processes;
	}
}