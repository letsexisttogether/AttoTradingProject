#include "FileDataSource.hpp"

#include <filesystem>
#include <iostream>

FileDataSource::FileDataSource(FileInfo&& fileInfo, Size bufferSize)
    : m_FileInfo{ std::move(fileInfo) },
      m_FileStream{ m_FileInfo.Path, std::ios::in | std::ios::out | std::ios::binary },
      m_ChunkSize{ bufferSize }
{
    if (!std::filesystem::exists(m_FileInfo.Path))
    {
        std::cerr << "[Error] File does not exist: "
            << m_FileInfo.Path << std::endl;

        return;
    }

    constexpr Size doubleSize = sizeof(double);

    m_FileSize = std::filesystem::file_size(m_FileInfo.Path);
    m_ValuesCount = m_FileSize / doubleSize;

    m_ChunkSize = std::min(m_FileSize, m_ChunkSize);

    m_RealData.resize(m_ChunkSize / doubleSize);

    m_MinPosition = 0;
    m_MaxPosition = m_ChunkSize / doubleSize;

    MoveStreamPointer(0);
    ReadData();

    std::cout << "The file size is " << m_FileSize
        << " The count is " << GetCount() << std::endl;
}

double FileDataSource::GetValue(Size valueNumber) noexcept
{
    if (!m_FileStream.good())
    {
        std::cerr << "FileStream is not good" << std::endl;

        return {};
    }

    if (valueNumber < m_MinPosition || valueNumber >= m_MaxPosition)
    {
        WriteData();
        MoveStreamPointer(valueNumber);
        ReadData();
    }

    const Size index = valueNumber - m_MinPosition;

    return m_RealData[index];
}

void FileDataSource::MoveStreamPointer(const Size valueNumber) noexcept
{
    const Size realPosition = valueNumber * sizeof(double);

    if (realPosition >= m_FileSize)
    {
        std::cerr << "[Error] Specified position is out of range: " << realPosition << std::endl;

        return;
    }

    m_FileStream.clear();
    m_FileStream.seekg(realPosition);
    m_FileStream.seekp(realPosition);

    if (!m_FileStream.good())
    {
        std::cerr << "[Error] Failed to seek to position: " << realPosition << std::endl;
    }
}

void FileDataSource::ReadData() noexcept
{
    if (!m_FileStream.is_open())
    {
        std::cerr << "[Error] File stream is not open for reading" << std::endl;
        return;
    }

    if (!m_FileStream.good())
    {
        std::cerr << "[Error] File stream is in a bad state before reading" << std::endl;
        m_FileStream.clear();  // Clear error flags
    }

    Size bytesToRead = std::min(m_ChunkSize, m_FileSize - m_FileStream.tellg());

    m_FileStream.read(reinterpret_cast<char*>(m_RealData.data()), bytesToRead);
    
    std::streamsize bytesRead = m_FileStream.gcount();
    
    if (bytesRead == 0 || !m_FileStream.good())
    {
        std::cerr << "[Error] Failed to read data from file" << std::endl;
        return;
    }

    m_MaxPosition = (m_FileStream.tellg() != -1) ? (m_FileStream.tellg() / sizeof(double)) : m_FileSize / sizeof(double);
    m_MinPosition = m_MaxPosition - (bytesRead / sizeof(double));
}

void FileDataSource::WriteData() noexcept
{
    if (!m_FileStream.good())
    {
        std::cerr << "[Error] File stream is not open for writing" << std::endl;

        return;
    }

    MoveStreamPointer(m_MinPosition);

    m_FileStream.write(reinterpret_cast<const char*>
        (m_RealData.data()), m_ChunkSize);

    if (!m_FileStream.good())
    {
        std::cerr << "[Error] Failed to write data to file" << std::endl;
    }
}


FileDataSource::Size FileDataSource::GetSize() const noexcept
{
    return m_FileSize;
}

FileDataSource::Size FileDataSource::GetCount() const noexcept
{
    return m_FileSize / sizeof(double);
}
