#pragma once

#include <fstream>
#include <vector>

#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"

class FileData
{
public:
    using Data = std::vector<double>;

public:
    FileData() = delete;
    FileData(const FileData&) = delete;
    FileData(FileData&&) = default;

    FileData(std::ifstream&& inputStream, std::ofstream&& outputStream,
        const std::size_t chunkSize) noexcept(false);

    ~FileData() = default;

    std::size_t Read() noexcept(false);
    void Write() noexcept(false);

    Data& GetData() noexcept;

    bool IsInputEOF() const noexcept;
    bool IsOutputEOF() const noexcept;

    FileData& operator = (const FileData&) noexcept = delete;
    FileData& operator = (FileData&&) noexcept = delete;

private:
    std::ifstream m_InputStream;
    std::ofstream m_OutputStream;

    std::size_t m_ChunkSize;
    Data m_Data{};

    std::unique_ptr<Parser<char, double>> m_ByteParser
    {
        new ByteParser{}
    };
    std::unique_ptr<Parser<double, char>> m_ValueParser 
    {
        new ValueParser{}
    };
};
