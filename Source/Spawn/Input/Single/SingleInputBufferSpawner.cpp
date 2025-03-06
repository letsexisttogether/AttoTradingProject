#include "SingleInputBufferSpawner.hpp"

SingleInputBufferSpawner::SingleInputBufferSpawner(const FileInfo fileInfo,
    const std::size_t chunkSize) noexcept(false)
    : InputBufferSpawner{ fileInfo, chunkSize }
{}

InputBuffer SingleInputBufferSpawner::Spawn() noexcept(false)
{
    InputBuffer buffer
    {
        m_FileStream, 0, m_ChunkSize, m_FileSize
    };
   
    m_IsBufferSpawned = true;

    return buffer;
}

bool SingleInputBufferSpawner::IsSpawnDone() const noexcept
{
    return m_IsBufferSpawned; 
}
