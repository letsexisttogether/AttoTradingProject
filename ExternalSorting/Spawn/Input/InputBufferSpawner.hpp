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

    InputBufferSpawner(const FileInfo& directoryInfo,
        const std::size_t availableMemory) noexcept(false);

    InputBufferSpawner(FileInfo&& directoryInfo,
        const std::size_t availableMemory) noexcept(false);

    ~InputBufferSpawner() = default;

    InputBuffer Spawn() noexcept(false);

    InputBufferSpawner& operator = (const InputBufferSpawner&) = delete;
    InputBufferSpawner& operator = (InputBufferSpawner&&) = delete;

private:
    void FetchFiles(const std::size_t availableMemory) noexcept(false);

private:
    std::vector<std::filesystem::path> m_Files{};
};
