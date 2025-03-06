#pragma once

#include "Spawn/Input/InputBufferSpawner.hpp"

class SingleInputBufferSpawner : public InputBufferSpawner
{
public:
    SingleInputBufferSpawner() = delete;
    SingleInputBufferSpawner(const SingleInputBufferSpawner&) = delete;
    SingleInputBufferSpawner(SingleInputBufferSpawner&&) = default;

    SingleInputBufferSpawner(const FileInfo fileInfo,
        const std::size_t chunkSize) noexcept(false);

    ~SingleInputBufferSpawner() = default;

    InputBuffer Spawn() noexcept(false) override;

    bool IsSpawnDone() const noexcept override;

    SingleInputBufferSpawner& operator = (const SingleInputBufferSpawner&)
        = delete;
    SingleInputBufferSpawner& operator = (SingleInputBufferSpawner&&)
        = delete;

private:
    bool m_IsBufferSpawned{};
};
