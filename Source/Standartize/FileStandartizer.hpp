#pragma once

#include <string>
#include <filesystem>
#include <fstream>

class FileStandartizer
{
public:
    using Size = std::uint8_t;

public:
    FileStandartizer() = default;
    FileStandartizer(const FileStandartizer&) = delete;
    FileStandartizer(FileStandartizer&&) = delete;

    FileStandartizer(const std::string& inputFilePath,
        const std::string& outputFilePath);

    ~FileStandartizer() = default;

    Size Standartize(const Size precision) noexcept;

private:
    Size CalculateWidth(const Size precision) const noexcept;

private:
    std::filesystem::path m_InputPath;
    std::ifstream m_InputStream;

    std::filesystem::path m_OutputPath;
    std::ofstream m_OutputStream;
};
