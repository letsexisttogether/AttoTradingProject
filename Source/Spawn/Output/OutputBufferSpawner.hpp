#pragma once

#include "Spawn/BufferSpawner.hpp"
#include "Buffer/Output/OutputBuffer.hpp"
#include "General/FileInfo.hpp"

class OutputBufferSpawner : public BufferSpawner
{
public:
    using OutputBuffer = OutputBuffer<double>;

public:
    OutputBufferSpawner() = delete;
    OutputBufferSpawner(const OutputBufferSpawner&) = default;
    OutputBufferSpawner(OutputBufferSpawner&&) = delete;

    OutputBufferSpawner(FileInfo&& fileInfo,
        const std::size_t readSize) noexcept;

    ~OutputBufferSpawner() = default;

    OutputBuffer Spawn() noexcept(false);

    OutputBufferSpawner& operator = (const OutputBufferSpawner&) = delete;
    OutputBufferSpawner& operator = (OutputBufferSpawner&&) = delete;
};
