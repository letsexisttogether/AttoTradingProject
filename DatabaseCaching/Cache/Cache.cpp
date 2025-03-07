#include "Cache.hpp"

std::string Cache::Get(const std::string& key) const noexcept
{
    if (const auto iter = m_Buffer.find(key); iter != m_Buffer.end())
    {
        return iter->second;
    }

    return {};
}

std::string Cache::Set(const std::string& key, const std::string& data)
    noexcept
{
    m_Buffer[key] = data;

    return key;
}

std::string Cache::Remove(const std::string& key) noexcept
{
    if (const auto iter = m_Buffer.find(key); iter != m_Buffer.end())
    {
        const std::string data{ std::move(iter->second) };

        m_Buffer.erase(iter); 

        return data;
    }

    return {};
}

void Cache::Clear() noexcept
{
    m_Buffer.clear(); 
}

std::size_t Cache::GetSize() const noexcept
{
    return m_Buffer.size();
}
