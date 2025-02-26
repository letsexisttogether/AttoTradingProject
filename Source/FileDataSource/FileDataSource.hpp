#pragma once

#include <fstream>
#include <filesystem>

class FileDataSource
{
public:
    using Index = std::size_t;

public:
    FileDataSource() = delete;
    FileDataSource(const FileDataSource&) = delete;
    FileDataSource(FileDataSource&&) = default;

    FileDataSource(const std::string& fileName, const Index width);

    ~FileDataSource() = default;

    // TODO: Make const (and m_FileStream mutable)
    double ReadValueAt(const Index lineNumber) noexcept;

    void WriteValueAt(const double value, const Index lineNumber) noexcept;

    Index Count() const noexcept;
    Index Size() const noexcept;

    FileDataSource& operator = (const FileDataSource&) = delete;
    FileDataSource& operator = (FileDataSource&&) = delete;

private:
    bool CheckOpen() const noexcept;

    bool MoveStreamPointer(const Index lineNumber) noexcept;

private:
    std::filesystem::path m_FilePath;
    std::fstream m_FileStream;

    Index m_Width;
};
