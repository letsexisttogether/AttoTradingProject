#include "InputBufferSpawner.hpp"

#include <stdexcept>

#include "Parse/Byte/ByteParser.hpp"

InputBufferSpawner::InputBufferSpawner(FileInfo&& directoryInfo,
    const std::size_t availableMemory) noexcept(false)
    : BufferSpawner{ std::move(directoryInfo) }
{
    const std::filesystem::path& path = m_Info.Path;

    if (!std::filesystem::exists(path)
        || !std::filesystem::is_directory(path))
    {
        throw std::runtime_error{ "No access to the specified directory" };
    }

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file()) 
        {
            m_Files.push_back(entry.path());
        }
    }

    m_EntitiesCount = m_Files.size();

    if (IsEnd())
    {
        throw std::runtime_error{ "No files found in the directory" };
    }

    m_BufferSize = availableMemory / m_EntitiesCount;
}

InputBufferSpawner::InputBuffer InputBufferSpawner::Spawn() noexcept(false)
{
    const std::size_t fileIndex = m_Files.size() - m_EntitiesCount--; 

    InputBuffer::FileReader reader
    {
        { m_Files.at(fileIndex), m_Info.OpenMode },
        new ByteParser{}
    };

    return { std::move(reader), m_BufferSize };
}
