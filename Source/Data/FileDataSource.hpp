#pragma once

#include <fstream>
#include <filesystem>

#include "Transform/FileInfo.hpp"

class FileDataSource
{
public:
    using Size = std::size_t;

public:
    FileDataSource() = delete;
    FileDataSource(const FileDataSource&) = delete;
    FileDataSource(FileDataSource&&) = default;

    FileDataSource(FileInfo&& fileInfo, const Size bufferSize);

    ~FileDataSource() = default;

    double GetValue(const Size valueNumber) noexcept;

    void ReadData() noexcept;
    void WriteData() noexcept;

    Size GetSize() const noexcept;
    Size GetCount() const noexcept;

    FileDataSource& operator = (const FileDataSource&) = delete;
    FileDataSource& operator = (FileDataSource&&) = delete;

private:
    void MoveStreamPointer(const Size valueNumber) noexcept;

private:
    FileInfo m_FileInfo;
    std::fstream m_FileStream;
    
    Size m_ChunkSize;
    std::vector<double> m_RealData{};

    Size m_MinPosition{};
    Size m_MaxPosition{};

    Size m_FileSize{};
    Size m_ValuesCount{};
};
