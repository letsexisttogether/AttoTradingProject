#pragma once

#include "Cache/Cache.hpp"

#include <queue>

class SizableCache : public Cache
{
public:
    SizableCache() = delete;
    SizableCache(const SizableCache&) = default;
    SizableCache(SizableCache&&) = default;

    SizableCache(const std::size_t maxSize, const std::size_t removeSize)
        noexcept;

    virtual ~SizableCache() = default;

    std::string Set(const std::string& key, const std::string& data)
        noexcept override;

    void Clear() noexcept override;

    SizableCache& operator = (const SizableCache&) = default;
    SizableCache& operator = (SizableCache&&) = default;

private:
    void RemoveExcess() noexcept;

private:
    std::size_t m_MaxSize;
    std::size_t m_RemoveSize;

    std::queue<std::string> m_Keys{};
};
