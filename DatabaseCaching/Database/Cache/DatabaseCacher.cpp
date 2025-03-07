#include "DatabaseCacher.hpp"

DatabaseCacher::DatabaseCacher(i_db* const database, 
    Cache* const cache) noexcept
    : m_DataBase{ database }, m_Cache{ cache }
{}

bool DatabaseCacher::begin_transaction() 
{
    std::lock_guard<std::mutex> lock{ m_CacheMutex };

    if (m_IsTransaction)
    {
        return false; 
    }

    m_IsTransaction = m_DataBase->begin_transaction();

    if (m_IsTransaction)
    {
        m_TransactionCache.reset(m_Cache->Clone());
    }

    return m_IsTransaction;
}

bool DatabaseCacher::commit_transaction()
{
    std::lock_guard<std::mutex> lock{ m_CacheMutex };

    if (!m_IsTransaction) 
    {
        return false;
    }

    const bool isCommitSuccess = m_DataBase->commit_transaction();

    if (isCommitSuccess)
    {
        *m_Cache = std::move(*m_TransactionCache);
        m_TransactionCache.reset();

        m_IsTransaction = false;
    }

    return isCommitSuccess;
}

bool DatabaseCacher::abort_transaction()
{
    std::lock_guard<std::mutex> lock(m_CacheMutex);

    if (!m_IsTransaction)
    {
        return false;
    }

    const bool isAbortSuccess = m_DataBase->abort_transaction();

    if (isAbortSuccess)
    {
        m_TransactionCache.reset();

        m_IsTransaction = false;
    }

    return isAbortSuccess;
}

std::string DatabaseCacher::get(const std::string& key)
{
    std::lock_guard<std::mutex> lock{ m_CacheMutex };

    Cache* const cache = ((m_IsTransaction) ?
        (m_TransactionCache.get()) : (m_Cache.get()));

    if (cache->DoesExist(key))
    {
        return cache->Get(key);
    }

    const std::string data{ m_DataBase->get(key) };
    cache->Set(key, data);

    return data;
}

std::string DatabaseCacher::set(const std::string& key, const std::string& data)
{
    std::lock_guard<std::mutex> lock{ m_CacheMutex };

    Cache* const cache = ((m_IsTransaction) ?
        (m_TransactionCache.get()) : (m_Cache.get()));

    const std::string realKey{ m_DataBase->set(key, data) }; 

    cache->Set(realKey, data);

    return realKey;
}

std::string DatabaseCacher::remove(const std::string& key)
{
    std::lock_guard<std::mutex> lock{ m_CacheMutex };

    Cache* const cache = ((m_IsTransaction) ?
        (m_TransactionCache.get()) : (m_Cache.get()));

    cache->Remove(key);

    return m_DataBase->remove(key);
}
