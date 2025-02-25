#include "FileStandartizer.hpp"

#include <ios>
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

FileStandartizer::Size FileStandartizer::Standartize(const Size precision)
    noexcept
{
    const Size width = CalculateWidth(precision);

    m_OutputStream << std::scientific << std::setprecision(precision);

    for (double value; m_InputStream >> value; )
    {
        m_OutputStream << std::setw(width) << std::right
            << value << std::endl;
    }

    if (m_InputStream.fail() && !m_InputStream.eof())
    {
        std::cerr << "[Error] Standartized found "
            "a non-double value" << std::endl;

        std::filesystem::remove(m_OutputPath);

        return 0;
    }

    return width;
}

FileStandartizer::Size FileStandartizer::CalculateWidth(const Size precision)
    const noexcept
{
    // Formula: possible sign + decimal + precision + e + e-sign + e-digits
    return 1 + 1 + precision + 1 + 1 + 3;
}
