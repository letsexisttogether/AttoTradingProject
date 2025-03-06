#pragma once

#include "Spawn/BufferSpawner.hpp"
#include "Buffer/Input/InputBuffer.hpp"
#include "General/FileInfo.hpp"

class InputBufferSpawner : public BufferSpawner
{ 
public:
    using InputBuffer = InputBuffer<double>;

public:
    InputBufferSpawner() = delete;
    InputBufferSpawner(const InputBufferSpawner&) = default;
    InputBufferSpawner(InputBufferSpawner&&) = delete;

    InputBufferSpawner(FileInfo&& directoryInfo,
        const std::size_t memoryAvailable) noexcept(false);

    ~InputBufferSpawner() = default;

    InputBuffer Spawn() noexcept(false);

    InputBufferSpawner& operator = (const InputBufferSpawner&) = delete;
    InputBufferSpawner& operator = (InputBufferSpawner&&) = delete;

private:
    std::vector<std::filesystem::path> m_Files{};
};
