#pragma once

#include <fstream>
#include <memory>
#include <exception>

#include "FileProcess/FileProcessor.hpp"
#include "Parse/Parser.hpp"

template <typename _Type>
class FileReader : public FileProcessor<std::ifstream>
{
public:
    using OutputData = std::vector<_Type>;
    using Parser = Parser<char, _Type>;

public:
    FileReader() = delete;
    FileReader(const FileReader&) = delete;
    FileReader(FileReader&&) = default;

    FileReader(const FileInfo& fileInfo, Parser* const parser)
        noexcept(false); 

    ~FileReader() = default;

    OutputData Read(const std::size_t m_ReadSize) noexcept(false);

    std::size_t GetPointer() noexcept override;
    void PlacePointer(const std::size_t position) noexcept override;

    std::size_t GetLastReadBytes() const noexcept;

private:
    using RawData = std::vector<char>;

private:
    std::unique_ptr<Parser> m_Parser;
};


template <typename _Type>
FileReader<_Type>::FileReader(const FileInfo& fileInfo, Parser* const parser)
    noexcept(false)
    : FileProcessor{ fileInfo }, m_Parser{ parser }
{}

template <typename _Type>
typename FileReader<_Type>::OutputData FileReader<_Type>::Read
    (const std::size_t m_ReadSize) noexcept(false)
{
    RawData rawData(m_ReadSize);

    m_FileStream.read(rawData.data(), rawData.size());

    if (m_FileStream.bad())
    {
        throw std::exception{ "The read operation has failed" };
    }

    return m_Parser->Parse(rawData);
}

template <typename _Type>
std::size_t FileReader<_Type>::GetPointer() noexcept
{
    return m_FileStream.tellg();
}

template <typename _Type>
void FileReader<_Type>::PlacePointer(const std::size_t position) noexcept
{
    m_FileStream.seekg(position);
}

template <typename _Type>
std::size_t FileReader<_Type>::GetLastReadBytes() const noexcept
{
    return m_FileStream.gcount();
}
