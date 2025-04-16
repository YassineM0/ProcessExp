#include "ProcessUtils.h"


#ifdef PLATEFORM_WINDOWS
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
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

#ifdef PLATEFORM_WINDOWS


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
				processes.emplace_back(pe32.th32ProcessID, std::wstring(pe32.szExeFile));
			} while (Process32Next(hSnaphot, &pe32));
		}
		CloseHandle(hSnaphot);
		return processes;
	}
	namespace Windows {
		ProcessID GetProcessParentID(ProcessID pid) {
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

			if (hSnapshot == INVALID_HANDLE_VALUE) {
				return 0;
			}

			PROCESSENTRY32 pe32;
			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(hSnapshot, &pe32)) {
				do {
					if (pe32.th32ProcessID == pid) {
						CloseHandle(hSnapshot);
						return pe32.th32ParentProcessID;
					}
				} while (Process32Next(hSnapshot, &pe32));
			}

			CloseHandle(hSnapshot);
			return 0;
		}

		//returns empty string on fail
		std::string GetProcessFullPath(ProcessID pid) {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
			if (hProcess == NULL) return "";

			char path[MAX_PATH];
			if (GetModuleFileNameExA(hProcess, NULL, path, MAX_PATH) == 0) {
				CloseHandle(hProcess);
				return "";
			}

			CloseHandle(hProcess);
			return path;
		}
	}

#endif


}