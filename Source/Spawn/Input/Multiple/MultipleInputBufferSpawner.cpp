#include "MultipleInputBufferSpawner.hpp"

MultipleInputBufferSpawner::MultipleInputBufferSpawner(const FileInfo fileInfo,
    const std::size_t chunkSize, const std::size_t bufferSize)
    noexcept(false)
    : InputBufferSpawner{ fileInfo, chunkSize },
    m_BufferSize{ bufferSize }
{}

InputBuffer MultipleInputBufferSpawner::Spawn() noexcept(false)
{
    const std::size_t newPosition = m_BufferPosition + m_BufferSize;

    InputBuffer buffer
    {
        m_FileStream, m_BufferPosition,
        m_ChunkSize, newPosition
    };

    m_BufferPosition = newPosition;

    return buffer;
}

bool MultipleInputBufferSpawner::IsSpawnDone() const noexcept
{
    return m_BufferPosition >= m_FileSize;
}
