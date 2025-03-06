#pragma once

#include "Spawn/General/FileInfo.hpp"
#include "Buffers/Input/InputBuffer.hpp"

class InputBufferSpawner
{
public:
    InputBufferSpawner() = delete;
    InputBufferSpawner(const InputBufferSpawner&) = delete;
    InputBufferSpawner(InputBufferSpawner&&) = default;

    InputBufferSpawner(const FileInfo fileInfo,
        const std::size_t chunkSize) noexcept(false);

    virtual ~InputBufferSpawner() = default;

    virtual InputBuffer Spawn() noexcept(false) = 0;

    virtual bool IsSpawnDone() const noexcept = 0;

protected:
    FileInfo m_FileInfo;
    std::ifstream m_FileStream;

    std::size_t m_ChunkSize;
    std::size_t m_FileSize;
};
