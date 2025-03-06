#include "BufferSpawner.hpp"

BufferSpawner::BufferSpawner(FileInfo&& info, const std::size_t readSize,
    const std::size_t entitiesCount) noexcept
    : m_Info{ std::move(info) }, m_BufferSize{ readSize },
    m_EntitiesCount{ entitiesCount }
{}

bool BufferSpawner::IsEnd() const noexcept
{
    return !m_EntitiesCount;
}
