#include "OutputBufferSpawner.hpp"

#include "Parse/Value/ValueParser.hpp"

OutputBufferSpawner::OutputBufferSpawner(const FileInfo& fileInfo,
    const std::size_t bufferSize) noexcept
    : BufferSpawner{ fileInfo, bufferSize / sizeof(double), 1 }
{}

OutputBufferSpawner::OutputBufferSpawner(FileInfo&& fileInfo,
    const std::size_t bufferSize) noexcept
    : BufferSpawner{ std::move(fileInfo), bufferSize / sizeof(double), 1 }
{}

OutputBufferSpawner::OutputBuffer OutputBufferSpawner::Spawn()
    noexcept(false)
{
    FileWriter<double> writer
    {
        m_Info, new ValueParser{}
    };

    --m_EntitiesCount;

    return { std::move(writer), m_BufferSize };
}
