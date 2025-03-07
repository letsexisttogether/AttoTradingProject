#pragma once

#include <memory>
#include <mutex>

#include "Cache/Cache.hpp"
#include "Database/Database.hpp"

class DatabaseCacher : public i_db
{
public:
    using CachePtr = std::unique_ptr<Cache>;

public:
    DatabaseCacher() = delete;
    DatabaseCacher(const DatabaseCacher&) = delete;
    DatabaseCacher(DatabaseCacher&&) = delete;

    DatabaseCacher(i_db* const database,
        Cache* const cache = new Cache{}) noexcept;

    ~DatabaseCacher() = default;

    bool begin_transaction() override;
    bool commit_transaction() override;
    bool abort_transaction() override;

    std::string get(const std::string& key) override;
    std::string set(const std::string& key,
        const std::string& data) override;
    std::string remove(const std::string& key) override;

    DatabaseCacher& operator = (const DatabaseCacher&) = delete;
    DatabaseCacher& operator = (DatabaseCacher&&) = delete;

private:
    i_db* m_DataBase;

    CachePtr m_Cache;
    std::mutex m_CacheMutex{};

    CachePtr m_TransactionCache{};
    bool m_IsTransaction{};
};
