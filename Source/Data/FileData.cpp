#include "FileData.hpp"

#include <filesystem>

FileData::FileData(std::ifstream&& inputFile, std::ofstream&& outputFile,
    const std::size_t chunkSize)
    : m_InputStream{ std::move(inputFile) }, 
    m_OutputStream{ std::move(outputFile) },
    m_ChunkSize{ chunkSize }
{
    if (!m_InputStream.is_open() || !m_OutputStream.is_open())
    {
        throw std::exception{ "Cannot open files" };
    }
}

std::size_t FileData::Read() noexcept(false)
{
    ByteParser::InputBuffer rawBuffer(m_ChunkSize);

    m_InputStream.read(rawBuffer.data(), m_ChunkSize);

    if (m_InputStream.bad())
    {
        throw std::exception{ "The read operation has failed" };
    }

    m_Data = m_ByteParser->Parse(rawBuffer);

    return m_InputStream.gcount();
}

void FileData::Write() noexcept(false)
{
    ValueParser::OutputBuffer rawBuffer 
    { 
        m_ValueParser->Parse(m_Data) 
    };

    m_OutputStream.write(rawBuffer.data(), rawBuffer.size());

    if (m_OutputStream.bad())
    {
        throw std::exception{ "The write operation has failed" };
    }
}

FileData::Data& FileData::GetData() noexcept
{
    return m_Data;
}

bool FileData::IsInputEOF() const noexcept
{
    return m_InputStream.eof();
}

bool FileData::IsOutputEOF() const noexcept
{
    return m_OutputStream.eof();
}
