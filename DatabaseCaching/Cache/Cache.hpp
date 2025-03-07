#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class Cache
{
public:
    using Buffer = std::unordered_map<std::string, std::string>;

public:
    Cache() = default;
    Cache(const Cache&) = default;
    Cache(Cache&&) = default;

    virtual ~Cache() = default;

    virtual std::string Get(const std::string& key) const noexcept;
    virtual std::string Set(const std::string& key, const std::string& data)
        noexcept;
    virtual std::string Remove(const std::string& key) noexcept;

    virtual void Clear() noexcept;

    std::size_t GetSize() const noexcept;

    Cache& operator = (const Cache&) = default;
    Cache& operator = (Cache&&) = default;

protected:
     Buffer m_Buffer;
};
