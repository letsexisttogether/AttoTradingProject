#include "FileDataSource.hpp"

#include <iostream>
#include <filesystem>

FileDataSource::FileDataSource(const std::string& fileName, const Index width)
    : m_FilePath{ fileName }, m_FileStream{ m_FilePath }, m_Width{ width + 2}
{
    if (!std::filesystem::exists(fileName))
    {
        std::cerr << "[Error] A file with the provided name \"" 
            << fileName << "\" does not exist" << std::endl;
    }
}

double FileDataSource::ReadValueAt(const Index lineNumber) noexcept
{ 

    if (!CheckOpen() || !MoveStreamPointer(lineNumber))
    {
        return {};
    }

    double value{};
    
    if (!(m_FileStream >> value))
    {
        std::cerr << "[Error] Failed to read the value at line number \"" 
            << lineNumber << "\"" << std::endl;

        return {};
    }

    return value;
}

void FileDataSource::WriteValueAt(const double value, const Index lineNumber)
    noexcept
{
    if (!CheckOpen() || !MoveStreamPointer(lineNumber))
    {
        return; 
    }

    m_FileStream << std::scientific << std::setprecision(8);

    if (!(m_FileStream << std::setw(15) << std::right
            << value << std::endl))
    {
        std::cerr << "[Error] Failed to write the value at line number \"" 
            << lineNumber << "\"" << std::endl;
    }
}

FileDataSource::Index FileDataSource::Count() const noexcept
{
    return Size() / m_Width;
}

FileDataSource::Index FileDataSource::Size() const noexcept
{
    return std::filesystem::file_size(m_FilePath);
}

bool FileDataSource::CheckOpen() const noexcept
{
    if (!m_FileStream.is_open())
    {
        std::cerr << "[Error] No access to the file" << std::endl;

        return false; 
    }

    return true;
}

bool FileDataSource::MoveStreamPointer(const Index lineNumber) noexcept
{
    const Index realPosition = lineNumber * m_Width;
    m_FileStream.seekg(realPosition);

    if (!m_FileStream.good())
    {
        std::cerr << "[Error] Seeking to the specified line number \"" 
            << lineNumber << "\" failed" << std::endl;

        return false; 
    }

    return true;
}
