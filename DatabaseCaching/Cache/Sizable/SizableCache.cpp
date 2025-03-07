#include "SizableCache.hpp"
#include "Cache/Cache.hpp"

#include <iostream>

SizableCache::SizableCache(const std::size_t maxSize,
    const std::size_t removeSize) noexcept
    : m_MaxSize{ maxSize }, 
    m_RemoveSize{ std::min(removeSize, m_MaxSize) }
{}

std::string SizableCache::Set(const std::string& key,
    const std::string& data) noexcept
{
    const auto [iter, inserted] = m_Buffer.try_emplace(key, data);

    if (inserted)
    {
        m_Keys.push(key);
    }

    if (m_Buffer.size() > m_MaxSize)
    {
        RemoveExcess();
    }

    return key;
}

void SizableCache::Clear() noexcept
{
    Cache::Clear();

    while(!m_Keys.empty())
    {
        m_Keys.pop();
    }
}


void SizableCache::RemoveExcess() noexcept
{
    if (m_MaxSize == m_RemoveSize)
    {
        Clear();

        return;
    }

    for (std::size_t i = 0; i < m_RemoveSize && !m_Keys.empty(); ++i)
    {
        const std::string storedKey{ std::move(m_Keys.front()) };
        m_Keys.pop();

        Remove(storedKey);
    }
}
