#include "OutputBufferSpawner.hpp"

#include "Parse/Value/ValueParser.hpp"

OutputBufferSpawner::OutputBufferSpawner(FileInfo&& fileInfo,
    const std::size_t readSize) noexcept
    : BufferSpawner{ std::move(fileInfo), readSize, 1 }
{}

OutputBufferSpawner::OutputBuffer OutputBufferSpawner::Spawn()
    noexcept(false)
{
    FileWriter<double> writer
    {
        m_Info, new ValueParser{}
    };

    --m_EntitiesCount;

    return { std::move(writer), m_ReadSize };
}
