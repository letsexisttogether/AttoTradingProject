#pragma once

#include "Buffer/Input/InputBuffer.hpp"
#include "General/FileInfo.hpp"

class InputBufferSpawner
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

    bool IsEnd() const noexcept;

    InputBufferSpawner& operator = (const InputBufferSpawner&) = delete;
    InputBufferSpawner& operator = (InputBufferSpawner&&) = delete;

private:
    FileInfo m_DirectoryInfo;

    std::size_t m_ReadSize;
    
    std::vector<std::filesystem::path> m_Files{};
    std::size_t m_Iterator{};
};
