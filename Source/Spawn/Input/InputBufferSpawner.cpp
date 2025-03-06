#include "InputBufferSpawner.hpp"

#include <stdexcept>

#include "Parse/Byte/ByteParser.hpp"

InputBufferSpawner::InputBufferSpawner(FileInfo&& directoryInfo,
    const std::size_t memoryAvailable) noexcept(false)
    : m_DirectoryInfo{ std::move(directoryInfo) }
{
    const std::filesystem::path& path = m_DirectoryInfo.Path;

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

    m_ReadSize = memoryAvailable / m_Files.size();
}


InputBufferSpawner::InputBuffer InputBufferSpawner::Spawn() noexcept(false)
{
    InputBuffer::FileReader reader
    {
        { m_Files.at(m_Iterator++), m_DirectoryInfo.OpenMode },
        new ByteParser{}
    };

    return { std::move(reader), m_ReadSize };
}

bool InputBufferSpawner::IsEnd() const noexcept
{
    return m_Iterator >= m_Files.size();
}
