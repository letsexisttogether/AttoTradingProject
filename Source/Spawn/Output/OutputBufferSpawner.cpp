#include "OutputBufferSpawner.hpp"

#include "Parse/Value/ValueParser.hpp"

OutputBufferSpawner::OutputBufferSpawner(FileInfo&& fileInfo,
    const std::size_t readSize) noexcept
    : m_FileInfo{ fileInfo }, m_ReadSize{ readSize }
{}


OutputBufferSpawner::OutputBuffer OutputBufferSpawner::Spawn()
    noexcept(false)
{
    FileWriter<double> writer
    {
        m_FileInfo, new ValueParser{}
    };

    return { std::move(writer), m_ReadSize };
}
