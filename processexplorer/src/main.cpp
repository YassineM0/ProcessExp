#include "ProcessUtils.h"
#include <iostream>

int main() {
	auto processes = ProcessUtils::GetProcessList();

	for (const auto& [pid, name] : processes) {
		std::cout << pid << "\t";
		std::wcout << name << std::endl;

#ifdef PLATEFORM_WINDOWS
		auto parent = ProcessUtils::Windows::GetProcessParentID(pid);
		std::cout << "parent's ID : " << parent << "\n";
#endif
	}

	return 0;
}