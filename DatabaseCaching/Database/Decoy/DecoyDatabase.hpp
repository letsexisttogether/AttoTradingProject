#pragma once

#include "Database/Database.hpp"

class DecoyDatabase : public i_db
{
public:
    DecoyDatabase() = default;
    DecoyDatabase(const DecoyDatabase&) = delete;
    DecoyDatabase(DecoyDatabase&&) = delete;

    ~DecoyDatabase() = default;

    bool begin_transaction() override;
    bool commit_transaction() override;
    bool abort_transaction() override;

    std::string get(const std::string& key) override;
    std::string set(const std::string& key,
        const std::string& data) override;
    std::string remove(const std::string& key) override;

    DecoyDatabase& operator = (const DecoyDatabase&) = delete;
    DecoyDatabase& operator = (DecoyDatabase&&) = delete;
};
