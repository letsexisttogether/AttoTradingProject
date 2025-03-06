#pragma once

#include "General/FileInfo.hpp"

class BufferSpawner
{
public:
    BufferSpawner() = default;
    BufferSpawner(const BufferSpawner&) = default;
    BufferSpawner(BufferSpawner&&) = default;

    BufferSpawner(FileInfo&& info, const std::size_t readSize = 0,
        const std::size_t entitiesCount = 0) noexcept;

    ~BufferSpawner() = default;

    bool IsEnd() const noexcept;

    BufferSpawner& operator = (const BufferSpawner& spawner) = delete;
    BufferSpawner& operator = (BufferSpawner&& spawner) = delete;

protected:
    FileInfo m_Info{};
    std::size_t m_ReadSize{};
    std::size_t m_EntitiesCount{};
};
