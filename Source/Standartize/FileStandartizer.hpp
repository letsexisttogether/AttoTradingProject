#pragma once

#include <string>
#include <filesystem>
#include <fstream>

class FileStandartizer
{
public:
    FileStandartizer() = default;
    FileStandartizer(const FileStandartizer&) = delete;
    FileStandartizer(FileStandartizer&&) = delete;

    FileStandartizer(const std::string& inputFilePath,
        const std::string& outputFilePath);

    ~FileStandartizer() = default;

    void Standartize() noexcept;

private:
    std::filesystem::path m_InputPath;
    std::ifstream m_InputStream;

    std::filesystem::path m_OutputPath;
    std::ofstream m_OutputStream;
};
