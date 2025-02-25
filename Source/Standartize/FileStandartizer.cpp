#include "FileStandartizer.hpp"

#include <iostream>
#include <string>

FileStandartizer::FileStandartizer(const std::string& inputFilePath,
        const std::string& outputFilePath)
    : m_InputPath{ inputFilePath }, m_InputStream{ m_InputPath },
    m_OutputPath{ outputFilePath }, m_OutputStream { m_OutputPath }
{
    if (!std::filesystem::exists(m_InputPath))
    {
        std::cerr << "[Error] A file with the provided path \"" 
            << m_InputPath << "\" does not exist" << std::endl;
    }
}

void FileStandartizer::Standartize() noexcept
{
    if (!m_InputStream.is_open()) 
    {
        // TODO: Fix this, type the real path 
        std::cerr << "[Error] Could not open input file \"" 
            << m_InputPath << '\"' << std::endl;

        return;
    }

    for (double value; m_InputStream >> value; )
    {
        m_OutputStream << value << std::endl;
    }

    if (m_InputStream.fail() && !m_InputStream.eof())
    {
        std::cerr << "[Error] Standartized found "
            "a non-double value" << std::endl;
    }
}
