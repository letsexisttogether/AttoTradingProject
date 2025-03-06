#pragma once

#include "Spawn/Input/InputBufferSpawner.hpp"

class MultipleInputBufferSpawner : public InputBufferSpawner
{
public:
    MultipleInputBufferSpawner() = delete;
    MultipleInputBufferSpawner(const MultipleInputBufferSpawner&) = delete;
    MultipleInputBufferSpawner(MultipleInputBufferSpawner&&) = default;

    MultipleInputBufferSpawner(const FileInfo fileInfo,
        const std::size_t chunkSize, const std::size_t bufferSize)
        noexcept(false);

    ~MultipleInputBufferSpawner() = default;

    InputBuffer Spawn() noexcept(false) override;

    bool IsSpawnDone() const noexcept override;

    MultipleInputBufferSpawner& operator = (const MultipleInputBufferSpawner&)
        = delete;
    MultipleInputBufferSpawner& operator = (MultipleInputBufferSpawner&&)
        = delete;

private:
    std::size_t m_BufferPosition{};
    std::size_t m_BufferSize{};
};
