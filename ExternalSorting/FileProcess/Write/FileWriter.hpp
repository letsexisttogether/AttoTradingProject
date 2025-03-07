#pragma once

#include <fstream>
#include <iosfwd>
#include <memory>

#include "FileProcess/FileProcessor.hpp"
#include "Parse/Parser.hpp"

template <typename _Type>
class FileWriter : public FileProcessor<std::ofstream>
{
public:
    using InputData = std::vector<_Type>;
    using Parser = Parser<_Type, char>;

public:
    FileWriter() = delete;
    FileWriter(const FileWriter&) = delete;
    FileWriter(FileWriter&&) = default;

    FileWriter(const FileInfo& fileInfo, Parser* const parser)
        noexcept(false); 

    ~FileWriter() = default;

    std::size_t Write(const InputData& inputData) noexcept(false);

    std::size_t GetPointer() noexcept override;
    void PlacePointer(const std::size_t position) noexcept override;

private:
    using RawData = std::vector<char>;

private:
    std::unique_ptr<Parser> m_Parser;
};


template <typename _Type>
FileWriter<_Type>::FileWriter(const FileInfo& fileInfo, Parser* const parser)
    noexcept(false)
    : FileProcessor{ fileInfo }, m_Parser{ parser }
{}

template <typename _Type>
std::size_t FileWriter<_Type>::Write(const InputData& inputData)
    noexcept(false)
{
    RawData rawData{ m_Parser->Parse(inputData) };

    m_FileStream.write(rawData.data(), rawData.size());

    if (m_FileStream.bad())
    {
        throw std::exception{ "The read operation has failed" };
    }
    
    return rawData.size();
}

template <typename _Type>
std::size_t FileWriter<_Type>::GetPointer() noexcept
{
    return m_FileStream.tellp();
}

template <typename _Type>
void FileWriter<_Type>::PlacePointer(const std::size_t position) noexcept
{
    m_FileStream.seekp(position);
}
