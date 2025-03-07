#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <psapi.h>

inline void PrintMemoryUsage(const std::string& message = {}) noexcept
{
    PROCESS_MEMORY_COUNTERS pmc{};

    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        const std::size_t memoryUseMB = pmc.WorkingSetSize / (1024 * 1024);

        std::cout << message << "[MEMORY] RAM Usage: "
            << memoryUseMB << " MB" << std::endl;
    }
}
