#include "Cache.hpp"

std::string Cache::Get(const std::string& key) const noexcept
{
    if (DoesExist(key))
    {
        return m_LastLookup->second;
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
    if (DoesExist(key))
    {
        const std::string data{ std::move(m_LastLookup->second) };

        m_Buffer.erase(m_LastLookup); 

        return data;
    }

    return {};
}


bool Cache::DoesExist(const std::string& key) const noexcept
{
    m_LastLookup = m_Buffer.find(key);

    return m_LastLookup != m_Buffer.end();
}

void Cache::Clear() noexcept
{
    m_Buffer.clear(); 
}

Cache* Cache::Clone() const noexcept
{
    return new Cache{ *this };
}

std::size_t Cache::GetSize() const noexcept
{
    return m_Buffer.size();
}
