#pragma once

#include <filesystem>

class ExternalSorter
{
public:
    ExternalSorter() = delete;
    ExternalSorter(const ExternalSorter&) = default;
    ExternalSorter(ExternalSorter&&) = default;

    ExternalSorter(const std::filesystem::path& inputPath,
        const std::filesystem::path& outputPath,
        const std::size_t availableMemory) noexcept;

    ~ExternalSorter();

    void Sort() noexcept;

    ExternalSorter& operator = (const ExternalSorter&) = delete;
    ExternalSorter& operator = (ExternalSorter&&) = delete;

private:
    void SortChunks() noexcept;
    void MergeChunks() noexcept;

private:
    const std::filesystem::path m_InputPath;
    const std::filesystem::path m_OutputPath;

    const std::size_t m_AvailableMemory;

    const std::filesystem::path m_TempDirPath{ "ext_sort_temp/" };
};
