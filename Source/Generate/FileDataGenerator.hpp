#pragma once

#include <random>

#include "General/FileInfo.hpp"

class FileDataGenerator
{
public:
    using Range = std::pair<double, double>;

public:
    FileDataGenerator() = delete;
    FileDataGenerator(const FileDataGenerator&) = delete;
    FileDataGenerator(FileDataGenerator&&) = default;

    FileDataGenerator(const std::filesystem::path& info,
        const std::size_t fileSize, const std::size_t bufferSize,
        const Range& valuesRange) noexcept;

    ~FileDataGenerator() = default;

    void Generate() noexcept;

    FileDataGenerator& operator = (const FileDataGenerator&) = delete;
    FileDataGenerator& operator = (FileDataGenerator&&) = delete;

private:
    double RandomizeValue() noexcept;

private:
    FileInfo m_Info;
    std::size_t m_FileSize;

    std::size_t m_BufferSize;

    std::mt19937 m_Generator;
    std::uniform_real_distribution<double> m_Distribution{};
};
