#include "FileDataGenerator.hpp"

#include <exception>
#include <iostream>

#include "Spawn/Output/OutputBufferSpawner.hpp"

FileDataGenerator::FileDataGenerator(const std::filesystem::path& path,
    const std::size_t fileSize, const std::size_t bufferSize,
    const Range& valuesRange) noexcept
    : m_Info{ path, std::ios::out }, m_FileSize{ fileSize },
    m_BufferSize{ bufferSize }, m_Generator{ std::random_device{}() },
    m_Distribution{ valuesRange.first, valuesRange.second }
{}

void FileDataGenerator::Generate() noexcept
{
    std::cout << "Filling the file...\n";

    try
    {
        OutputBufferSpawner spawner
        {
            m_Info, m_BufferSize
        };

        auto outputBuffer = spawner.Spawn();

        for (std::size_t i = 0; i < m_FileSize;)
        {
            if (outputBuffer.IsEnd())
            {
                i += outputBuffer.Write();
            }

            outputBuffer.PutValue(RandomizeValue());
        }

    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during generation] " << exp.what()
            << std::endl;

        return;
    }

    std::cout << "[Success] The file has been filled" << std::endl;
};


double FileDataGenerator::RandomizeValue() noexcept
{
    return m_Distribution(m_Generator);
}
