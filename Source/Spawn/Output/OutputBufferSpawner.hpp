#pragma once

#include "Buffer/Output/OutputBuffer.hpp"
#include "General/FileInfo.hpp"

class OutputBufferSpawner
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

    bool IsEnd() const noexcept;

    OutputBufferSpawner& operator = (const OutputBufferSpawner&) = delete;
    OutputBufferSpawner& operator = (OutputBufferSpawner&&) = delete;

private:
    FileInfo m_FileInfo;

    std::size_t m_ReadSize{};
};
